#include "cmds.hpp"


int	mode_user(std::vector<std::string> params, user* askingOne,
	std::map<unsigned int, user *> &users, Server& srv){
	// Parameters: <nickname> *( ( "+" / "-" ) *( "i" / "w" / "o" / "O" / "r" ) )
	user*	usr = searchUserByNick(params[0], users);
	if (usr == NULL)
		return (numeric_reply(ERR_NOSUCHNICK, params[0], srv));
	if (usr->getNick().compare(askingOne->getNick()) != 0)
		return (numeric_reply(ERR_USERSDONTMATCH, srv));
	if (params.size() == 1)
		return (numeric_reply(RPL_UMODEIS, usr, srv));
	if (params[1].size() != 2){
		if (params[1][0] != '+' && params[1][0] != '-'){
			std::string tmp("+");
			tmp.append(params[1]);
			params[1] = tmp;
		}
		while (!std::isalpha(params[1][1])){
			params[1].erase(1, 1);
		}
	}
	switch (params[1][1]){
		// case 'a'://a - user is flagged as away//pour le flag a, l'askingOne doit utiliser la commande AWAY
		// 	return (EXIT_FAILURE);
		// 	break;
		case 'i':// i - marks a users as invisible
			if (params[1][0] == '+')
				usr->addMode('i');
			else if (params[1][0] == '-')
				usr->rmMode('i');
			break;
		// case 'w'://w - user receives wallops
		// 	if (params[1][0] == '+')
		// 		usr->addMode('w');
		// 	else if (params[1][0] == '-')
		// 		usr->rmMode('w');
		// 	break;
		case 'r'://r - restricted user connection
			if (params[1][0] == '+')
				usr->addMode('r');
			break;
		case 'o'://o - operator flag
			if (params[1][0] == '-' && usr->getLvl() == SRV_OP){
				usr->setLvl(DEFAULT_USR);
				usr->rmMode('o');
			}
			break;
		// case 'O'://O - local operator flag
		// 	if (params[1][0] == '-' && usr->getLvl() == SRV_OP){
		// 		usr->setLvl(DEFAULT_USR);
		// 		usr->rmMode('O');
		// 	}
		// 	break;
		default:
			return (numeric_reply(ERR_UMODEUNKNOWNFLAG, srv));
			break;
	}
	return (EXIT_SUCCESS);
}

int	mode_channel(std::vector<std::string> params, std::vector<channel *> &chan_vec, Server& srv){
	// Parameters: <channel> *( ( "-" / "+" ) *<modes> *<modeparams> )
	channel*	chan = searchChannelByName(params[0], chan_vec);
	if (chan == NULL)
		return (numeric_reply(ERR_NOSUCHCHANNEL, params[0], srv));
	if (params[0][0] == '+'){
		return (numeric_reply(ERR_NOCHANMODES, chan, srv));
	}
	return (EXIT_SUCCESS);
}
/* 		
	The various modes available for channels are as follows:

        O - give "channel creator" status;
        o - give/take channel operator privilege;
        v - give/take the voice privilege;

        a - toggle the anonymous channel flag;
        i - toggle the invite-only channel flag;
        m - toggle the moderated channel;
        n - toggle the no messages to channel from clients on the
            outside;
        q - toggle the quiet channel flag;
        p - toggle the private channel flag;
        s - toggle the secret channel flag;
        r - toggle the server reop channel flag;
        t - toggle the topic settable by channel operator only flag;

        k - set/remove the channel key (password);
        l - set/remove the user limit to channel;

        b - set/remove ban mask to keep users out;
        e - set/remove an exception mask to override a ban mask;
        I - set/remove an invitation mask to automatically override
            the invite-only flag;

		INVITE  - Invite a client to an invite-only channel (mode +i)
        KICK    - Eject a client from the channel
        MODE    - Change the channel's mode, as well as
                  members' privileges
        PRIVMSG - Sending messages to the channel (mode +n, +m, +v)
        TOPIC   - Change the channel topic in a mode +t channel
*/

int	mode(std::vector<std::string> params, user* askingOne, std::vector<channel *> &chan_vec, std::map<unsigned int, user *> &users, Server& srv){
	// Parameters: <target> [<modestring> [<mode arguments>...]]
	if (params.empty())
		return (numeric_reply(ERR_NEEDMOREPARAMS, "MODE", srv));
	if (params[0][0] == '&' || params[0][0] == '#'
		|| params[0][0] == '+' || params[0][0] == '!')
		return (mode_channel(params, chan_vec, srv));
	return (mode_user(params, askingOne, users, srv));
}
