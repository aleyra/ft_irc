#include "numeric_reply.hpp"
//usr.nick = nickname
//usr = user // don't know more...
	//usr.lvl = access lvl
	//usr.away = boolean : if user is away return TRUE
	//usr.away_msg = automatic msg setting by user when away
	//usr.true_name = user's true name ?!
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
		std::cout << usr.nick << ":Erroneus nickname\n";//weird
		break;
	case ERR_NICKNAMEINUSE:
		std::cout << usr.nick << ":Nickname is already in use\n";
		break;
	case ERR_NICKCOLLISION:
		std::cout << usr.nick << ":Nickname collision KILL\n";
		break;
	case ERR_NOLOGIN:
		std::cout << usr << ":User not logged in\n";
		break;
	// case RPL_AWAY:
	// 	std::cout << usr.nick << ":" << usr.away_msg << std::endl;
	// 	break;	
	default:
		break;
	}
	return (err);
}

int	error_msg(int err, server srv){
	switch (err){
	case ERR_NOSUCHSERVER:
		std::cout << srv.name << ":No such serve\n";
		break;
	case ERR_NOTOPLEVEL:
		std::cout << srv.mask << ":No toplevel domain specified\n";
		break;
	case ERR_WILDTOPLEVEL:
		std::cout << srv.mask << ":Wildcard in toplevel domain\n";
		break;
	case ERR_NOADMININFO:
		std::cout << srv << ":No administrative info available\n";
		break;
	default:
		break;
	}
	return (err);
}

int	error_msg(int err, channel chan){
	switch (err){
	case ERR_NOSUCHCHANNEL:
		std::cout << chan.name << ":No such channel\n";
		break;
	case ERR_CANNOTSENDTOCHAN:
		std::cout << chan.name << ":Cannot send to channel\n";
		break;
	case ERR_TOOMANYCHANNELS:
		std::cout << chan.name << ":You have joined too many channels\n";
		break;
	case ERR_WASNOSUCHNICK:
		std::cout << chan.name << ":There was no such nickname\n";
		break;
	case ERR_NOTONCHANNEL:
		std::cout << chan << ":You're not on that channel\n";
		break;
	case ERR_KEYSET:
		std::cout << chan << ":Channel key already set\n";
		break;
	case ERR_CHANNELISFULL:
		std::cout << chan << ":Cannot join channel (+l)\n";
		break;
	case ERR_INVITEONLYCHAN:
		std::cout << chan << ":Cannot join channel (+i)\n";
		break;
	case ERR_BANNEDFROMCHAN:
		std::cout << chan << ":Cannot join channel (+b)\n";
		break;
	case ERR_BADCHANNELKEY:
		std::cout << chan << ":Cannot join channel (+k)\n";
		break;
	case ERR_CHANOPRIVSNEEDED:
		std::cout << chan << ":You're not channel operator\n";
		break;
	default:
		break;
	}
	return (err);
}

int	error_msg(int err, std::string s){//s for cmd, operation, charactere, string
	switch (err){
	case ERR_NOSUCHNICK:
		std::cout << s << ":No such nick/channel\n";
		break;
	case ERR_TOOMANYTARGETS:
		std::cout << s << ":Duplicate recipients. No message delivered\n";
		break;
	case ERR_NORECIPIENT:
		std::cout << ":No recipient given (" << s << ")\n";
		break;
	case ERR_UNKNOWNCOMMAND:
		std::cout << s << ":Unknown command\n";
		break;
	case ERR_NEEDMOREPARAMS:
		std::cout << s << ":Not enough parameters\n";
		break;
	case ERR_UNKNOWNMODE:
		std::cout << s << ":is unknown mode char to me\n";
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
		std::cout << ":No origin specified\n";
		break;
	case ERR_NOTEXTTOSEND:
		std::cout << ":No text to send\n";
		break;
	case ERR_NOMOTD:
		std::cout << ":MOTD File is missing\n";
		break;
	case ERR_NONICKNAMEGIVEN:
		std::cout << ":No nickname given\n";
		break;
	case ERR_SUMMONDISABLED:
		std::cout << ":SUMMON has been disabled\n";
		break;
	case ERR_USERSDISABLED:
		std::cout << ":USERS has been disabled\n";
		break;
	case ERR_NOTREGISTERED:
		std::cout << ":You have not registered\n";
		break;
	case ERR_ALREADYREGISTRED:
		std::cout << ":You may not reregister\n";
		break;
	case ERR_NOPERMFORHOST:
		std::cout << ":Your host isn't among the privileged\n";
		break;
	case ERR_PASSWDMISMATCH:
		std::cout << ":Password incorrect\n";
		break;
	case ERR_YOUREBANNEDCREEP:
		std::cout << ":You are banned from this server\n";
		break;
	case ERR_NOPRIVILEGES:
		std::cout << ":Permission Denied- You're not an IRC operator\n";
		break;
	case ERR_CANTKILLSERVER:
		std::cout << ":You cant kill a server!\n";
		break;
	case ERR_NOOPERHOST:
		std::cout << ":No O-lines for your host\n";
		break;
	case ERR_UMODEUNKNOWNFLAG:
		std::cout << ":Unknown MODE flag\n";
		break;
	case ERR_USERSDONTMATCH:
		std::cout << ":Cant change mode for other users\n";
		break;
	// case RPL_UNAWAY:
	// 	std::cout << ":You are no longer marqued as being away\n";
	// 	break;
	// case RPL_NOWAWAY:
	// 	std::cout << ":You have been marked as being away\n";
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
		std::cout << usr.nick << " " << chan << ":They aren't on that channel\n";
		break;
	case ERR_USERONCHANNEL:
		std::cout << usr << " " << chan << ":is already on channel\n";
		break;
	default:
		break;
	}
	return (err);
}

// int	error_msg(int err, user usr, server srv){
// 	switch (err){
// 	case RPL_USERHOST://to be used with a 'for' for each nick in the cmd USERHOST separate by a ' ' et a '\n' right after the 'for'
// 		std::cout << usr.nick << "[";
// 		if (usr.lvl == 2) std::cout << "operator";
// 		else std::cout << "non operator";
// 		std::cout << "] = <";
// 		if (usr.away == TRUE) std::cout << usr.away_msg;
// 		std::cout << ">" << srv.host;
// 		break;
// 	case RPL_WHOISUSER:
// 		std::cout << usr.nick << " " << usr << srv.host << "*:" << usr.true_name << std::endl;
// 		break;
// 	case RPL_WHOISSERVER:
// 		std::cout << usr.nick << " " << srv << ":" << srv.info << std::endl;
// 		break;
// 	}
// return (err);
// }

// case /* constant-expression */:
// 		/* code */
// 		break;
