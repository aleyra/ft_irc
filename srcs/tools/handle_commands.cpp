#include <iostream>
#include <map>
#include "tools.hpp"

void	exec_command(std::pair<int, std::string> &command)
{
	std::cout << command.second;
	// std::string firstWord = command.second.substr(0, command.second.find(" "));
	// std::string args = command.second.substr(command.second.find_first_of(" \t") + 1);
	// std::cout << "The first word is: " << firstWord << std::endl;
	// std::cout << "The args are: " << args << std::endl;
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
* 	Maybe a better name ?
* 	If a buffer is sent partially and then the client disconnects,
* 	the buffer still exists in the memory. It's not a problem for such
* 	small amounts of data though.
**/

void	handle_commands(std::map<int, std::string> &msg,
	std::map<int, std::string> &buffers,
	std::map<int, user *> users)
{
	(void)users;
	for (std::map<int, std::string>::iterator it = msg.begin(); it != msg.end(); ++it)
	{
		buffers[it->first] += it->second;
		if (users[it->first]->getIsonline())
			users[it->first]->setLast_activity();
		else
			continue;
		if (buffers[it->first].back() == '\n')
		{
			std::cout << it->first << "=>";
			std::pair<int, std::string> pair(it->first, buffers[it->first]);
			exec_command(pair);
			buffers[it->first].clear();
		}
	}
}