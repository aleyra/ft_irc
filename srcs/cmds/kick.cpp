#include "cmds.hpp"

int	try_to_kick(std::string kicked, std::string msg, user *askingOne, channel* chan,
	std::map<unsigned int, user *>& users, Server &srv){
	user*							usr = NULL;
	std::map<unsigned int, int> &	usr_list = chan->getUsr_list();
	std::map<unsigned int, int>::iterator pos = usr_list.end();
	std::string						def_msg("bye kicked one");
	//check usr = kicked exists
	usr = searchUserByNick(kicked, users);
	if (usr == NULL)
		return (numeric_reply(ERR_NOSUCHNICK, askingOne, kicked, srv));
	//check usr is on chan
	pos = usr_list.find(usr->getId());
	if (pos == usr_list.end())
		numeric_reply(ERR_USERNOTINCHANNEL, askingOne, usr, chan, srv);
	//kick usr avec le message msg
	chan->rmUsr_list(usr);
	usr->rmList_chan(chan);
	if (msg.empty()){
		srv.send("KICK " + usr->getNick() + " :" + def_msg, askingOne->getId());
		for(std::map<unsigned int, int>::iterator it = usr_list.begin();
			it != usr_list.end(); ++it){
			if (it->first != askingOne->getId())
				srv.send("KICK " + usr->getNick() + " :" + def_msg, it->first);
		}
	}
	else{
		srv.send("KICK " + usr->getNick() + " :" + msg, askingOne->getId());
		for(std::map<unsigned int, int>::iterator it = usr_list.begin();
			it != usr_list.end(); ++it){
			if (it->first != askingOne->getId())
				srv.send("KICK " + usr->getNick() + " :" + msg, it->first);
		}
	}
	return (EXIT_SUCCESS);
}

int	kick(std::vector<std::string> params, user *askingOne,
	std::vector<channel *> &chan_vec, std::map<unsigned int, user *>& users, 
	Server &srv){
	if (params.size() < 2)
		return (numeric_reply(ERR_NEEDMOREPARAMS, askingOne, "KICK", srv));
	std::vector<std::string>	channels = paramsSeparedByComas(params[0]);
	std::vector<std::string>	kicked = paramsSeparedByComas(params[1]);
	std::string					msg("");
	channel*					chan = NULL;
	//preparation of msg. Can be empty
	for (size_t i = 2; i < params.size(); ++i){
		msg.append(params[i]);
		msg.append(" ");
	}
	for (size_t i = 0; i < channels.size(); ++i){
		//check chan exists
		chan = searchChannelByName(channels[i], chan_vec);
		if (chan == 0)
			return (numeric_reply(ERR_NOSUCHCHANNEL, askingOne, channels[i], srv));
		//check askingOne is on chan
		std::map<unsigned int, int> & usr_list = chan->getUsr_list();
		std::map<unsigned int, int>::iterator pos = usr_list.find(askingOne->getId());
		if (pos == usr_list.end())
			return (numeric_reply(ERR_NOTONCHANNEL, askingOne, chan, srv));
		//check askingOne is op on chan
		if (usr_list.at(askingOne->getId()) != CHAN_OP)
			return (numeric_reply(ERR_CHANOPRIVSNEEDED, askingOne, chan, srv));
		try_to_kick(kicked[0], msg, askingOne, chan, users, srv);
		if (channels.size() != 1 && kicked.size() != 1)
			break;
		if (channels.size() == 1){
			for (size_t j = 1; j < kicked.size(); ++j){
				try_to_kick(kicked[j], msg, askingOne, chan, users, srv);
			}
		}
	}
	return (EXIT_SUCCESS);
}

/*   Command: KICK
   Parameters: <channel> *( "," <channel> ) <user> *( "," <user> )
               [<comment>]

   The KICK command can be used to request the forced removal of a user
   from a channel.  It causes the <user> to PART from the <channel> by
   force.  For the message to be syntactically correct, there MUST be
   either one channel parameter and multiple user parameter, or as many
   channel parameters as there are user parameters.  If a "comment" is
   given, this will be sent instead of the default message, the nickname
   of the user issuing the KICK.

   The server MUST NOT send KICK messages with multiple channels or
   users to clients.  This is necessarily to maintain backward
   compatibility with old client software.

   Numeric Replies:

                         
           ERR_BADCHANMASK                 
                       */