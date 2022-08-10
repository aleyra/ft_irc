/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafay <tlafay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 13:48:49 by tlafay            #+#    #+#             */
/*   Updated: 2022/08/10 15:42:46 by tlafay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server()
{
	std::cout << "Default constructor called" << std::endl;
}

/**
 *	Args:
 *		port: The port to listen to
 *		pass: The password to access the server
 **/

Server::Server(char *port, char *pass)
{
	(void)pass;
	struct addrinfo hints;
	struct addrinfo *res;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC; 
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	getaddrinfo("127.0.0.1", port, &hints, &res);
	freeaddrinfo(res);
	_sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	if (_sockfd == -1) {
		std::cout << "Failed to create socket. errno: " << errno << std::endl;
		exit(EXIT_FAILURE);
	}

	_sockaddr.sin_family = AF_INET;
	_sockaddr.sin_addr.s_addr = INADDR_ANY;
	_sockaddr.sin_port = htons(atoi(port)); // htons is necessary to convert a number to
	                                 // network byte order
	if (bind(_sockfd, (struct sockaddr*)&_sockaddr, sizeof(_sockaddr)) < 0) {
		std::cout << "Failed to bind to port. errno: " << errno << std::endl;
		exit(EXIT_FAILURE);
	}
}

Server::Server(const Server &other)
{
	*this = other;
}

Server::~Server()
{
	close(_sockfd);
}


/**
 * This is just a useless test for now
 **/

void	Server::connection_test()
{
	if (listen(_sockfd, 10) < 0) {
		std::cout << "Failed to listen on socket. errno: " << errno << std::endl;
		exit(EXIT_FAILURE);
	}

  // Grab a connection from the queue
	size_t addrlen = sizeof(sockaddr);
	int connection = accept(_sockfd, (struct sockaddr*)&_sockaddr, (socklen_t*)&addrlen);
	if (connection < 0) {
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
	send(connection, response.c_str(), response.size(), 0);

  // Close the connections
	close(connection);
}

void	Server::operator=(const Server &other)
{
	std::cout << "Copy assignment operator called" << std::endl;
	(void)other;
}
