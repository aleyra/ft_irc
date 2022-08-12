/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucille <lucille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 13:50:36 by tlafay            #+#    #+#             */
/*   Updated: 2022/08/12 15:38:46 by lucille          ###   ########.fr       */
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
#include <cerrno>

#define MAX_CLIENTS 4000

class Server
{
	public:
		Server();
		Server(std::string port, std::string pass);
		Server(const Server &f);
		~Server();

		void	connection_test();
		void	send(std::string msg, int client_fd);
		std::vector<std::string>	receive();

		void	operator=(const Server &f);
		
	private:
		int			_main_socket;
		int			_client_sockets[MAX_CLIENTS];
		fd_set		readfds;
		sockaddr_in _sockaddr;

};

#endif