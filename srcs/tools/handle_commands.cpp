#include <iostream>
#include <map>

void	exec_command(std::string &buffer)
{
	std::cout << buffer;
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
**/


void	handle_commands(std::map<int, std::string> &msg, std::map<int, std::string> &buffers)
{
	for (std::map<int, std::string>::iterator it = msg.begin(); it != msg.end(); ++it)
	{
		buffers[it->first] += it->second;
		if (buffers[it->first].back() == '\n')
		{
			std::cout << it->first << "=>";
			exec_command(buffers[it->first]);
			buffers[it->first].clear();
		}
	}
}