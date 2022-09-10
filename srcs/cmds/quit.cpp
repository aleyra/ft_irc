#include "cmds.hpp"

void	quit(std::vector<std::string> params, user &askingOne,
	std::vector<channel*> chan_vec, Server &server,
	std::map<unsigned int, user *>& users)
{
	std::string reason = (params.size() == 0) ? "" : params[0];
	for (std::vector<channel *>::iterator it = chan_vec.begin();
		it != chan_vec.end(); ++it)
	{
		std::map<unsigned int, int> usr_list = (*it)->getUsr_list();
		if ((*it)->getUsr_list().count(askingOne.getId()))
			(*it)->send(server, ":" + askingOne.getNick() + "!" + askingOne.getHistory_nick().front()
				+ "@" + askingOne.getIp() + " " + "QUIT " + askingOne.getNick() + ": " + reason);
		if (usr_list.at(askingOne.getId()) <= CHAN_OP)
			(*it)->rm1toNbChanOp();
		askingOne.rmList_chan((*it));
		(*it)->rmUsr_list(&askingOne);
	}
	error(askingOne, server, "quit requested", users);

}

void	quit_server(user &askingOne, Server &server, std::string msg,
	std::map<unsigned int, user *>& users)
{
	if (!askingOne.getIsonline())
		return;
	
	server.send(":" + askingOne.getNick() + "!" + askingOne.getHistory_nick().front() +
		"@" + askingOne.getIp() + " " + "QUIT " + msg, askingOne.getId());
	server.disconnect(askingOne, users);
}