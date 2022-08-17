#include "tools.hpp"

/**
* Description:
* 	Execute a command.
* 
* Args:
* 	id: The id of the user executing.
* 	command: The full command + args to execute.
* 	users: The list of all users.
* 	channels: The list of all channels.
* 	server: The server to execute the command on.
* 
* Return:
* 	None.
* 
* Notes:
* 	The parsing is very simple, not tested that much.
* 	A switch or function pointers could be used in case
* 	the if/else become overwhelming.
**/


void	exec_command(const int &id, const std::string &command,
	std::map<unsigned int, user *> &users,
	std::vector<channel *> &channels,
	Server &server)
{
	std::string firstWord = command.substr(0, command.find(" "));
	std::string args = command.substr(command.find_first_of(" \t") + 1);
	if (firstWord == "NICK")
		nick(params(args), *users[id], users, server);
	else if (firstWord == "NAMES")
		names(args, channels, users, server);
	else if (firstWord == "PING")
		pong(params(args), *users[id], server);
	else if (firstWord == "QUIT")
		quit(*users[id], server);
	else if (firstWord == "OPER")
		oper(params(args), *users[id], server);

}

/**
* Description:
* 	This is where we create "full" commands to execute.
* 
* Args:
* 	msg: A map of all the messages by user id.
* 	buffers: A map of the previous unfinished commands.
* 
* Return:
* 	None.
* 
* Notes:
* 	If a buffer is sent partially and then the client disconnects,
* 	the buffer still exists in the memory. It's not a problem for such
* 	small amounts of data though.
**/

void	make_full_command(std::map<unsigned int, std::string> &msg,
	std::map<unsigned int, std::string> &buffers,
	std::map<unsigned int, user *> &users,
	std::vector<channel *> &channels,
	Server &server)
{
	for (std::map<unsigned int, std::string>::iterator it = msg.begin();
		it != msg.end(); ++it)
	{
		buffers[it->first] += it->second;
		if (users[it->first]->getIsonline())
			users[it->first]->setLast_activity();
		else
			continue;
		if (buffers[it->first].back() == '\n')
		{
			exec_command(it->first, buffers[it->first], users, channels, server);
			buffers[it->first].clear();
		}
	}
}