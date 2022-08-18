#include "cmds.hpp"

int	join(std::string t, user* askingOne, std::vector<channel*>& chan_vec, Server& srv){
//Parameters: ( <channel> *( "," <channel> ) [ <key> *( "," <key> ) ] ) / "0"
	if (t.empty())
		return (numeric_reply(ERR_NEEDMOREPARAMS, askingOne, "JOIN", srv));

	std::vector<std::string>	params = paramsSeparedByComas(t);
	if (params[0].compare("0") == 0){
		// Leave all currently joined channels.
		return (EXIT_SUCCESS);
	}

	//on a pas de mode k pour les channel donc pas de <key> a gerer
	//sur libera.chat (cmd : nc -C irc.libera.chat 6667), si, y'a plusieurs <channel>, ils gerent qu'un seul
	if (params[0][0] == '&' || params[0][0] == '#'
		|| params[0][0] == '+' || params[0][0] == '!'){
		return (numeric_reply(ERR_NOSUCHCHANNEL, askingOne, params[0], srv));
	channel*	chan = NULL;
	chan = searchChannelByName(params[i]);
	if (chan == NULL){
		if (params[0][0] == '&' || params[0][0] == '+' || params[0][0] == '!')
			return (numeric_reply(ERR_NOSUCHCHANNEL, askingOne, params[0], srv));
		chan = new channel(params[0], askingOne);
		chan_vec.push_back(chan);
		askingOne->addList_chan(chan);
	}
	//join
	return (EXIT_SUCCESS);
}
/*
	ERR_BANNEDFROMCHAN
    ERR_INVITEONLYCHAN              
                   ERR_BADCHANMASK
                   ERR_TOOMANYCHANNELS
                  ERR_UNAVAILRESOURCE
    RPL_TOPIC
*/