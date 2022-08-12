/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafay <tlafay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 13:48:49 by tlafay            #+#    #+#             */
/*   Updated: 2022/08/12 14:36:46 by tlafay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server() {}

/**
 * Description:
 * 	The constructor that should be used. It will setup sockets
 * 	to receive further connections.
 * 
 * Args:
 *		port: The port to listen to.
 *		pass: The password to access the server.
 * 
 * Return:
 * 	N/A.
 * 
 * Notes:
 * 	** Notes **
 **/

Server::Server(const std::string &port, const std::string &pass): _current_id(0)
{
	(void)pass;

	for (int i = 0; i < MAX_CLIENTS; ++i)
		_client_sockets[i] = 0;

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
	_address.sin_port = htons(atoi(port.c_str()));
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
	close(_main_socket);
}


/**
 * This is just a useless test for now.
 **/

void	Server::connection_test()
{
	size_t addrlen = sizeof(sockaddr);
	int connection = accept(_main_socket,
		(struct sockaddr*)&_address, (socklen_t*)&addrlen);
	if (connection < 0)
	{
		std::cout << "Failed to grab connection. errno: " << errno << std::endl;
		exit(EXIT_FAILURE);
	}

	char buffer[100];
	size_t bytesRead = read(connection, buffer, 100);
	(void)bytesRead;
	std::cout << "The message was: " << buffer;

	std::string response = "Good talking to you\n";
	send(response, connection);
	close(connection);
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

void	Server::send(const std::string &msg, const int &client_fd)
{
	if(::send(client_fd, msg.c_str(), msg.size(), 0) != static_cast<long>(msg.size()))
		std::cout << "Couldn't send message. errno: " << errno << std::endl;
}

/**
* Description:
* 	Receive the messages from all clients.
* 
* Args:
* 	None.
* 
* Return:
* 	Returns a vector of strings containing all the messages.
* 
* Notes:
* 	The return should be a map, associocating an id with a buffer.
**/

std::vector<std::string>	Server::receive(fd_set &readfds)
{
	int		sd;
	char	*buffer = NULL;
	size_t	valread;
	
	std::vector<std::string>	v;

	for (int i = 0; i < MAX_CLIENTS; i++) 
	{
		valread = 0;
		sd = _client_sockets[i];

		if (FD_ISSET(sd, &readfds))
		{
			fcntl(sd, F_SETFL, O_NONBLOCK);
			FILE* fp = fdopen(sd, "r");
			getline(&buffer, &valread, fp);
			if (valread > 1)
			{
				v.push_back(buffer);
				send(buffer, sd);
				free(buffer);
			}
			else
			{
				close(sd);
				_client_sockets[i] = 0;
			}
		}
	}
	return (v);
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
* 	None.
* 
* Notes:
* 	Exits if accept fails.
**/

void	Server::add_connection(fd_set &readfds)
{
	if (!FD_ISSET(_main_socket, &readfds))
		return;

	std::size_t addrlen = sizeof(_address);
	int new_socket = accept(_main_socket,
		(struct sockaddr *)&_address, (socklen_t*)&addrlen);
	if (new_socket < 0)
	{
		std::cout << "Accept failed. errno: " << errno << std::endl;
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < MAX_CLIENTS; i++)
	{
		if(_client_sockets[i] == 0)
		{
			_client_sockets[i] = new_socket;
			break;
		}
	}
	_current_id++;
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
	for (int i = 0 ; i < MAX_CLIENTS ; i++)
	{
		int sd = _client_sockets[i];
		if(sd > 0)
			FD_SET(sd, &readfds);
		if(sd > max_sd)
			max_sd = sd;
	}

	int activity = ::select(max_sd + 1, &readfds, NULL, NULL, NULL);
	if ((activity < 0) && (errno != EINTR))
		std::cout << "Select failed: " << errno << std::endl;
}

void	Server::operator=(const Server &other)
{
	std::cout << "Copy assignment operator called" << std::endl;
	(void)other;
}
