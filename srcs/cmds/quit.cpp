#include "cmds.hpp"

void	quit(std::vector<std::string> params, user &askingOne,
	std::vector<channel*> chan_vec, Server &server)
{
	for (std::vector<channel *>::iterator it = chan_vec.begin();
		it != chan_vec.end(); ++it)
	{
		if ((*it)->getUsr_list().count(askingOne.getId()))
			(*it)->send(server, "QUIT " + askingOne.getNick() + ": " + params[0]);
	}
	error(askingOne, server, "quit requested");

}

void	quit_server(user &user, Server &server, std::string msg)
{
	if (!user.getIsonline())
		return;
	
	server.send("QUIT " + msg, user.getId());
	server.disconnect(user);
}