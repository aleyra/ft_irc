#include "Server.hpp"
#include "tools.hpp"

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cout << "Usage: ./ircserv <port> <password>" << std::endl;
		return (1);
	}

	Server server(argv[1], argv[2]);
	fd_set readfds;
	std::vector<user *> users;
	std::map<int, std::string> buffers;
	while (true)
	{
		server.select(readfds);
		user *tmp = server.add_connection(readfds);
		if (tmp)
			users.push_back(tmp);
		std::map<int, std::string> msg = server.receive(readfds);
		handle_commands(msg, buffers);
		// for (std::map<int, std::string>::iterator it = msg.begin(); it != msg.end(); ++it)
		// 	std::cout << it->first << "=>" << it->second;
		server.rm_useless();
	}
	for (std::vector<user *>::iterator it = users.begin(); it != users.end(); ++it)
	{
		delete *it;
	}
}