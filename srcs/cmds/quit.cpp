#include "cmds.hpp"

void	quit(std::vector<std::string> params, user &askingOne,
	std::vector<channel*> chan_vec, Server &server)
{
	std::string reason = (params.size() == 0) ? "" : params[0];
	for (std::vector<channel *>::iterator it = chan_vec.begin();
		it != chan_vec.end(); ++it)
	{
		if ((*it)->getUsr_list().count(askingOne.getId()))
			(*it)->send(server, ":" + askingOne.getNick() + "!~" + askingOne.getHistory_nick().front()
				+ "@" + askingOne.getIp() + " " + "QUIT " + askingOne.getNick() + ": " + reason);
	}
	error(askingOne, server, "quit requested");

}

void	quit_server(user &user, Server &server, std::string msg)
{
	if (!user.getIsonline())
		return;
	
	server.send(":" + user.getNick() + "!~" + user.getHistory_nick().front() +
		"@" + user.getIp() + " " + "QUIT " + msg, user.getId());
	server.disconnect(user);
}