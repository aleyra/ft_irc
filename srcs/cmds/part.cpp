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

		std::map<unsigned int, int> & usr_list = chan->getUsr_list();
		if (usr_list.at(askingOne->getId()) <= CHAN_OP)
			chan->rm1toNbChanOp();
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
			chan->send(srv, ":" + askingOne->getNick() + "!" + askingOne->getHistory_nick().front() + "@" + askingOne->getIp() + " " + "PART " + params[i] + " " + msg);
			srv.send(":" + askingOne->getNick() + "!" + askingOne->getHistory_nick().front() + "@" + askingOne->getIp() + " " + "PART " + params[i] + " " + msg, askingOne->getId());
		}
		//if chan is empty, delete chan

		// std::map<unsigned int, int> * usr_list = &chan->getUsr_list();

		if (chan->get_nb_chan_op() == 0){
			for (std::map<unsigned int, int>::const_iterator it = usr_list.begin(); it != usr_list.end(); ++it){
				if (chan->hasMode('m') && ((it->second < CHAN_OP && it->second >= VOICE_OK) || usr_list.size() == 1)){
					usr_list.at(it->first) = CHAN_OP;
					chan->add1toNbChanOp();
				}
				else if (it->second < CHAN_OP){
					usr_list.at(it->first) = CHAN_OP;
					chan->add1toNbChanOp();
				}
				if (chan->get_nb_chan_op() == 1)
					break;
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