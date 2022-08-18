#include "cmds.hpp"

int	invite(std::vector<std::string> params, user* askingOne,
	std::map<unsigned int, user *>& users, std::vector<channel *> &chan_vec, Server& srv){
	//Parameters: <nickname> <channel>
	if (params.size() < 2)
		return (numeric_reply(ERR_NEEDMOREPARAMS, askingOne, "MODE", srv));
	user*	usr = searchUserByNick(params[0], users);
	if (usr != NULL)
		return (numeric_reply(ERR_NOSUCHNICK, askingOne, params[0], srv));
	channel*	chan = searchChannelByName(params[2], chan_vec);
	if (chan == NULL)
		return (EXIT_FAILURE);
	std::map<unsigned int, int>&			usr_list = chan->getUsr_list();
	std::map<unsigned int, int>::iterator	pos = usr_list.find(askingOne->getId());
	if (pos == usr_list.end())
		return (numeric_reply(ERR_NOTONCHANNEL, askingOne, chan, srv));
	if (chan->hasMode('i') == true && pos->second != CHAN_OP)
		return (numeric_reply(ERR_CHANOPRIVSNEEDED, askingOne, chan, srv));
	pos = usr_list.find(usr->getId());
	if (pos != usr_list.end())
		return (numeric_reply(ERR_USERONCHANNEL, askingOne, usr, chan, srv));
	chan->addInvite_list(usr->getId());
	return (numeric_reply(RPL_INVITING, askingOne, usr, chan, srv));
}

/*Only the user inviting and the user being invited will receive
   notification of the invitation.*/