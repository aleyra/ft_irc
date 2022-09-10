#include "tools.hpp"

int	channel::send(user &askingOne, Server &server,
		std::map<unsigned int, user *> &users, std::string &message, int type)
	{
		if (!this->hasMode('n') && _usr_list.find(askingOne.getId()) == _usr_list.end())
		{
			numeric_reply(ERR_CANNOTSENDTOCHAN, &askingOne, this, server);
			return (0);
		}
		int sent = 0;
		for (std::map<unsigned int, int>::iterator it = _usr_list.begin();
			it != _usr_list.end(); ++it)
		{
			if (!this->hasMode('m') || (this->hasMode('m') && _usr_list.at(askingOne.getId()) >= VOICE_OK))
			{
				sent = searchUserByID(it->first, users)->send_msg(askingOne,
					server, message, type, this->getName());
			}
			else
			{
				if (type == PRIVMSG)
					numeric_reply(ERR_CANNOTSENDTOCHAN, &askingOne, this, server);
				break;
			}
		}
		return (sent);
	}