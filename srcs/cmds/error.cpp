#include "cmds.hpp"

void	error(user &user, Server &server, const std::string &msg)
{
	server.send("ERROR " + msg + "\n", user.getId());
	server.disconnect(user);
}