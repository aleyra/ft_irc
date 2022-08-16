#include "tools.hpp"

void	timeout(std::map<int, user *> &users, Server &server)
{
	for (std::map<int, user *>::iterator it = users.begin(); it != users.end(); ++it)
		{
			if (users[it->first]->getIsonline() && users[it->first]->check_Idle_time() > 10)
			{
				server.disconnect(it->first);
				users[it->first]->setIsonline(false);
			}
		}
}