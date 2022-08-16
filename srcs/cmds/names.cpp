#include "cmds.hpp"

int	rpl_namreply(channel* chan, Server& srv){
	// "<client> <symbol> <channel> :[prefix]<nick>{ [prefix]<nick>}"
	(void) srv;//
	std::cout << /*srv->client <<*/ " ";//<client>
	if (chan->getMode() == 's')//<symbol>
		std::cout << "@";//chan is secret
	else if (chan->getMode() == 'p')
		std::cout << "*";//chan is private
	else 
		std::cout << "=";
	std::cout << chan->getName() << " :";//<channel> :
	std::map<user*, int>*	usr_map = &(chan->getUsr_list());
	for (std::map<user*, int>::iterator it = usr_map->begin(); it != usr_map->end(); ++it){//[prefix]<nick>
		if (it->second == 4)
			std::cout << "@";
		else if (chan->getIsMod() == true && it->second == 1)
			std::cout << "+";
		std::cout << it->first->getNick() << " ";
	}
	std::cout << std::endl;
	return (RPL_NAMREPLY);
}

int	names(std::string params, std::vector<channel*> chan_vec, std::map<int, user *>& users, Server& srv){
	channel*				chan = NULL;

	//case no <channel> parameter is given
	if (params.empty()){
		for (size_t i = 0; i < chan_vec.size(); ++i){
			if (chan_vec[i]->getMode() != 's' && chan_vec[i]->getMode() != 'p')
				rpl_namreply(chan_vec[i], srv);
		}
		for (std::map<int, user *>::iterator it = users.begin(); it != users.end(); ++it){
			if ((it->second->getMode() != 'i' && it->second->getList_chan().empty())
				|| isIn1VisibleChannel(it->second) == false)
			std::cout << it->second->getNick() << " ";
		}
		std::cout << std::endl;
		return (numeric_reply(RPL_ENDOFNAMES, "", srv));
	}

	//case we have a list of <channel> parameter is given
	std::vector<std::string> v = paramsSeparedByComas(params);
	for (size_t i = 0; i < v.size(); ++i){
		chan = searchChannelByName(v[i], chan_vec);
		if (chan !=  NULL)
			rpl_namreply(chan, srv);
	}
	return (numeric_reply(RPL_ENDOFNAMES, v[v.size() - 1], srv));
}