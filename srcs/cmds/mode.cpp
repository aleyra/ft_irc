#include "cmds.hpp"


int	mode_user(std::vector<std::string> params, user* askingOne,
	std::map<unsigned int, user *> &users, Server& srv){
	// Parameters: <nickname> *( ( "+" / "-" ) *( "i" / "w" / "o" / "O" / "r" ) )
	user*	usr = searchUserByNick(params[0], users);
	if (usr == NULL)
		return (numeric_reply(ERR_NOSUCHNICK, askingOne, params[0], srv));
	if (usr->getNick().compare(askingOne->getNick()) != 0)
		return (numeric_reply(ERR_USERSDONTMATCH, askingOne, srv));
	if (params.size() == 1)
		return (numeric_reply(RPL_UMODEIS, askingOne, usr, srv));
	if (params[1].size() != 2){
		if (params[1][0] != '+' && params[1][0] != '-'){
			std::string tmp("+");
			tmp.append(params[1]);
			params[1] = tmp;
		}
		while (!std::isalpha(params[1][1])){
			params[1].erase(0, 1);
		}
	}
	switch (params[1][1]){
		case 'i':// i - marks a users as invisible
			if (params[1][0] == '+')
				usr->addMode('i');
			else if (params[1][0] == '-')
				usr->rmMode('i');
			break;
		case 'r'://r - restricted user connection
			if (params[1][0] == '+')
				usr->addMode('r');
			break;
		case 'o'://o - operator flag
			if (params[1][0] == '-' && usr->getLvl() == SRV_OP){
				usr->setLvl(DEFAULT_USR);
				usr->rmMode('o');
				usr->setIsop(false);
			}
			break;
		default:
			return (numeric_reply(ERR_UMODEUNKNOWNFLAG, askingOne, srv));
			break;
	}
	return (EXIT_SUCCESS);
}

