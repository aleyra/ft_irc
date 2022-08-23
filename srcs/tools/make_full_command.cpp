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
* 	password: The connection password required by the server.
* 
* Return:
* 	None.
* 
* Notes:
* 	The parsing is fairly simple, not tested that much.
* 	A switch or function pointers could be used in case
* 	the if/else becomes overwhelming.
**/


void	exec_command(const int &id, const std::string &command,
	std::map<unsigned int, user *> &users,
	std::vector<channel *> &channels,
	Server &server, std::string password)
{
	std::string firstWord = command.substr(0, command.find_first_of(" "));
	std::string args = command.substr(command.find_first_of(" \t\n") + 1);
	firstWord.erase(remove(firstWord.begin(), firstWord.end(), '\n'), firstWord.end());

	std::cout << firstWord << " " << args;

	if (!users[id]->getHasConnected())
	{
		if (firstWord == "PASS")
			pass(params(args), *users[id], server, password);
		return;
	}

	// std::cout << "coucou" << std::endl;//

	if (firstWord == "NICK")
		nick(params(args), users[id], users, server);
	else if (firstWord == "USER")
		user_cmd(params(args), users[id], server);
	else if (firstWord == "PASS")
			pass(params(args), *users[id], server, password);
	else if (firstWord == "INVITE" && users[id]->getFirstNickGiven() == true
		&& !users[id]->getTruename().empty())
		invite(params(args), users[id], users, channels, server);
	else if (firstWord == "JOIN" && users[id]->getFirstNickGiven() == true
		&& !users[id]->getTruename().empty())
		join(args, users[id], channels, users, server);
	else if (firstWord == "KICK" && users[id]->getFirstNickGiven() == true
		&& !users[id]->getTruename().empty())
		kick(params(args), users[id], channels, users, server);
	else if (firstWord == "LIST" && users[id]->getFirstNickGiven() == true
		&& !users[id]->getTruename().empty())
		list(args, users[id], channels, users, server);
	else if (firstWord == "MODE" && users[id]->getFirstNickGiven() == true
		&& !users[id]->getTruename().empty())
		mode(params(args), users[id], channels, users, server);
	else if (firstWord == "NAMES" && users[id]->getFirstNickGiven() == true
		&& !users[id]->getTruename().empty())
		names(args, users[id], channels, users, server);
	else if (firstWord == "OPER" && users[id]->getFirstNickGiven() == true
		&& !users[id]->getTruename().empty())
		oper(params(args), *users[id], server);
	else if (firstWord == "PART" && users[id]->getFirstNickGiven() == true
		&& !users[id]->getTruename().empty())
		part(params(args), users[id], channels, server);
	else if (firstWord == "PING" && users[id]->getFirstNickGiven() == true
		&& !users[id]->getTruename().empty())
		pong(params(args), *users[id], server);
	else if (firstWord == "TOPIC" && users[id]->getFirstNickGiven() == true
		&& !users[id]->getTruename().empty())
		topic(params(args), users[id], channels, server);
	else if (firstWord == "QUIT" && users[id]->getFirstNickGiven() == true
		&& !users[id]->getTruename().empty())
		quit(params(args), *users[id], channels, server);
	else if (firstWord == "NOTICE" && users[id]->getFirstNickGiven() == true
		&& !users[id]->getTruename().empty())
		notice(params(args), *users[id], channels, users, server);
	else if (firstWord == "PRIVMSG" && users[id]->getFirstNickGiven() == true
		&& !users[id]->getTruename().empty())
		privmsg(params(args), *users[id], channels, users, server);
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
	Server &server, std::string password)
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
			exec_command(it->first, buffers[it->first],
				users, channels, server, password);
			buffers[it->first].clear();
		}
	}
}