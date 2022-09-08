#include "cmds.hpp"

// static void	send_msg(Server &server, std::string &message, std::string &target, user &askingOne, user &receiver)
// {
// 	if (receiver.getId() != askingOne.getId())
// 		server.send(":" + askingOne.getNick() + "!"
// 			+ askingOne.getHistory_nick().front() + "@" + askingOne.getIp()
// 			+ " " + "PRIVMSG " + target + " :" + message, receiver.getId());
// }

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
			send_msg(server, message, *it, askingOne, *receiver);
		}
		// Channels
		else
		{
			channel *chan = searchChannelByName(*it ,chan_vec);
			if (chan == NULL)
				continue;
			std::map<unsigned int, int> chan_users = chan->getUsr_list();
			if (chan_users.find(askingOne.getId()) == chan_users.end())
				continue;
			
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
					if (it2->second >= lvl)
						send_msg(server, message, *it, askingOne, *searchUserByID(it2->first, users));
				}

			}
			else
			{
				for (std::map<unsigned int, int>::iterator it3 = chan_users.begin();
					it3 != chan_users.end(); it3++)
					send_msg(server, message, *it, askingOne, *searchUserByID(it3->first, users));

			}
		}
	}
}
