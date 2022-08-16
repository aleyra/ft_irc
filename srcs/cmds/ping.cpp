#include "cmds.hpp"

void	ping(std::vector<std::string> params, user &user, Server &server)
{
	server.send("PING " + params[0] + "\n", user.getId());
}