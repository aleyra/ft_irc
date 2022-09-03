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
* 	Largely untested.
**/


void	privmsg(std::vector<std::string> params, user &askingOne,
			std::vector<channel*> chan_vec,
			std::map<unsigned int, user *>& users, Server &server)
{
	if (params.size() == 0)
		numeric_reply(ERR_NOTEXTTOSEND, &askingOne, server);
	
	std::vector<user*> recipients;
	std::string	message = *(params.end() - 1);

	// Iterate all targets and stop before the message.
	for (std::vector<std::string>::iterator it = params.begin();
		it != params.end() - 1; ++it)
	{
		// Users
		if (it->find_first_of("#&!+") == std::string::npos)
		{
			user *receiver = searchUserByNick(*it, users);
			if (receiver == NULL)
			{
				numeric_reply(ERR_NOSUCHNICK, &askingOne, *it, server);
				continue;
			}
			recipients.push_back(receiver);
		}
		// Channels ~&@%
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
				for (std::map<unsigned int, int>::iterator it = chan_users.begin();
					it != chan_users.end(); it++)
				{
					if (it->second >= lvl)
						recipients.push_back(searchUserByID(it->first, users));
				}
			}
			else
			{
				for (std::map<unsigned int, int>::iterator it = chan_users.begin();
					it != chan_users.end(); it++)
				{
					recipients.push_back(searchUserByID(it->first, users));
				}
			}
		}
	}
	// Check if recipients were found
	if (recipients.empty())
		numeric_reply(ERR_NORECIPIENT, &askingOne, message, server);

	// Send messages
	for (std::vector<user*>::iterator it = recipients.begin();
		it != recipients.end(); ++it)
	{
		// server.send(":" + askingOne.getNick() + " PRIVMSG "
		// 	+ (*it)->getNick() + " :" + message, (*it)->getId());
		server.send(":" + askingOne.getNick() + "!~" + askingOne.getHistory_nick().front() + "@" + askingOne.getIp() + " "
			+ "PRIVMSG " + (*it)->getNick() + " :" + message, (*it)->getId());
	}
}