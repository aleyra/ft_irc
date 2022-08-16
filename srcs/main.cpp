#include "Server.hpp"
#include "tools.hpp"
#include "channel.hpp"

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cout << "Usage: ./ircserv <port> <password>" << std::endl;
		return (1);
	}

	Server server(argv[1]);
	fd_set readfds;
	std::map<int, user *> users;
	std::vector<channel *> channels;
	std::map<int, std::string> buffers;
	while (true)
	{
		server.select(readfds);
		user *tmp = server.add_connection(readfds);
		if (tmp)
			users[tmp->getId()] = tmp;
		std::map<int, std::string> msg = server.receive(readfds);
		handle_commands(msg, buffers, users);
		server.rm_useless();
	}
	for (std::map<int, user *>::iterator it = users.begin(); it != users.end(); ++it)
	{
		delete it->second;
	}
}