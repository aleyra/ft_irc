#include "cmds.hpp"

void	pong(std::vector<std::string> params, user &user, Server &server)
{
	server.send("PONG ft_irc " + params[0] + "\n", user.getId());
}