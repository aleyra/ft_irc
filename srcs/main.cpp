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
	std::map<unsigned int, user *> users;
	std::vector<channel *> channels;
	std::map<unsigned int, std::string> buffers;
	while (true)
	{
		server.select();
		user *tmp = server.add_connection();
		if (tmp)
			users[tmp->getId()] = tmp;
		std::map<unsigned int, std::string> msg = server.receive(users);
		timeout(users, server);
		if (make_full_command(msg, buffers, users, channels, server, argv[2]) == 1)
			break;
	}

	// It's a "good practice" but useless since we never exit the loop anyway.
	for (std::map<unsigned int, user *>::iterator it = users.begin(); it != users.end(); ++it)
	{
		delete it->second;
	}
	for (std::vector<channel *>::iterator it = channels.begin(); it != channels.end(); ++it)
	{
		delete *it;
	}
}