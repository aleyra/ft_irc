#ifndef SERVER_HPP
# define SERVER_HPP

#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <map>
#include <string>
#include <fcntl.h>
#include <cerrno>
#include <fstream>
#include <sys/types.h>
#include <arpa/inet.h>
#include "user.hpp"

#define MAX_CLIENTS 4000

class user;

class Server
{
	public:
		Server(const std::string &port);
		Server(const Server &f);
		~Server();

		std::size_t const	&get_current_id() const;

		void						send(const std::string &msg, const std::size_t &id);
		std::map<unsigned int,
		std::string>				receive(std::map<unsigned int, user *> &users);
		user						*add_connection();
		void						select();
		void						disconnect(user &askingOne,
			std::map<unsigned int, user *>& users);
		std::string					client_ip(unsigned int id);

		void	operator=(const Server &f);
		
	private:
		// A map of ids, with a socket associated.
		std::map<unsigned int, int>	_users;
		
		// The socket that handles all connections.
		int					_main_socket;
		
		// A thing used to get addresses.
		sockaddr_in 		_address;

		// The fd_set to read fds.
		fd_set				readfds;

		// The fd_set to write on fds.
		fd_set				writefds;

		// The id of the next user.
		std::size_t			_current_id;
		
		// A list of user ips.
		std::map<unsigned int, std::string> _ips;

		// A map of buffers to send.
		std::map<unsigned int, std::string> to_send;

		void	check_port_range(const std::string &port);
		void	set_oper();

		Server();
};

#endif