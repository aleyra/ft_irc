/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucille <lucille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 13:50:36 by tlafay            #+#    #+#             */
/*   Updated: 2022/08/12 15:44:52 by lucille          ###   ########.fr       */
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
#include <arpa/inet.h>
#include <cerrno>

#define MAX_CLIENTS 30

class Server
{
	public:
		Server(const std::string &port, const std::string &pass);
		Server(const Server &f);
		~Server();

		void						connection_test();
		void						send(const std::string &msg, const int &client_fd);
		std::vector<std::string>	receive(fd_set &readfds);
		void						add_connection(fd_set &readfds);
		void						select(fd_set &readfds);

		void	operator=(const Server &f);
		
	private:
		int			_main_socket;
		int			_client_sockets[MAX_CLIENTS];
		sockaddr_in _address;

		Server();
};

#endif