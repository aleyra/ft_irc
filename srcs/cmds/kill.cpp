#include "cmds.hpp"

int	kill(std::vector<std::string> params, user* askingOne,
	std::map<unsigned int, user *>& users, Server &srv){
	if (askingOne->getLvl() != SRV_OP)
		return (numeric_reply(ERR_NOPRIVILEGES, askingOne, srv));
	
	return (EXIT_SUCCESS);
}