/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafay <tlafay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 13:50:36 by tlafay            #+#    #+#             */
/*   Updated: 2022/08/15 14:20:37 by tlafay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

#include "user.hpp"

#define MAX_CLIENTS 4000

class Server
{
	public:
		Server(const std::string &port, const std::string &pass);
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
		int					_main_socket;
		sockaddr_in _address;
		std::size_t	_current_id;

		void	check_port_range(const std::string &port);

		Server();
};


#endif