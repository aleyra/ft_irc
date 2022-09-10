#include "tools.hpp"

int	channel::send(user &askingOne, Server &server,
		std::map<unsigned int, user *> &users, std::string &message, int type)
	{
		if (_usr_list.find(askingOne.getId()) == _usr_list.end())
		{
			numeric_reply(ERR_CANNOTSENDTOCHAN, &askingOne, this, server);
			return (0);
		}
		int sent = 0;
		for (std::map<unsigned int, int>::iterator it = _usr_list.begin();
			it != _usr_list.end(); ++it)
		{
			if (type == PRIVMSG)
			{
				if (!this->hasMode('m') || (this->hasMode('m') && _usr_list.at(askingOne.getId()) >= VOICE_OK))
				{
					sent = searchUserByID(it->first, users)->send_msg(askingOne,
						server, message, type, this->getName());
				}
				else
				{
					numeric_reply(ERR_CANNOTSENDTOCHAN, &askingOne, this, server);
					break;
				}
			}
			else if (this->hasMode('n'))
			{
				sent = searchUserByID(it->first, users)->send_msg(askingOne,
						server, message, type, this->getName());
			}
		}
		return (sent);
	}