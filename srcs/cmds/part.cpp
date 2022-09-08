#include "cmds.hpp"

int	part(std::vector<std::string> paramsEtMsg, user* askingOne,
	std::vector<channel *> &chan_vec, Server& srv){
	if (paramsEtMsg.empty())
		return (numeric_reply(ERR_NEEDMOREPARAMS, askingOne, "PART", srv));
	//get list of chan where user want to part
	std::vector<std::string>		params = paramsSeparedByComas(paramsEtMsg[0]);
	
	std::string						msg;
	channel*						chan = NULL;
	std::vector<channel*> &			list_chan = askingOne->getList_chan();
	std::vector<channel*>::iterator	pos = list_chan.end();
	//get msg
	if (paramsEtMsg.size() == 2)
		msg = paramsEtMsg[1];
	//let's go
	for (size_t i = 0; i < params.size(); ++i){
		//check chan exists
		if (params[i][0] != '&' && params[i][0] != '#'
			&& params[i][0] != '+' && params[i][0] != '!'){
			numeric_reply(ERR_NOSUCHCHANNEL, askingOne, params[i], srv);
			continue;
		}
		chan = searchChannelByName(params[i], chan_vec);
		if (chan == NULL){
			numeric_reply(ERR_NOSUCHCHANNEL, askingOne, params[i], srv);
			continue;
		}
		//check askingOne is in chan
		pos = std::find(list_chan.begin(), list_chan.end(), chan);
		if (pos == list_chan.end())
			numeric_reply(ERR_NOTONCHANNEL, askingOne, chan, srv);
		//rm chan from askingOne.list_chan
		askingOne->rmList_chan(chan);
		//rm askingOne from chan.usr_list
		chan->rmUsr_list(askingOne);
		//send msgs
		if (msg.empty()){
			chan->send(srv, ":" + askingOne->getNick() + "!" + askingOne->getHistory_nick().front() + "@" + askingOne->getIp() + " " + "PART " + params[i]);
			srv.send(":" + askingOne->getNick() + "!" + askingOne->getHistory_nick().front() + "@" + askingOne->getIp() + " " + "PART " + params[i], askingOne->getId());
		}
		else{
			chan->send(srv, ":" + askingOne->getNick() + "!" + askingOne->getHistory_nick().front() + "@" + askingOne->getIp() + " " + "PART " + params[i] + ":" + msg);
			srv.send(":" + askingOne->getNick() + "!" + askingOne->getHistory_nick().front() + "@" + askingOne->getIp() + " " + "PART " + params[i] + ":" + msg, askingOne->getId());
		}
		//if chan is empty, delete chan
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