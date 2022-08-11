#include "cmds.hpp"

int	away(std::string txt, user*	usr, server* srv){
	if (txt.empty() == true){
		usr->setAway(false);
		return (numeric_reply(RPL_UNAWAY, srv));
	}

	usr->setAway(true);
	usr->setAway_msg(txt);
	return (numeric_reply(RPL_NOWAWAY, srv));
}