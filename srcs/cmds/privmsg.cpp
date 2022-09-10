#include "cmds.hpp"

static void	send_msg(Server &server, std::string &message, std::string &target, user &askingOne, user &receiver)
{
	if (receiver.getId() != askingOne.getId())
		server.send(":" + askingOne.getNick() + "!"
			+ askingOne.getHistory_nick().front() + "@" + askingOne.getIp()
			+ " " + "PRIVMSG " + target + " :" + message, receiver.getId());
}

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
	(void)chan_vec;
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
			receiver->send_msg(askingOne, server, message, PRIVMSG, *it);
			sent = 1;
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
			// std::string test = "#bunny";
			chan->send(askingOne, server, users, message, PRIVMSG);

			/*****  *****/
			std::map<unsigned int, int> chan_users = chan->getUsr_list();
			if (chan_users.find(askingOne.getId()) == chan_users.end())
			{
				numeric_reply(ERR_CANNOTSENDTOCHAN, &askingOne, chan, server);
				continue;
			}
			
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
				if (chan->hasMode('m') && lvl < CHAN_OP)
					lvl = VOICE_OK;
				for (std::map<unsigned int, int>::iterator it2 = chan_users.begin();
					it2 != chan_users.end(); it2++)
				{
					std::cout << it2->second << std::endl;
					if (it2->second >= lvl)
					{
						send_msg(server, message, *it, askingOne, *searchUserByID(it2->first, users));
						sent = 1;
					}
				}

			}
			else
			{
				for (std::map<unsigned int, int>::iterator it3 = chan_users.begin();
					it3 != chan_users.end(); it3++)
				{
					if (!chan->hasMode('m') || it3->second >= VOICE_OK)
					{
						send_msg(server, message, *it, askingOne, *searchUserByID(it3->first, users));
						sent = 1;
					}
				}

			}
		}
		/***** *****/
	}
	if (!sent)
		numeric_reply(ERR_NORECIPIENT, &askingOne, message, server);
}