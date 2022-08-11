/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lburnet <lburnet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 13:48:49 by tlafay            #+#    #+#             */
/*   Updated: 2022/08/11 14:40:51 by lburnet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server() {}

/**
 * The constructor that should be used. It will setup sockets
 * to receive further connections.
 * 
 * Args:
 *		port: The port to listen to
 *		pass: The password to access the server
 **/

Server::Server(std::string port, std::string pass)
{
	(void)pass;

	for (int i = 0; i < MAX_CLIENTS; ++i)
	{
		_client_sockets[i] = 0;
	}

	int	opt = 1;
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

	_sockaddr.sin_family = AF_INET;
	_sockaddr.sin_addr.s_addr = INADDR_ANY;
	_sockaddr.sin_port = htons(atoi(port.c_str()));
	if (bind(_main_socket, (struct sockaddr*)&_sockaddr, sizeof(_sockaddr)) < 0)
	{
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
 * This is just a useless test for now
 **/

void	Server::connection_test()
{

  // Grab a connection from the queue
	size_t addrlen = sizeof(sockaddr);
	int connection = accept(_main_socket,
		(struct sockaddr*)&_sockaddr, (socklen_t*)&addrlen);
	if (connection < 0)
	{
		std::cout << "Failed to grab connection. errno: " << errno << std::endl;
		exit(EXIT_FAILURE);
	}

  // Read from the connection
	char buffer[100];
	size_t bytesRead = read(connection, buffer, 100);
	(void)bytesRead;
	std::cout << "The message was: " << buffer;

  // Send a message to the connection
	std::string response = "Good talking to you\n";
	send(response, connection);

  // Close the connections
	close(connection);
}

/**
* 
* Sends a message to a client
* 
* Args:
* 	msg: The message to send
* 	client_fd: The fd of the corresponding client
* 
* ** Notes **
* 
**/


void	Server::send(std::string msg, int client_fd)
{
	if(::send(client_fd, msg.c_str(), msg.size(), 0) != static_cast<long>(msg.size()))
	{
		std::cout << "Couldn't send message. errno: " << errno << std::endl;
	}
}

/**
 * Used to receive a message
 * 
 * Notes : I need to make a kind of gnl to fully read messages, plus
 * 	I should probably create a map instead of a vector to return the
 * 	index of the socket.
 **/

std::vector<std::string>	Server::receive()
{
	int sd;
	char	buffer[1024];
	int	valread;
	std::vector<std::string> v;

	for (int i = 0; i < MAX_CLIENTS; i++) 
	{
		sd = _client_sockets[i];

		if (FD_ISSET( sd , &readfds))
		{
			if ((valread = read( sd , buffer, 1024)))
			{
				buffer[valread] = '\0';
				v.push_back(buffer);
			}
		}
		else
		{
			close(sd);
			_client_sockets[i] = 0;
		}
	}
	return (v);
}

void	Server::operator=(const Server &other)
{
	std::cout << "Copy assignment operator called" << std::endl;
	(void)other;
}
