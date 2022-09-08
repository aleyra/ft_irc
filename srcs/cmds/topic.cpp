#include "cmds.hpp"

int	topic(std::vector<std::string> params, user* askingOne,
	std::vector<channel*> chan_vec, Server& srv){
	if (params.empty())
		return (numeric_reply(ERR_NEEDMOREPARAMS, askingOne, "TOPIC", srv));
	
	channel*	chan = searchChannelByName(params[0], chan_vec);
	if (params.size() == 1){
		if (chan->getTopic().empty())
			return (numeric_reply(RPL_NOTOPIC, askingOne, chan, srv));
		return (numeric_reply(RPL_TOPIC, askingOne, chan, srv));
	}
	
	std::map<unsigned int, int>*	usr_list = &(chan->getUsr_list());	
	if (usr_list->find(askingOne->getId()) == usr_list->end())
		return (numeric_reply(ERR_NOTONCHANNEL, askingOne, chan, srv));
	
	unsigned int	usr_id = askingOne->getId();
	int				level_access = usr_list->at(usr_id);
	if (chan->hasMode('t') == true 
		&& (level_access < CHAN_OP))
		return (numeric_reply(ERR_CHANOPRIVSNEEDED, askingOne, chan, srv));
	
	if (params[1][0] == ':')
		params[1].erase(0, 1);
	for (size_t i = 2; i < params.size(); ++i){
		params[1].append(" ");
		params[1].append(params[i]);
	}
	chan->setTopic(params[1]);
	chan->send(srv, ":" + askingOne->getNick() + "!" + askingOne->getHistory_nick().front() + "@" + askingOne->getIp() + " " + "TOPIC " + chan->getName() + " :" + params[1]);
	/*case ERR_NOCHANMODES
		return (numeric_reply(ERR_NOCHANMODES, askingOne, chan, srv));
	
	cette erreur ne sera pas geree car :
		elle suppose qu'il existe un mode ou personne (?) ne peut changer le topic
		il n'y a pas de mode tel que celui-ci (https://datatracker.ietf.org/doc/html/rfc2811#section-4)
		et quand on regarde la gestion des topic (https://datatracker.ietf.org/doc/html/rfc2811#section-4.2.8) ils ne parlent que du mode t qui est gerer avec l'erreur ERR_CHANOPRIVSNEEDED
	*/
	return (EXIT_SUCCESS);
}