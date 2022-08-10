#include "numeric_reply.hpp"
//usr = user // don't know more...
	//usr.idle_time = time since last activity in seconds
//srv.name = server's name
//srv.mask = server's mask
	//srv.host = host's server
//srv = server //don't know more...
	//srv.info = server's info
//chan.name = channel's name
	//chan = channel // don't know more... maybe canal's id ?

int	error_msg(int err, user usr){
	switch (err){
	case ERR_ERRONEUSNICKNAME:
		std::cout << usr.getNick() << ":Erroneus nickname" << std::endl;//weird
		break;
	case ERR_NICKNAMEINUSE:
		std::cout << usr.getNick() << ":Nickname is already in use" << std::endl;
		break;
	case ERR_NICKCOLLISION:
		std::cout << usr.getNick() << ":Nickname collision KILL" << std::endl;
		break;
	case ERR_NOLOGIN:
		std::cout << usr << ":User not logged in" << std::endl;
		break;
	// case RPL_AWAY:
	// 	std::cout << usr.getNick() << ":" << usr.getAway_msg() << std::endl;
	// 	break;	
	default:
		break;
	}
	return (err);
}

int	error_msg(int err, server srv){
	switch (err){
	case ERR_NOSUCHSERVER:
		std::cout << srv.name << ":No such serve" << std::endl;
		break;
	case ERR_NOTOPLEVEL:
		std::cout << srv.mask << ":No toplevel domain specified" << std::endl;
		break;
	case ERR_WILDTOPLEVEL:
		std::cout << srv.mask << ":Wildcard in toplevel domain" << std::endl;
		break;
	case ERR_NOADMININFO:
		std::cout << srv << ":No administrative info available" << std::endl;
		break;
	default:
		break;
	}
	return (err);
}

int	error_msg(int err, channel chan){
	switch (err){
	case ERR_NOSUCHCHANNEL:
		std::cout << chan.name << ":No such channel" << std::endl;
		break;
	case ERR_CANNOTSENDTOCHAN:
		std::cout << chan.name << ":Cannot send to channel" << std::endl;
		break;
	case ERR_TOOMANYCHANNELS:
		std::cout << chan.name << ":You have joined too many channels" << std::endl;
		break;
	case ERR_WASNOSUCHNICK:
		std::cout << chan.name << ":There was no such nickname" << std::endl;
		break;
	case ERR_NOTONCHANNEL:
		std::cout << chan << ":You're not on that channel" << std::endl;
		break;
	case ERR_KEYSET:
		std::cout << chan << ":Channel key already set" << std::endl;
		break;
	case ERR_CHANNELISFULL:
		std::cout << chan << ":Cannot join channel (+l)" << std::endl;
		break;
	case ERR_INVITEONLYCHAN:
		std::cout << chan << ":Cannot join channel (+i)" << std::endl;
		break;
	case ERR_BANNEDFROMCHAN:
		std::cout << chan << ":Cannot join channel (+b)" << std::endl;
		break;
	case ERR_BADCHANNELKEY:
		std::cout << chan << ":Cannot join channel (+k)" << std::endl;
		break;
	case ERR_CHANOPRIVSNEEDED:
		std::cout << chan << ":You're not channel operator" << std::endl;
		break;
	default:
		break;
	}
	return (err);
}

int	error_msg(int err, std::string s){//s for cmd, operation, charactere, string
	switch (err){
	case ERR_NOSUCHNICK:
		std::cout << s << ":No such nick/channel" << std::endl;
		break;
	case ERR_TOOMANYTARGETS:
		std::cout << s << ":Duplicate recipients. No message delivered" << std::endl;
		break;
	case ERR_NORECIPIENT:
		std::cout << ":No recipient given (" << s << ")" << std::endl;
		break;
	case ERR_UNKNOWNCOMMAND:
		std::cout << s << ":Unknown command" << std::endl;
		break;
	case ERR_NEEDMOREPARAMS:
		std::cout << s << ":Not enough parameters" << std::endl;
		break;
	case ERR_UNKNOWNMODE:
		std::cout << s << ":is unknown mode char to me" << std::endl;
		break;
	// case RPL_ISON://to be used with a 'for' for each nick in the cmd ISON separate by a ' ' et a '\n' right after the 'for'
	// 	if (is_user(s) == TRUE) std::cout << s;
	// 	break;
	default:
		break;
	}
	return (err);
}

