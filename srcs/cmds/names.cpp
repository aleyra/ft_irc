#include "cmds.hpp"

std::vector<std::string>	names_params(std::string txt){
	std::vector<std::string> 	v;
	size_t						pos = txt.find(',');
	while	(pos != std::string::npos){
		txt.replace(pos, 1, " ");
		pos = txt.find(',');
	}
	v = params(txt);
	return v;
}

int	rpl_namreply(channel* chan, Server* srv){
	// "<client> <symbol> <channel> :[prefix]<nick>{ [prefix]<nick>}"	
	std::cout << /*srv->client <<*/ " ";//<client>
	//<symbol>
	if (chan->getMode() == 's')//chan is secret
		std::cout << "@";
	else if (chan->getMode() == 'p')//chan is private
		std::cout << "*";
	else 
		std::cout << "=";
	std::cout << chan->getName() << " :";//<channel> :
	std::map<user*, int>&	usr_map = chan->getUsr_list();
	for (std::map<user*, int>::iterator it = usr_map.begin(); it != usr_map.end(); ++it){//[prefix]<nick>
		if (it->second == 4)
			std::cout << "@";
		else if (chan->getIsMod() == true && it->second == 1)
			std::cout << "+";
		std::cout << it->first->getNick() << " ";
	}
	return (RPL_NAMREPLY);
}

int	names(std::string params, std::vector<channel*> chan_vec, std::map<int, user *>& users, Server* srv){
	/*If no <channel> parameter is given, a list of all channels and their
	occupants is returned.  At the end of this list, a list of users who are
	visible but either not on any channel or not on a visible channel are listed
	as being on `channel' "*".*/
	// std::map<user*, int>*	usr_map = NULL;
	user*					usr = NULL;
	channel*				chan = NULL;

	//case no <channel> parameter is given
	if (params.empty()){
		for (size_t i = 0; i < chan_vec.size(); ++i){
			//if chan_vec[i] est visible ??
			// usr_map = &(chan_vec[i]->getUsr_list());
			// for (std::map<user*, int>::iterator it = usr_map->begin(); it != usr_map->end(); ++it){
			// 	usr = it->first;
			// 	//afficher quoi  de usr ?
			// }
		}
		//lister les user qui sont dans aucun chan ou dans un chan invisible
		return (numeric_reply(RPL_ENDOFNAMES, "", srv);
	}

	//case we have a list of <channel> parameter is given
	std::vector<std::string> v = names_params(params);
	for (size_t i = 0; i < v.size(); ++i){
		chan = searchChannelByName(v[i], chan_vec);
		if (chan !=  NULL){
			// usr_map = &(chan_vec[i]->getUsr_list());
			// for (std::map<user*, int>::iterator it = usr_map->begin(); it != usr_map->end(); ++it){
			// 		usr = it->first;
			// 		//afficher quoi  de usr ?
			// }
		}
	}
	return (numeric_reply(RPL_ENDOFNAMES, v[v.size() - 1]), srv);
}