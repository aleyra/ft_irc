#include "cmds.hpp"

void	error(user &askingOne, Server &server, const std::string &msg)
{
	// server.send("ERROR " + msg, askingOne.getId());
	server.send(":" + askingOne.getNick() + "!~" + askingOne.getHistory_nick().front() + "@" + askingOne.getIp() + " " + "ERROR " + msg, askingOne.getId());
	server.disconnect(askingOne);
}