int	error_msg(int err){
	switch (err){
	case ERR_NOORIGIN:
		std::cout << ":No origin specified" << std::endl;
		break;
	case ERR_NOTEXTTOSEND:
		std::cout << ":No text to send" << std::endl;
		break;
	case ERR_NOMOTD:
		std::cout << ":MOTD File is missing" << std::endl;
		break;
	case ERR_NONICKNAMEGIVEN:
		std::cout << ":No nickname given" << std::endl;
		break;
	case ERR_SUMMONDISABLED:
		std::cout << ":SUMMON has been disabled" << std::endl;
		break;
	case ERR_USERSDISABLED:
		std::cout << ":USERS has been disabled" << std::endl;
		break;
	case ERR_NOTREGISTERED:
		std::cout << ":You have not registered" << std::endl;
		break;
	case ERR_ALREADYREGISTRED:
		std::cout << ":You may not reregister" << std::endl;
		break;
	case ERR_NOPERMFORHOST:
		std::cout << ":Your host isn't among the privileged" << std::endl;
		break;
	case ERR_PASSWDMISMATCH:
		std::cout << ":Password incorrect" << std::endl;
		break;
	case ERR_YOUREBANNEDCREEP:
		std::cout << ":You are banned from this server" << std::endl;
		break;
	case ERR_NOPRIVILEGES:
		std::cout << ":Permission Denied- You're not an IRC operator" << std::endl;
		break;
	case ERR_CANTKILLSERVER:
		std::cout << ":You cant kill a server!" << std::endl;
		break;
	case ERR_NOOPERHOST:
		std::cout << ":No O-lines for your host" << std::endl;
		break;
	case ERR_UMODEUNKNOWNFLAG:
		std::cout << ":Unknown MODE flag" << std::endl;
		break;
	case ERR_USERSDONTMATCH:
		std::cout << ":Cant change mode for other users" << std::endl;
		break;
	// case RPL_UNAWAY:
	// 	std::cout << ":You are no longer marqued as being away" << std::endl;
	// 	break;
	// case RPL_NOWAWAY:
	// 	std::cout << ":You have been marked as being away" << std::endl;
	// 	break;
	default:
		break;
	}
	return (err);
}

int	error_msg(int err, std::string s/*, file f*/){
	switch (err){
	case ERR_FILEERROR:
		std::cout << ":File error doing "<< s << " on " /*<< f.name */<< std::endl;
		break;
	default:
		break;
	}
	return (err);
}

int	error_msg(int err, user usr, channel chan){
	switch (err){
	case ERR_USERNOTINCHANNEL:
		std::cout << usr.getNick() << " " << chan << ":They aren't on that channel" << std::endl;
		break;
	case ERR_USERONCHANNEL:
		std::cout << usr << " " << chan << ":is already on channel" << std::endl;
		break;
	default:
		break;
	}
	return (err);
}

// int	error_msg(int err, user usr, server srv){
// 	switch (err){
// 	case RPL_USERHOST://to be used with a 'for' for each nick in the cmd USERHOST separate by a ' ' et a '\n' right after the 'for'
// 		std::cout << usr.getNick() << "[";
// 		if (usr.getLvl() == 2) std::cout << "operator";
// 		else std::cout << "non operator";
// 		std::cout << "] = <";
// 		if (usr.getAway() == TRUE) std::cout << usr.getAway_msg();
// 		std::cout << ">" << srv.host;
// 		break;
// 	case RPL_WHOISUSER:
// 		std::cout << usr.getNick() << " " << usr << srv.host << "*:" << usr.getTruename() << std::endl;
// 		break;
// 	case RPL_WHOISSERVER:
// 		std::cout << usr.getNick() << " " << srv << ":" << srv.info << std::endl;
// 		break;
// 	}
// return (err);
// }

// case /* constant-expression */:
// 		/* code */
// 		break;
