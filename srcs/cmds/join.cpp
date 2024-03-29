#include "cmds.hpp"

int	join(std::string t, user* askingOne, std::vector<channel*>& chan_vec,
	std::map<unsigned int, user *> &users, Server& srv){
//Parameters: ( <channel> *( "," <channel> ) [ <key> *( "," <key> ) ] ) / "0"
	
	if (t.empty())
		return (numeric_reply(ERR_NEEDMOREPARAMS, askingOne, "JOIN", srv));
	std::vector<std::string>	params = paramsSeparedByComas(t);
	std::vector<channel*> &		list_chan = askingOne->getList_chan();
	std::vector<std::string>	paramsDePart;
	paramsDePart.push_back("");
	if (params[0].compare("0") == 0){
		if (list_chan.empty())
			return (EXIT_SUCCESS);
		for (size_t i = 0; i < list_chan.size(); ++i){
			if (i != 0)
				paramsDePart[0].append(",");
			paramsDePart[0].append(list_chan[i]->getName());
		}
		part(paramsDePart, askingOne, chan_vec, srv);
		return (EXIT_SUCCESS);
	}

	//on a pas de mode k pour les channel donc pas de <key> a gerer
	std::vector<std::string>::iterator pos = params.end();
	for (size_t i = 0; i < params.size(); ++i){
		if (params[i][0] != '&' && params[i][0] != '#'
			&& params[i][0] != '+' && params[i][0] != '!'){
			numeric_reply(ERR_NOSUCHCHANNEL, askingOne, params[i], srv);
			pos = std::find(params.begin(), params.end(), params[i]);
			params.erase(pos);
		}
	}

	channel*		chan = NULL;
	unsigned int	askingOne_id = 0;
	std::vector<unsigned int> * invite_list = NULL;
	// std::vector<unsigned int>::iterator	position;
	for (size_t i = 0; i < params.size(); ++i){
		chan = searchChannelByName(params[i], chan_vec);
		if (chan == NULL){//try to create chan
			if (params[i][0] == '&' || params[i][0] == '+' || params[i][0] == '!')
				return (numeric_reply(ERR_NOSUCHCHANNEL, askingOne, params[i], srv));
			chan = new channel(params[i], askingOne);
			chan_vec.push_back(chan);
			chan->addMode('t');
			chan->addMode('n');
		}
		//check if askingOne is already on chan
		std::vector<channel*>::iterator itchan = std::find(askingOne->getList_chan().begin(), askingOne->getList_chan().end(), chan);
		if (itchan == askingOne->getList_chan().end()){
			invite_list = &(chan->getInvite_list());
			askingOne_id = askingOne->getId();
			//check if chan has mode i and if so, if askingOne is invited
			std::vector<unsigned int>::iterator position = std::find(invite_list->begin(), invite_list->end(), askingOne_id);
			if(chan->hasMode('i') == true && position == invite_list->end())
				return (numeric_reply(ERR_INVITEONLYCHAN, askingOne, chan, srv));
			//add chan to askingOne.list_chan
			askingOne->addList_chan(chan);
			//add askingOne to chan.list_usr
			std::map<unsigned int, int> &	usr_list = chan->getUsr_list();
			if (usr_list.find(askingOne_id) == usr_list.end())
				chan->addUsr_list(askingOne);
			if (chan->getUsr_list().size() <= 5)
				chan->getUsr_list().at(askingOne_id) = CHAN_OP;
			//send msgs
			chan->send(srv, ":" + askingOne->getNick() + "!" + askingOne->getHistory_nick().front() + "@" + askingOne->getIp() + " " + "JOIN " + params[i]);
			if (chan->hasMode('t') ==  true && !(chan->getTopic().empty()))
				numeric_reply(RPL_TOPIC, askingOne, chan, srv);
			numeric_reply(RPL_CHANNELMODEIS, askingOne, chan, srv);
			names(params[i], askingOne, chan_vec, users, srv);
		}
	}
	return (EXIT_SUCCESS);
}
/*
	ERR_BANNEDFROMCHAN              
    ERR_BADCHANMASK
    ERR_TOOMANYCHANNELS
    ERR_UNAVAILRESOURCE
*/