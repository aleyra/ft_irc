#include "cmds.hpp"

int	pass(std::string psw, user* askingOne, user* usr, Server& srv){
	if (psw.empty())
		return (numeric_reply(ERR_NEEDMOREPARAMS, askingOne, "PASS", srv));
	if (!usr->getPassword().empty())
		return (numeric_reply(ERR_ALREADYREGISTERED, askingOne, srv));
	usr->setPassword(psw);
	return (EXIT_SUCCESS);
}