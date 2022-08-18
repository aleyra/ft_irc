#include "cmds.hpp"

int	join(std::string t, user* askingOne, std::vector<channel*>& chan_vec,
	std::map<unsigned int, user *> &users, Server& srv){
//Parameters: ( <channel> *( "," <channel> ) [ <key> *( "," <key> ) ] ) / "0"
	if (t.empty())
		return (numeric_reply(ERR_NEEDMOREPARAMS, askingOne, "JOIN", srv));
	std::vector<std::string>	params = paramsSeparedByComas(t);
	if (params[0].compare("0") == 0){//todo
		// Leave all currently joined channels.
		return (EXIT_SUCCESS);
	}

	//on a pas de mode k pour les channel donc pas de <key> a gerer
	/*sur libera.chat (cmd : nc -C irc.libera.chat 6667), si y'a plusieurs <channel>,
	 ils gerent qu'un seul*/
	if (params[0][0] == '&' || params[0][0] == '#'
		|| params[0][0] == '+' || params[0][0] == '!')
		return (numeric_reply(ERR_NOSUCHCHANNEL, askingOne, params[0], srv));
	channel*	chan = NULL;
	chan = searchChannelByName(params[0], chan_vec);
	if (chan == NULL){
		if (params[0][0] == '&' || params[0][0] == '+' || params[0][0] == '!')
			return (numeric_reply(ERR_NOSUCHCHANNEL, askingOne, params[0], srv));
		chan = new channel(params[0], askingOne);
		chan_vec.push_back(chan);
		chan->addMode('t');
	}
	askingOne->addList_chan(chan);
	std::map<unsigned int, int> &	usr_list = chan->getUsr_list();
	if (usr_list.find(askingOne->getId()) == usr_list.end())
		chan->addUsr_list(askingOne);
	srv.send("JOIN " + params[0], askingOne->getId());
	if (chan->hasMode('t') ==  true && !(chan->getTopic().empty()))
		numeric_reply(RPL_TOPIC, askingOne, chan, srv);
	numeric_reply(RPL_CHANNELMODEIS, askingOne, chan, srv);
	names(params[0], askingOne, chan_vec, users, srv);
	return (EXIT_SUCCESS);
}
/*
	ERR_BANNEDFROMCHAN
    ERR_INVITEONLYCHAN              
    ERR_BADCHANMASK
    ERR_TOOMANYCHANNELS
    ERR_UNAVAILRESOURCE
*/