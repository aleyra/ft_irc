#include "cmds.hpp"

void	quit(std::vector<std::string> params, user &user, Server &server)
{
	(void)params, (void)user, (void)server;
	error(user, server, "quit requested");
}

void	quit_server(user &user, Server &server, std::string msg)
{
	server.send("QUIT " + msg + "\n", user.getId());
	server.disconnect(user);
}