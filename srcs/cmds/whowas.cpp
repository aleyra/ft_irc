#include "cmds.hpp"

int whowas(std::vector<std::string> params, server* srv){
	if (params.empty())
		return (numeric_reply(ERR_NEEDMOREPARAMS, "whowas", srv));//ou return (numeric_reply(ERR_NONICKNAMEGIVEN, srv));

	//transform params to a string and eventually an int
	if (params.size() > 2)
		return (EXIT_FAILURE);
	std::string	mask = params[0];
	int			count = 0;
	if (params.size() == 2)
		count = std::atoi(params[1].c_str());

	//from string to user*
	std::vector<user*>		usr = findInAllUser(mask);//chercher un nickname correspondant dans la liste des user OFFLINE ou ONLINE old nick
	
	//if no such mask
	if (usr[0] == NULL){
		numeric_reply(ERR_WASNOSUCHNICK, mask);
		return (numeric_reply(RPL_ENDOFWHOWAS, srv));
	}
	
	//else
	if (count <= 0){
		for (int i = 0; i < usr.size(); ++i){
			//RPL_WHOWASUSER
			std::cout << srv->client << " " << mask << " " << usr[i]->getUsername() << " "
				<< srv->host << " * :" << usr[i]->getTruename() << std::endl;
			if (isOnline(usr[i]) == true){//verifie si un usr is ONLINE ou OFFLINE
				//RPL_WHOISACTUALLY
				std::cout << srv->client << " " << usr[i]->getNick() << " " << srv->host << " :is actually using host" << std::endl;
			}
			std::cout << srv->client << " " << usr[i]->getNick() << " " << srv << " :" << srv->info << std::endl;//RPL_WHOISSERVER
		}
	}
	else
		for (int i = 0; i < usr.size() && i < count; ++i){
			//RPL_WHOWASUSER
			std::cout << srv->client << " " << mask << " " << usr[i]->getUsername() << " "
				<< srv->host << " * :" << usr[i]->getTruename() << std::endl;
			if (isOnline(usr[i]) == true){//verifie si un usr is ONLINE ou OFFLINE
				//RPL_WHOISACTUALLY
				std::cout << srv->client << " " << usr[i]->getNick() << " " << srv->host << " :is actually using host" << std::endl;
			}
			std::cout << srv->client << " " << usr[i]->getNick() << " " << srv << " :" << srv->info << std::endl;//RPL_WHOISSERVER
		}
	return (numeric_reply(RPL_ENDOFWHOWAS, srv));
}