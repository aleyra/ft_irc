#include "cmds.hpp"

void	notice(std::vector<std::string> params, user &askingOne,
			std::vector<channel*> chan_vec,
			std::map<unsigned int, user *>& users, Server &server)
{	
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
				continue;
			recipients.push_back(receiver);
		}
		// Channels
		else
		{
			(void)chan_vec;
		}
	}

	// Send messages
	for (std::vector<user*>::iterator it = recipients.begin();
		it != recipients.end(); ++it)
	{
		server.send(":" + askingOne.getNick() + " PRIVMSG "
			+ (*it)->getNick() + " :" + message, (*it)->getId());
	}
}