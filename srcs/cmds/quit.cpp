#include "cmds.hpp"

void	quit(user &user, Server &server)
{
	error(user, server, "quit requested");
}

void	quit_server(user &user, Server &server, std::string msg)
{
	if (!user.getIsonline())
		return;
	
	server.send("QUIT " + msg, user.getId());
	server.disconnect(user);
}