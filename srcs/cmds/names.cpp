#include "cmds.hpp"

int	rpl_namreply(user* askingOne, channel* chan, std::map<unsigned int,
	user *>& users, Server& srv){
	std::string	to_send;
	// "<client> <symbol> <channel> :[prefix]<nick>{ [prefix]<nick>}"
	to_send += ":server " + to_string(RPL_NAMREPLY) + " " + askingOne->getNick() + " " ;//<client>
	// These are lines are supposed to be here, but... weechat
	// if (chan->hasMode('s') == true)//<symbol>
	// 	to_send += "@";//chan is secret
	// else if (chan->hasMode('p') == true)
	// 	to_send += "*";//chan is private
	// else 
	// 	to_send += "=";
	to_send += chan->getName() + " :";//<channel> :
	std::map<unsigned int, int>*	usr_map = &(chan->getUsr_list());
	for (std::map<unsigned, int>::iterator it = usr_map->begin(); it != usr_map->end(); ++it){//[prefix]<nick>
		if (it->second == 4)
			to_send += "@";
		else if (chan->getIsMod() == true && it->second == 1)
			to_send += "+";
		to_send += searchUserByID(it->first, users)->getNick() + " ";
	}
	srv.send(to_send, askingOne->getId());
	return (RPL_NAMREPLY);
}

int	names(std::string params, user* askingOne, std::vector<channel*> chan_vec, std::map<unsigned int, user *>& users, Server& srv){
	channel*	chan = NULL;
	std::string	to_send;

	//case no <channel> parameter is given
	if (params.empty()){
		for (size_t i = 0; i < chan_vec.size(); ++i){
			if (chan_vec[i]->hasMode('s') == true && chan_vec[i]->hasMode('p') == true)
				rpl_namreply(askingOne, chan_vec[i], users, srv);
		}
		for (std::map<unsigned int, user *>::iterator it = users.begin(); it != users.end(); ++it){
			if ((it->second->hasMode('i') == false && it->second->getList_chan().empty())
				|| isIn1VisibleChannel(it->second) == false)
			to_send += it->second->getNick() + " ";
		}
		srv.send(to_send, askingOne->getId());
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