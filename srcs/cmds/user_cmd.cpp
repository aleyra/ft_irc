#include "cmds.hpp"

int	user_cmd(std::vector<std::string> params, user* usr, std::map<unsigned int, user *>& users, Server& srv){//<user> <mode> <unused> <realname>
	if (params.size() < 4)
		return (numeric_reply(ERR_NEEDMOREPARAMS, usr, "USER",srv));
	if (!usr->getTruename().empty())
		return (numeric_reply(ERR_ALREADYREGISTERED, usr, srv));
	for (size_t i = 0; i < params[1].size(); ++i){//case where mode is not a positive number
		if (!std::isdigit(params[1][i]))
			params[1] = "0";
	}
	usr->setUsername(params[0]);
	int	mode = std::atoi(params[1].c_str());
	if (mode >= 8)
		usr->addMode('i');
	else if (mode >= 4)
		usr->addMode('w');
	if (params[3][0] == ':')
		params[3].erase(0, 1);
	for(size_t i = 4; i < params.size(); ++i){
		params[3].append(" ");
		params[3].append(params[i]);
	}
	for (std::map<unsigned int, user *>::iterator it = users.begin(); it != users.end(); ++it){
		if (it->second->getTruename().compare(params[3]) == 0)
			return(numeric_reply(ERR_ALREADYREGISTERED, usr, srv));
	}
	usr->setTruename(params[3]);
	return (EXIT_SUCCESS);
}