#include "cmds.hpp"

int	part(std::vector<std::string> paramsEtMsg, user* askingOne,
	std::vector<channel *> &chan_vec, Server& srv){
	if (paramsEtMsg.empty())
		return (numeric_reply(ERR_NEEDMOREPARAMS, askingOne, "PART", srv));
	std::vector<std::string>		params = paramsSeparedByComas(paramsEtMsg[0]);
	std::string						msg;
	channel*						chan = NULL;
	std::vector<channel*> &			list_chan = askingOne->getList_chan();
	std::vector<channel*>::iterator	pos = list_chan.end();
	if (paramsEtMsg.size() == 2)
		msg = paramsEtMsg[1];
	for (size_t i = 0; i < params.size(); ++i){
		if (params[i][0] != '&' || params[i][0] != '#'
			|| params[i][0] != '+' || params[i][0] != '!'){
			numeric_reply(ERR_NOSUCHCHANNEL, askingOne, params[i], srv);
			continue;
		}
		chan = searchChannelByName(params[i], chan_vec);
		if (chan == NULL){
			numeric_reply(ERR_NOSUCHCHANNEL, askingOne, params[i], srv);
			continue;
		}
		pos = std::find(list_chan.begin(), list_chan.end(), chan);
		if (pos == list_chan.end())
			numeric_reply(ERR_NOTONCHANNEL, askingOne, chan, srv);
		askingOne->rmList_chan(chan);
		chan->rmUsr_list(askingOne);
		std::map<unsigned int, int> &	usr_list = chan->getUsr_list();
		if (msg.empty()){
			srv.send("PART " + params[i], askingOne->getId());
			for(std::map<unsigned int, int>::iterator it = usr_list.begin();
				it != usr_list.end(); ++it){
				if (it->first != askingOne->getId())
					srv.send("PART " + params[i], it->first);
			}
		}
		else{
			srv.send("PART " + params[i] + ":" + msg, askingOne->getId());
			for(std::map<unsigned int, int>::iterator it = usr_list.begin();
				it != usr_list.end(); ++it){
				if (it->first != askingOne->getId())
					srv.send("PART " + params[i] + ":" + msg, it->first);
			}
		}
		if (chan->getUsr_list().empty()){
			pos = std::find(chan_vec.begin(), chan_vec.end(), chan);
			chan_vec.erase(pos);
			delete chan;
		}
	}
	return (EXIT_SUCCESS);
}
/*
	ERR_NEEDMOREPARAMS
	ERR_NOSUCHCHANNEL
    ERR_NOTONCHANNEL
*/