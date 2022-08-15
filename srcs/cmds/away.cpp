#include "cmds.hpp"

int	away(std::string txt, user*	usr, Server* srv){
	if (txt.empty() == true){
		usr->setIsaway(false);
		return (numeric_reply(RPL_UNAWAY, srv));
	}
	usr->setIsaway(true);
	usr->setIsaway_msg(txt);
	return (numeric_reply(RPL_NOWAWAY, srv));
}