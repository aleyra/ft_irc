#include "cmds.hpp"

/**
* Description:
* 	Send a message to a user or a channel.
* 
* Args:
* 	Lazy.
* 
* Return:
* 	None.
* 
* Notes:
* 	Basically the same as privmsg but without
* 	sending numeric replies.
**/

void	notice(std::vector<std::string> params, user &askingOne,
			std::vector<channel*> chan_vec,
			std::map<unsigned int, user *>& users, Server &server)
{
	std::string message = concat(params);
	int sent = 0;

	if (message.find(':') == std::string::npos)
		return;

	message = message.substr(message.find(':') + 1);
	std::map<std::string, user*> recipients;
	for (std::vector<std::string>::iterator it = params.begin();
		it != params.end(); ++it)
	{
		if (it->find(':') != std::string::npos)
			break;
		// Users
		if (it->find_first_of("#&!+") == std::string::npos)
		{
			user *receiver = searchUserByNick(*it, users);
			if (receiver == NULL)
				continue;
			receiver->send_msg(askingOne, server, message, PRIVMSG, *it);
			sent = 1;
		}
		// Channels
		else
		{
			channel *chan = searchChannelByName(*it ,chan_vec);
			if (chan == NULL)
				continue;
			chan->send(askingOne, server, users, message, PRIVMSG);
		}
	}
}
