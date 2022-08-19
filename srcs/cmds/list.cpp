#include "cmds.hpp"

int	rpl_list(user* askingOne, channel* chan, std::map<unsigned int, user *>& users, Server& srv){
	std::string	to_send;
	to_send += srv.client_ip(askingOne->getId()) + to_string(RPL_LIST) + " " + askingOne->getNick() + " ";
	to_send += chan->getName() + " ";
	to_send += to_string(countVisibleUsers(chan, users)) + " :" + chan->getTopic();
	srv.send(to_send, askingOne->getId());
	return (RPL_LIST);
}

int	list(std::string params, user* askingOne, std::vector<channel*>& chan_vec, std::map<unsigned int, user *>& users, Server& srv){
	// Parameters: [ <channel> *( "," <channel> ) [ <target> ] ]
	if (params.empty()){
		for (size_t i = 0; i < chan_vec.size(); ++i){
			rpl_list(askingOne, chan_vec[i], users, srv);
			// numeric_reply(RPL_LIST, chan_vec[i], srv);
		}
	}
	std::vector<std::string>	v = paramsSeparedByComas(params);
	channel*	chan = NULL;
	for (size_t i = 0; i < v.size(); ++i){
		chan = searchChannelByName(v[i], chan_vec);
		if (chan != NULL)
			rpl_list(askingOne, chan, users, srv);
		// numeric_reply(RPL_LIST, v[i], srv);
	}
	return (numeric_reply(RPL_LISTEND, askingOne, srv));
}

