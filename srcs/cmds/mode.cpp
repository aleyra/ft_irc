#include "cmds.hpp"


int	mode_user(std::vector<std::string> params, user* askingOne,
	std::map<unsigned int, user *> &users, Server& srv){
	// Parameters: <nickname> *( ( "+" / "-" ) *( "i" / "w" / "o" / "O" / "r" ) )
	user*	usr = searchUserByNick(params[0], users);
	if (usr == NULL)
		return (numeric_reply(ERR_NOSUCHNICK, askingOne, params[0], srv));
	// if (usr->getNick().compare(askingOne->getNick()) != 0)//tentative en deplacant ce if
	// 	return (numeric_reply(ERR_USERSDONTMATCH, askingOne, srv));
	if (params.size() == 1)
		return (numeric_reply(RPL_UMODEIS, askingOne, usr, srv));
	
	std::string	modestring = params[1];
	std::string tmp;
	std::string	last_sign = "+";

	if(modestring.size() == 1 && (modestring[0] == '-' || modestring[0] == '+'))
		return (EXIT_FAILURE);
	if (params[1].size() != 2){
		if (modestring[0] != '+' && modestring[0] != '-'){
				tmp = last_sign;
				tmp.append(modestring);
				modestring = tmp;
			}
			while (!std::isalpha(modestring[1])){
				modestring.erase(0, 1);
			}
			last_sign = modestring.substr(0, 1);
	}
	switch (modestring[1]){
		case 'i':// i - marks a users as invisible
			{
				if (modestring[0] == '+' && (usr->getNick().compare(askingOne->getNick()) != 0 || askingOne->getLvl() == SRV_OP))//tentative en ajoutant && cond
					usr->addMode('i');
				else if (params[1][0] == '-' && (usr->getNick().compare(askingOne->getNick()) != 0 || askingOne->getLvl() == SRV_OP))//tentative en ajoutant && cond
					usr->rmMode('i');
			}
			break;
		case 'o'://o - operator flag
			{
				if (usr->getNick().compare(askingOne->getNick()) != 0)//tentative en deplacant ce if
					return (numeric_reply(ERR_USERSDONTMATCH, askingOne, srv));
				if (modestring[0] == '-'){
					usr->setLvl(DEFAULT);
					usr->rmMode('o');
					usr->setIsop(false);
				}
			}
			break;
		default:
			return (numeric_reply(ERR_UMODEUNKNOWNFLAG, askingOne, srv));
			break;
	}
	// srv.send(askingOne->getNick() + " MODE " + usr->getNick() + " :" + modestring.substr(0, 2), askingOne->getId());
	// if (askingOne->getId() != usr->getId())
	// 	srv.send(askingOne->getNick() + " MODE " + usr->getNick() + " :" + modestring.substr(0, 2), usr->getId());
	numeric_reply(RPL_UMODEIS, askingOne, usr, srv);
	modestring.erase(0, 2);
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
	unsigned int					askingOne_id = askingOne->getId();
	// int								level_access = usr_list->at(askingOne_id);
	size_t							count_ov = 0;
	std::string						modestring = params[1];
	std::string						last_sign = "+";

	if(modestring.size() == 1 && (modestring[0] == '-' || modestring[0] == '+'))
		return (EXIT_FAILURE);
	//check enough params
	for (size_t i = 0; i < modestring.size(); ++i){
		if (modestring[i] == 'o' || modestring[i] == 'v')
			count_ov++;
	}
	if (params.size() < count_ov + 2)
		return (numeric_reply(ERR_NEEDMOREPARAMS, askingOne, "MODE", srv));
	
	if (askingOne->getLvl() >= SRV_OP || !(usr_list->find(askingOne_id) != usr_list->end() && usr_list->at(askingOne_id) >= CHAN_OP)){
		return (numeric_reply(ERR_CHANOPRIVSNEEDED, askingOne, chan, srv));
	}
	
	size_t		i = 2;
	int			count = 1;
	std::string	tmp;
	user*		usr = NULL;
	
	while (!modestring.empty() && count <= 3){
		if (modestring[0] != '-' && modestring[0] != '+'){
			tmp = last_sign;
			tmp.append(modestring);
			modestring = tmp;
		}
		while (modestring.size() > 2 && std::isalpha(modestring[1])){
			modestring.erase(0, 1);
		}
		last_sign = modestring.substr(0, 1);
		if (!std::isalpha(modestring[1]))
			break ;
		switch (modestring[1]){
			case 'o':// o - give/take channel operator privilege;
				{
					if (params.size() <= i)//case there's no nick given to give "channel operator"
						return (EXIT_FAILURE);
					usr = searchUserByNick(params[i], users);
					if (usr == NULL)//params[i] ne correspond pas a un user
						return (numeric_reply(ERR_NOSUCHNICK, askingOne, params[i], srv));
					if (usr_list->find(usr->getId()) == usr_list->end())
						return (numeric_reply(ERR_USERNOTINCHANNEL, askingOne, usr, chan, srv));
					askingOne_id = usr->getId();
					if (modestring[0] == '+')
						usr_list->at(askingOne_id) = CHAN_OP;
					else if (modestring[0] == '-'&& usr_list->at(askingOne_id) == CHAN_OP)
						usr_list->at(askingOne_id) = DEFAULT;
					i++;
					chan->send(srv, ":" + askingOne->getNick() + "!" + askingOne->getHistory_nick().front() + "@" + askingOne->getIp() + " " + "MODE " + chan->getName() + + " " + modestring.substr(0, 2) + " " + usr->getNick());
				}
				break;
			case 'v'://v - give/take the voice privilege;
				{
					if (params.size() <= i)//case there's no nick given to give "the voice privilege"
						return (EXIT_FAILURE);
					usr = searchUserByNick(params[i], users);
					if (usr == NULL)//params[i] ne correspond pas a un user
						return (EXIT_FAILURE);
					if (usr_list->find(usr->getId()) == usr_list->end())
						return (numeric_reply(ERR_USERNOTINCHANNEL, askingOne, usr, chan, srv));
					unsigned int	usr_id = usr->getId();
					if (modestring[0] == '+' && usr_list->at(usr_id) < VOICE_OK)
						usr_list->at(usr_id) = VOICE_OK;
					else if (modestring[0] == '-' && usr_list->at(usr_id) == VOICE_OK)
						usr_list->at(usr_id) = DEFAULT;
					i++;
					chan->send(srv, ":" + askingOne->getNick() + "!" + askingOne->getHistory_nick().front() + "@" + askingOne->getIp() + " " + "MODE " + chan->getName() + " " + modestring.substr(0, 2) + " " + usr->getNick());
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
					chan->send(srv, ":" + askingOne->getNick() + "!" + askingOne->getHistory_nick().front() + "@" + askingOne->getIp() + " " + "MODE " + chan->getName() + " " + modestring.substr(0, 2));
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
					chan->send(srv, ":" + askingOne->getNick() + "!" + askingOne->getHistory_nick().front() + "@" + askingOne->getIp() + " " + "MODE " + chan->getName() + " " + modestring.substr(0, 2));
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
					chan->send(srv, ":" + askingOne->getNick() + "!" + askingOne->getHistory_nick().front() + "@" + askingOne->getIp() + " " + "MODE " + chan->getName() + " " + modestring.substr(0, 2));
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
					chan->send(srv, ":" + askingOne->getNick() + "!" + askingOne->getHistory_nick().front() + "@" + askingOne->getIp() + " " + "MODE " + chan->getName() + " " + modestring.substr(0, 2));
				}
				break;
			case 'n'://n - notice ok
				{
					if (modestring[0] == '+'){
						chan->addMode('n');
					}
					else if (modestring[0] == '-'){
						chan->rmMode('n');
					}
					chan->send(srv, ":" + askingOne->getNick() + "!" + askingOne->getHistory_nick().front() + "@" + askingOne->getIp() + " " + "MODE " + chan->getName() + " " + modestring.substr(0, 2));
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
					chan->send(srv, ":" + askingOne->getNick() + "!" + askingOne->getHistory_nick().front() + "@" + askingOne->getIp() + " " + "MODE " + chan->getName() + " " + modestring.substr(0, 2));
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

int	mode(std::vector<std::string> params, user* askingOne, std::vector<channel *> &chan_vec,
	std::map<unsigned int, user *> &users, Server& srv){
	// Parameters: <target> [<modestring> [<mode arguments>...]]
	if (params.empty())
		return (numeric_reply(ERR_NEEDMOREPARAMS, askingOne, "MODE", srv));
	if (params[0][0] != '&' && params[0][0] != '#'
		&& params[0][0] != '+' && params[0][0] != '!')
			return (mode_user(params, askingOne, users, srv));
	return (mode_channel(params, askingOne, chan_vec, users, srv));
}
