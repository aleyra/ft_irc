#include "cmds.hpp"

int	pass(std::string psw, user* usr, Server* srv){
	if (psw.empty())
		return (numeric_reply(ERR_NEEDMOREPARAMS, "PASS", srv));
	if (!usr->getPassword().empty())
		return (numeric_reply(ERR_ALREADYREGISTERED, srv));
	usr->setPassword(psw);
	return (EXIT_SUCCESS);
}