#include "cmds.hpp"

/**
* Description:
* 	Send a message to a user or a channel.
* 
* Args:
* 	Don't be lazy and go look out for other files!
* 	I'm the one allowed to be lazy.
* 
* Return:
* 	None.
* 
* Notes:
* 	Largely untested.
**/

void	privmsg(std::vector<std::string> params, user &askingOne,
			std::vector<channel*> chan_vec,
			std::map<unsigned int, user *>& users, Server &server)
{
	std::string message = concat(params);
	int sent = 0;

	if (message.find(':') == std::string::npos)
	{
		numeric_reply(ERR_NOTEXTTOSEND, &askingOne, server);
		return;
	}

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
			{
				numeric_reply(ERR_NOSUCHNICK, &askingOne, *it, server);
				continue;
			}
			sent = receiver->send_msg(askingOne, server, message, PRIVMSG, *it);
		}
		// Channels
		else
		{
			
			channel *chan = searchChannelByName(*it ,chan_vec);
			if (chan == NULL)
			{
				numeric_reply(ERR_NOSUCHCHANNEL, &askingOne, *it, server);
				continue;
			}
			sent = chan->send(askingOne, server, users, message, PRIVMSG);
		}
	}
	if (!sent)
		numeric_reply(ERR_NORECIPIENT, &askingOne, message, server);
}