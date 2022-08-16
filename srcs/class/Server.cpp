#include "Server.hpp"

Server::Server() {}

/**
 * Description:
 * 	The constructor that should be used. It will setup sockets
 * 	to receive further connections.
 * 
 * Args:
 *		port: The port to listen to.
 * 
 * Return:
 * 	N/A.
 * 
 * Notes:
 * 	The program might exit at multiple instances due to
 * 	vital functions' failure.
 **/

Server::Server(const std::string &port):
	_users(std::map<int, int>()),
	_current_id(0)
{
	check_port_range(port);
	int	opt = true;
	_main_socket = socket(AF_INET , SOCK_STREAM , 0);
	if (_main_socket == -1)
	{
		std::cout << "Failed to create socket. errno: " << errno << std::endl;
		exit(EXIT_FAILURE);
	}

	if( setsockopt(_main_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt,
		sizeof(opt)) < 0 )
	{
		std::cout << "Setsockopt failed. errno: " << errno << std::endl;
		exit(EXIT_FAILURE);
	}

	_address.sin_family = AF_INET;
	_address.sin_addr.s_addr = INADDR_ANY;
	_address.sin_port = htons(std::atoi(port.c_str()));
	if (bind(_main_socket, (struct sockaddr*)&_address, sizeof(_address)) < 0)
	{
		// Port is unavaible
		std::cout << "Failed to bind to port. errno: " << errno << std::endl;
		exit(EXIT_FAILURE);
	}

	if (listen(_main_socket, 3) < 0)
	{
		std::cout << "Failed to listen on socket. errno: " << errno << std::endl;
		exit(EXIT_FAILURE);
	}
}

Server::Server(const Server &other)
{
	*this = other;
}

Server::~Server()
{
	// Don't leak fds
	close(_main_socket);
}

/**
* Description:
* 	Returns the current id available for user creation.
* 
* Args:
* 	None.
* 
* Return:
* 	The current id.
* 
* Notes:
* 	** Notes **
**/


std::size_t const	&Server::get_current_id() const
{
	return (_current_id);
}

/**
* Description:
* 	Sends a message to a client.
* 
* Args:
* 	msg: The message to send.
* 	client_fd: The fd of the corresponding client.
* 
* Return:
* 	None.
* 
* Notes:
* 	** Notes **
**/

void	Server::send(const std::string &msg, const std::size_t &id)
{
	if (_users.find(id) == _users.end())
		return;

	if(::send(_users[id], msg.c_str(), msg.size(), 0) != static_cast<long>(msg.size()))
		std::cout << "Couldn't send message. errno: " << errno << std::endl;
}

/**
* Description:
* 	Receive the messages from all clients.
* 
* Args:
* 	readfds: A fd_set of all sockets connected.
* 
* Return:
* 	Returns a vector of strings containing all the messages.
* 
* Notes:
* 	The return should be a map, associocating an id with a buffer.
**/

std::map<int, std::string>	Server::receive(fd_set &readfds)
{
	int		sd;
	char	*buffer = NULL;
	size_t	valread;
	
	std::map<int, std::string>	m;

	for (std::map<int, int>::iterator it = _users.begin(); it != _users.end(); ++it) 
	{
		valread = 0;
		sd = it->second;

		if (FD_ISSET(sd, &readfds))
		{
			fcntl(sd, F_SETFL, O_NONBLOCK);
			FILE* fp = fdopen(sd, "r");
			getline(&buffer, &valread, fp);
			if (valread > 1)
				m[it->first] = buffer;
			else
			{
				close(sd);
				it->second = 0;
			}
			free(buffer);
		}
	}
	return (m);
}

/**
* Description:
* 	Adds a new connection to the server. Can be called at every
* 	occurence of the main loop.
* 
* Args:
* 	readfds: A fd_set of all sockets connected.
* 
* Return:
* 	Returns a new user.
* 
* Notes:
* 	Exits if accept fails.
**/

user	*Server::add_connection(fd_set &readfds)
{
	if (!FD_ISSET(_main_socket, &readfds))
		return NULL;

	std::size_t addrlen = sizeof(_address);
	int new_socket = accept(_main_socket,
		(struct sockaddr *)&_address, (socklen_t*)&addrlen);
	if (new_socket < 0)
	{
		std::cout << "Accept failed. errno: " << errno << std::endl;
		exit(EXIT_FAILURE);
	}
	user *usr = new user("", _current_id);
	_users[_current_id] = new_socket;
	_current_id++;
	return (usr);
}

/**
* Description:
* 	Init the select function to accept multiple connections.
* 
* Args:
* 	readfds: A fd_set of all sockets connected.
* 
* Return:
* 	None.
* 
* Notes:
* 	** Notes **
**/

void	Server::select(fd_set &readfds)
{
	FD_ZERO(&readfds);
	FD_SET(_main_socket, &readfds);
	
	int max_sd = _main_socket;
	for (std::map<int, int>::iterator it = _users.begin(); it != _users.end(); ++it)
	{
		int sd = it->second;
		if(sd > 0)
			FD_SET(sd, &readfds);
		if(sd > max_sd)
			max_sd = sd;
	}

	int activity = ::select(max_sd + 1, &readfds, NULL, NULL, NULL);
	if ((activity < 0) && (errno != EINTR))
		std::cout << "Select failed: " << errno << std::endl;
}

/**
* Description:
* 	Remove useless ids (connection over).
* 
* Args:
* 	None.
* 
* Return:
* 	None.
* 
* Notes:
* 	** Notes **
**/


void	Server::rm_useless()
{
	if (_users.size() <= 1)
		return ;
	for (std::map<int, int>::iterator it = _users.begin(); it != _users.end(); ++it)
	{
		if (it->second == 0)
			_users.erase(it->first);
	}
}

/**
* Description:
* 	Disconnect a user from the server.
* 
* Args:
* 	id: The id of the user.
* 
* Return:
* 	None.
* 
* Notes:
* 	** Notes **
**/


void	Server::disconnect(const std::size_t &id)
{
	close(_users[id]);
	_users[id] = 0;
}

void	Server::operator=(const Server &other)
{
	std::cout << "Copy assignment operator called" << std::endl;
	_users = other._users;
	_main_socket = other._main_socket;
	_address = other._address;
	_current_id = other._current_id;
}

/**
* Description:
* 	Check if given port is valid.
* 
* Args:
* 	port: The port number.
* 
* Return:
* 	None
* 
* Notes:
* 	Ports in the range 0-1023 are theoratically
* 	usable. However, they should be reserved for
* 	Unix services.
**/


void	Server::check_port_range(const std::string &port)
{
	int iport = std::atoi(port.c_str());
	if (iport < 1024 || iport > 65535)
	{
		std::cout << "The given port is invalid\nAllowed: 1024 - 65535" << std::endl;
		exit(EXIT_FAILURE);
	}
}