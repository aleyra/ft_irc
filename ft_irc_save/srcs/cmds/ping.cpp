#include "cmds.hpp"

void	ping(std::vector<std::string> params, user &user, Server &server)
{
	if (params.size() == 0)
	{
		numeric_reply(ERR_NEEDMOREPARAMS, &user, "PING", server);
		return;
	}
	server.send("PING " + params[0] + "\n", user.getId());
}