int	mode_channel(std::vector<std::string> params, user* askingOne,
	std::vector<channel *> &chan_vec, std::map<unsigned int, user *> &users,
	Server& srv){
	// Parameters: <channel> *( ( "-" / "+" ) *<modes> *<modeparams> )
	channel*	chan = searchChannelByName(params[0], chan_vec);
	if (chan == NULL)
		return (numeric_reply(ERR_NOSUCHCHANNEL, askingOne, params[0], srv));
	if (params[0][0] == '+')
		return (numeric_reply(ERR_NOCHANMODES, askingOne, chan, srv));
	if (params.size() == 1)
		return (numeric_reply(RPL_CHANNELMODEIS, askingOne, chan, srv));

	std::map<unsigned int, int>*	usr_list = &(chan->getUsr_list());
	unsigned int					usr_id = askingOne->getId();
	int								level_access = usr_list->at(usr_id);
	if (usr_list->find(askingOne->getId()) == usr_list->end() || level_access != CHAN_OP)
		return (numeric_reply(ERR_CHANOPRIVSNEEDED, askingOne, chan, srv));
	std::string	modestring = params[1];
	size_t		i = 2;
	int			count = 1;
	std::string	tmp;
	user*		usr = NULL;
	// std::pair<unsigned int, int>	*p = NULL;
	while (!modestring.empty() && count <= 3){
		if (modestring.size() != 2){//les 2 premiers char seront toujours un signe et une lettre
			if (modestring[0] != '+' && modestring[0] != '-'){
				tmp = "+";
				tmp.append(modestring);
				modestring = tmp;
			}
			while (!std::isalpha(modestring[1])){
				modestring.erase(0, 1);
			}
		}
		switch (modestring[2]){
			case 'o':// o - give/take channel operator privilege;
				{
					if (params.size() <= i + 1)//case there's no nick given to give "channel operator"
						return (EXIT_FAILURE);
					usr = searchUserByNick(params[i], users);
					if (usr == NULL)//params[i] ne correspond pas a un user
						return (EXIT_FAILURE);
					if (usr_list->find(usr->getId()) == usr_list->end())
						return (numeric_reply(ERR_USERNOTINCHANNEL, askingOne, usr, chan, srv));
					usr_id = usr->getId();
					if (modestring[0] == '+')
						usr_list->at(usr_id) = CHAN_OP;
					else if (modestring[0] == '-')
						usr_list->at(usr_id) = DEFAULT;
					i++;
				}
				break;
			case 'v'://v - give/take the voice privilege;
				{
					if (params.size() <= i + 1)//case there's no nick given to give "the voice privilege"
						return (EXIT_FAILURE);
					usr = searchUserByNick(params[i], users);
					if (usr == NULL)//params[i] ne correspond pas a un user
						return (EXIT_FAILURE);
					if (usr_list->find(usr->getId()) == usr_list->end())
						return (numeric_reply(ERR_USERNOTINCHANNEL, askingOne, usr, chan, srv));
					usr_id = usr->getId();
					if (modestring[0] == '+')
						usr_list->at(usr_id) = VOICE_OK;
					else if (modestring[0] == '-')
						usr_list->at(usr_id) = DEFAULT;
					i++;
				}
				break;
			case 'i'://i - toggle the invite-only channel flag;
				{
					if (modestring[0] == '+'){
						chan->addMode('i');
					}
					else if (modestring[0] == '-'){
						chan->rmMode('i');
					}
				}
				break;
			case 'm'://m - toggle the moderated channel;
				{
					if (modestring[0] == '+'){
						chan->addMode('m');
					}
					else if (modestring[0] == '-'){
						chan->rmMode('m');
					}
				}
				break;
			case 'p'://p - toggle the private channel flag;
				{
					if (modestring[0] == '+'){
						chan->addMode('p');
					}
					else if (modestring[0] == '-'){
						chan->rmMode('p');
					}
				}
				break;
			case 's'://s - toggle the secret channel flag;
				{
					if (modestring[0] == '+'){
						chan->addMode('s');
					}
					else if (modestring[0] == '-'){
						chan->rmMode('s');
					}
				}
				break;
			case 't'://t - toggle the topic settable by channel operator only flag;
				{
					if (modestring[0] == '+'){
						chan->addMode('t');
					}
					else if (modestring[0] == '-'){
						chan->rmMode('t');
					}
				}
				break;

			// case 'b'://b - set/remove ban mask to keep users out;//whynot
			// 	{
			// 		if (modestring[0] == '+'){
			// 			chan->addMode('b');
			// 		}
			// 		else if (modestring[0] == '-'){
			// 			chan->rmMode('b');
			// 		}
			// 	}
			// 	break;
			
			default:
				return (numeric_reply(ERR_UNKNOWNMODE, askingOne, modestring.substr(1, 1), srv));
				break;
		}
		modestring.erase(0, 2);
		count++;
	}
	return (EXIT_SUCCESS);
}
/* 		
	The various modes available for channels are as follows:

		INVITE  - Invite a client to an invite-only channel (mode +i)
        KICK    - Eject a client from the channel
        MODE    - Change the channel's mode, as well as
                  members' privileges
        PRIVMSG - Sending messages to the channel (mode +n, +m, +v)
        TOPIC   - Change the channel topic in a mode +t channel
*/

int	mode(std::vector<std::string> params, user* askingOne, std::vector<channel *> &chan_vec,
	std::map<unsigned int, user *> &users, Server& srv){
	// Parameters: <target> [<modestring> [<mode arguments>...]]
	if (params.empty())
		return (numeric_reply(ERR_NEEDMOREPARAMS, askingOne, "MODE", srv));
	if (params[0][0] == '&' || params[0][0] == '#'
		|| params[0][0] == '+' || params[0][0] == '!')
		return (mode_channel(params, askingOne, chan_vec, users, srv));
	return (mode_user(params, askingOne, users, srv));
}
