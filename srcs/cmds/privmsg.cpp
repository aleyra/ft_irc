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
			recipients[*it] = receiver;
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
			std::map<unsigned int, int> chan_users = chan->getUsr_list();
			if (it->find_first_of("~&@%") != std::string::npos)
			{
				int lvl = 0;
				if (it->find("%") != std::string::npos)
					lvl = 4;
				else if (it->find("@") != std::string::npos)
					lvl = 3;
				else if (it->find("&") != std::string::npos)
					lvl = 2;
				else if (it->find("~") != std::string::npos)
					lvl = 1;
				for (std::map<unsigned int, int>::iterator it2 = chan_users.begin();
					it2 != chan_users.end(); it2++)
				{
					// if (it2->second >= lvl)
						recipients[*it] = searchUserByID(it2->first, users);
				}
			}
			else
			{
				for (std::map<unsigned int, int>::iterator it2 = chan_users.begin();
					it2 != chan_users.end(); it2++)
				{
					recipients[*it] = searchUserByID(it2->first, users);
				}
			}
		}
	}
	// Check if recipients were found
	if (recipients.empty())
		numeric_reply(ERR_NORECIPIENT, &askingOne, message, server);

	// Send messages
	for (std::map<std::string, user*>::iterator it = recipients.begin();
		it != recipients.end(); ++it)
	{
		if (it->second->getId() == askingOne.getId())
			continue;
		server.send(":" + askingOne.getNick() + "!~" + askingOne.getHistory_nick().front() + "@" + askingOne.getIp() + " "
			+ "PRIVMSG " + it->first + " :" + message, it->second->getId());
	}
}