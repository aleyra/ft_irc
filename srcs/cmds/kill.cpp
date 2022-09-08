#include "cmds.hpp"

int	kill(std::vector<std::string> params, user* askingOne,
	std::map<unsigned int, user *>& users, std::vector<channel*> chan_vec,
	Server &srv){
	if (askingOne->getLvl() != SRV_OP)
		return (numeric_reply(ERR_NOPRIVILEGES, askingOne, srv));
	if (params.size() < 2)
		return (numeric_reply(ERR_NEEDMOREPARAMS, askingOne, "KILL", srv));
	user*	usr = NULL;
	usr = searchUserByNick(params[0], users);
	if (usr == NULL)
		return (numeric_reply(ERR_NOSUCHNICK, askingOne, params[0], srv));
	params.erase(params.begin());
	quit(params, *usr, chan_vec, srv, users);
	return (EXIT_SUCCESS);
}