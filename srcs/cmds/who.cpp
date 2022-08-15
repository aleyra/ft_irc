#include "cmds.hpp"

int rpl_whoreply(user* usr, int count){
//"<channel> <user> <host> <server> <nick> ( "H" / "G" > ["*"] [ ( "@" / "+" ) ] :<hopcount> <real name>"
	std::cout << usr->getList_chan()[0]->getName() << " ";
	std::cout << usr->getNick() << " ";//<user>//?
	std::cout << "<host>" << " ";//<host>//a modifier//?
	// std::cout << srv << " ";//<server> //?
	std::cout << usr->getNick() << " ";//<nick> 
	std::cout << display_isaway(usr) << " ";//( "H" / "G" > 
	if (usr->getIsop() == true)//["*"] 
		std::cout << "* ";
	std::vector<channel*> list_chan = usr->getList_chan();//"@" de [ ( "@" / "+" ) ]
	for (size_t i = 0; i < list_chan.size(); ++i){
		if (list_chan[i]->getUsr_list()[usr] == 4){
			std::cout << "@";
			break ;
		}
	}
	//[ ( "@" / "+" ) ]//+ ?? pas d'espace a gerer
	std::cout << " :"<< count << " ";//<hopcount>
	std::cout << usr->getTruename();//<real name>
	return (RPL_WHOREPLY);
}


int who(std::vector<std::string> params, user* askingOne, std::vector<user*> usr_vec, std::vector<channel*> chan_vec, Server* srv){
	user*		usr = NULL;
	channel*	chan = NULL;
	int			hopcount = 0;
	//case where no params
	if (params.size() == 0){
		for(size_t i = 0; i < usr_vec.size(); ++i){
			if (usr_vec[i]->getMode() != 'i' && has1channelInCommon(askingOne, usr_vec[i]) == false)
				rpl_whoreply(usr_vec[i], hopcount++);
		}
		return (numeric_reply(RPL_ENDOFWHO, params[0], srv));
	}
	//case where mask has *
	size_t pos = params[0].find('*');//y a t il d'autre wildcard a gerer ?
	std::string mask(params[0]);
	if (pos != std::string::npos){
		if (mask.c_str()[0] == '*')
			mask.erase(0, 1);
		pos = mask.find('*');
		if (pos != std::string::npos)
			mask.erase(pos, mask.size() - pos);
		for (size_t i = 0; i < usr_vec.size(); ++i){
			if (usr_vec[i]->getNick().find(mask) != std::string::npos)
				rpl_whoreply(usr_vec[i], hopcount++);
		}
		return (numeric_reply(RPL_ENDOFWHO, params[0], srv));
	}
	//case mask is a correct full nickname or a channel's name
	usr = searchUserByNick(params[0], usr_vec);
	if (usr != NULL)
		numeric_reply(RPL_WHOREPLY, usr, srv);
	if (usr == NULL){
		chan = searchChannelByName(params[0], chan_vec);
		if (chan != NULL){
			std::map<user*, int> usr_map = chan->getUsr_list();
			for (std::map<user*, int>::iterator it = usr_map.begin(); it != usr_map.end(); ++it){
				rpl_whoreply(it->first, hopcount++);
			}
		}
	}
	return (numeric_reply(RPL_ENDOFWHO, params[0], srv));
}

