#include "cmds.hpp"

int	ison(std::vector<std::string> params, Server* srv){
	if (params.empty())
		return (numeric_reply(ERR_NEEDMOREPARAMS, "ISON", srv));
	//recup la liste des user online
	for(size_t i = 0; i < params.size(); ++i){
		//chercher params[0] dans la liste
		//si trouvé afficher : ??? //":*1<nick> *( " " <nick> )"
	}
	return (RPL_ISON);
}