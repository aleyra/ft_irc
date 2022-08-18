#include "cmds.hpp"

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
			(void)chan_vec;
		}
	}
	// Check if recipients were found
	if (recipients.empty())
		numeric_reply(ERR_NORECIPIENT, &askingOne, message, server);

	// Send messages
	for (std::vector<user*>::iterator it = recipients.begin();
		it != recipients.end(); ++it)
	{
		server.send(":" + askingOne.getNick() + " PRIVMSG "
			+ (*it)->getNick() + " :" + message, (*it)->getId());
	}
}