#include "cmds.hpp"

int	rpl_namreply(user* askingOne, channel* chan, std::map<unsigned int,
	user *>& users, Server& srv){
	// "<client> <symbol> <channel> :[prefix]<nick>{ [prefix]<nick>}"
	(void) srv;//
	std::cout << /*srv->client <<*/ RPL_NAMREPLY << " " << askingOne->getNick() << " " ;//<client>
	if (chan->hasMode('s') == true)//<symbol>
		std::cout << "@";//chan is secret
	else if (chan->hasMode('p') == true)
		std::cout << "*";//chan is private
	else 
		std::cout << "=";
	std::cout << chan->getName() << " :";//<channel> :
	std::map<unsigned int, int>*	usr_map = &(chan->getUsr_list());
	for (std::map<unsigned, int>::iterator it = usr_map->begin(); it != usr_map->end(); ++it){//[prefix]<nick>
		if (it->second == 4)
			std::cout << "@";
		else if (chan->getIsMod() == true && it->second == 1)
			std::cout << "+";
		std::cout << searchUserByID(it->first, users)->getNick() << " ";
	}
	std::cout << std::endl;
	return (RPL_NAMREPLY);
}

int	names(std::string params, user* askingOne, std::vector<channel*> chan_vec, std::map<unsigned int, user *>& users, Server& srv){
	channel*				chan = NULL;

	//case no <channel> parameter is given
	if (params.empty()){
		for (size_t i = 0; i < chan_vec.size(); ++i){
			if (chan_vec[i]->hasMode('s') == true && chan_vec[i]->hasMode('p') == true)
				rpl_namreply(askingOne, chan_vec[i], users, srv);
		}
		for (std::map<unsigned int, user *>::iterator it = users.begin(); it != users.end(); ++it){
			if ((it->second->hasMode('i') == false && it->second->getList_chan().empty())
				|| isIn1VisibleChannel(it->second) == false)
			std::cout << it->second->getNick() << " ";
		}
		std::cout << std::endl;
		return (numeric_reply(RPL_ENDOFNAMES, askingOne, "", srv));
	}

	//case we have a list of <channel> parameter is given
	std::vector<std::string> v = paramsSeparedByComas(params);
	for (size_t i = 0; i < v.size(); ++i){
		chan = searchChannelByName(v[i], chan_vec);
		if (chan !=  NULL)
			rpl_namreply(askingOne, chan, users, srv);
	}
	return (numeric_reply(RPL_ENDOFNAMES, askingOne, v[v.size() - 1], srv));
}