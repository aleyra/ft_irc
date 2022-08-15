/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafay <tlafay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 11:25:23 by tlafay            #+#    #+#             */
/*   Updated: 2022/08/15 11:15:10 by tlafay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cout << "Usage: ./ircserv <port> <password>" << std::endl;
		return (1);
	}

	Server server(argv[1], argv[2]);
	fd_set readfds;	
	while (true)
	{
		server.rm_useless();
		server.select(readfds);
		server.add_connection(readfds);
		std::vector<std::string> v = server.receive(readfds);
		for (std::vector<std::string>::iterator it = v.begin(); it != v.end(); ++it)
		{
			std::cout << *it;
		}
	}
}