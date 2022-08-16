#ifndef SERVER_HPP
# define SERVER_HPP

#include <sys/socket.h>
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
#include "user.hpp"

#define MAX_CLIENTS 4000

class Server
{
	public:
		Server(const std::string &port);
		Server(const Server &f);
		~Server();

		std::size_t const	&get_current_id() const;

		void						send(const std::string &msg, const std::size_t &id);
		std::map<int, std::string>	receive(fd_set &readfds);
		user						*add_connection(fd_set &readfds);
		void						select(fd_set &readfds);
		void						rm_useless();
		void						disconnect(const std::size_t &id);

		void	operator=(const Server &f);
		
	private:
		// A map of ids, with a socket associated.
		std::map<int, int>	_users;
		// The socket that handles all connections.
		int					_main_socket;
		// A thing used to get addresses.
		sockaddr_in 		_address;
		// The id of the next user.
		std::size_t			_current_id;

		void	check_port_range(const std::string &port);

		Server();
};


#endif