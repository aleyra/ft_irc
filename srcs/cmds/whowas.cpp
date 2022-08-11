#include "cmds.hpp"

// int whowas(std::vector<std::string> params, Server* srv){
// 	if (params.empty())
// 		return (numeric_reply(ERR_NONICKNAMEGIVEN, srv));

// 	//transform params to a string and eventually an int
// 	if (params.size() > 2)
// 		return (EXIT_FAILURE);
// 	std::string	mask = *(params[0]);
// 	int			count = 0;
// 	if (params.size() == 2)
// 		count = std::atoi(params[1].c_str());

// 	//from string to user*
// 	user*		usr = findInAllUser(mask);//chercher un nickname correspondant dans la liste des user OFFLINE ou ONLINE old nick
	
// 	//if no such mask
// 	if (usr == NULL){
// 		numeric_reply(ERR_NOSUCHNICK, mask);
// 		return (numeric_reply(RPL_ENDOFWHOWAS, srv));
// 	}
	
// 	//else
// 	std::cout << usr->getNick() << "@" << usr << srv->host << "*:"
// 		<< usr->getTruename() << std::endl;//RPL_WHOISUSER
// 	std::cout << usr->getNick() << ":";//RPL_WHOISCHANNELS
// 	std::vector<channel*> &list_chan = usr->getList_chan;

// 	if (count == 0){
// 		for (int i = 0; i < list_chan.size(); ++i){
// 			if (i == 0 && i != list_chan.size() - 1)
// 				std::cout << " ";
// 			if (list_chan[i]->getUsr_list[usr] == 4)//est un operateur du chan
// 				std::cout << "@" ;//a verif
// 			else if (list_chan[i]->getIsMod() == true && list_chan[i]->getUsr_list[usr] >= 1)//if it's a moderated channel and usr is allowed to speak
// 				std::cout << "+";
// 			std::cout << list_chan[i]->getName();
// 		}
// 	}
// 	else
// 	std::endl;
// 	std::cout << usr->getNick() << ": " << usr->check_Idle_time() << "seconds idle"
// 		<< std::endl;//RPL_WHOISIDLE
// 	if (usr->getLvl == 2)//RPL_WHOISOPERATOR
// 		std::cout << usr->getNick() << "is an IRC operator" << std::endl;
// 	//autre chose ?
	
// 	return (numeric_reply(RPL_ENDOFWHOWAS, srv));
// }