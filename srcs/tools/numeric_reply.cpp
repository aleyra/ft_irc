#include "tools.hpp"
//usr = user // don't know more...
//chan->getName() = channel // don't know more... maybe canal's id ?
//srv->name = server's name
//srv->mask = server's mask
//srv->host = host's server (always localhost)
//srv = server //don't know more...

int	numeric_reply(int err, user* usr, Server& srv){
	(void)srv;
	switch (err){
		case ERR_ERRONEUSNICKNAME:
			std::cout << /*srv->client <<*/ " " << usr->getNick() << ":Erroneus nickname" << std::endl;//weird
			break;
		case ERR_NICKCOLLISION:
			std::cout << /*srv->client <<*/ " " << usr->getNick() << ":Nickname collision KILL" << std::endl;
			break;
		case ERR_NOLOGIN:
			std::cout << /*srv->client <<*/ " " << usr << ":User not logged in" << std::endl;
			break;
		case RPL_UMODEIS:
			{/*std::cout << srv->client;*/
			std::string mode = usr->getMode();
			for (size_t i = 0; i < mode.size(); ++i){
				std::cout << mode[i] << " ";
			}
			std::cout << std::endl;}
			break;
		default:
			break;
	}
	return (err);
}

int	numeric_reply(int err, channel* chan, Server& srv){
	(void)srv;
	switch (err){
		case ERR_CANNOTSENDTOCHAN:
			std::cout << /*srv->client <<*/ " " << chan->getName() << ":Cannot send to channel" << std::endl;
			break;
		case ERR_TOOMANYCHANNELS:
			std::cout << /*srv->client <<*/ " " << chan->getName() << ":You have joined too many channels" << std::endl;
			break;
		case ERR_WASNOSUCHNICK:
			std::cout << /*srv->client <<*/ " " << chan->getName() << ":There was no such nickname" << std::endl;
			break;
		case ERR_NOTONCHANNEL:
			std::cout << /*srv->client <<*/ " " << chan->getName() << ":You're not on that channel" << std::endl;
			break;
		case ERR_KEYSET:
			std::cout << /*srv->client <<*/ " " << chan->getName() << ":Channel key already set" << std::endl;
			break;
		case ERR_CHANNELISFULL:
			std::cout << /*srv->client <<*/ " " << chan->getName() << ":Cannot join channel (+l)" << std::endl;
			break;
		case ERR_INVITEONLYCHAN:
			std::cout << /*srv->client <<*/ " " << chan->getName() << ":Cannot join channel (+i)" << std::endl;
			break;
		case ERR_BANNEDFROMCHAN:
			std::cout << /*srv->client <<*/ " " << chan->getName() << ":Cannot join channel (+b)" << std::endl;
			break;
		case ERR_BADCHANNELKEY:
			std::cout << /*srv->client <<*/ " " << chan->getName() << ":Cannot join channel (+k)" << std::endl;
			break;
		case ERR_CHANOPRIVSNEEDED:
			std::cout << /*srv->client <<*/ " " << chan->getName() << ":You're not channel operator" << std::endl;
			break;
		case RPL_NOTOPIC:
			std::cout << /*srv->client <<*/ " " << chan->getName() << " :No topic is set" << std::endl;
			break;
		case RPL_TOPIC:
			std::cout << /*srv->client <<*/ " " << chan->getName() << " :" << chan->getTopic() << std::endl;
			break;
		case ERR_NOCHANMODES:
			std::cout << /*srv->client <<*/ " " << chan->getName() << " :Channel doesn't support modes" << std::endl;
			break;
		default:
			break;
	}
	return (err);
}

int	numeric_reply(int err, std::string s, Server& srv){//s for cmd, operation, charactere, string
	(void)srv;
	switch (err){
		case ERR_NOSUCHCHANNEL:
			std::cout << /*srv->client <<*/ " " << s << ":No such channel" << std::endl;
			break;
		case ERR_NOSUCHNICK:
			std::cout << /*srv->client <<*/ " " << s << ":No such nick/channel" << std::endl;
			break;
		case ERR_TOOMANYTARGETS:
			std::cout << /*srv->client <<*/ " " << s << ":Duplicate recipients. No message delivered" << std::endl;
			break;
		case ERR_NORECIPIENT:
			std::cout << /*srv->client <<*/ " " << ":No recipient given (" << s << ")" << std::endl;
			break;
		case ERR_UNKNOWNCOMMAND:
			std::cout << /*srv->client <<*/ " " << s << ":Unknown command" << std::endl;
			break;
		case ERR_NEEDMOREPARAMS:
			std::cout << /*srv->client <<*/ " " << s << ":Not enough parameters" << std::endl;
			break;
		case ERR_UNKNOWNMODE:
			std::cout << /*srv->client <<*/ " " << s << ":is unknown mode char to me" << std::endl;
			break;
		case RPL_ENDOFWHO:
			std::cout << s << " :End of WHO list" << std::endl;
			break;
		case ERR_UNAVAILRESOURCE:
			std::cout << s << " :Nick/channel is temporarily unavailable" << std::endl;
			break;
		case ERR_NICKNAMEINUSE:
			std::cout << /*srv->client <<*/ " " << s << ":Nickname is already in use" << std::endl;
			break;
		case RPL_ENDOFNAMES://avec s comme param car le chan->getName() s peut de pas exister;
			std::cout << /*srv->client <<*/ " " << s << " :End of NAMES list" << std::endl;
			break;
		default:
			break;
	}
	return (err);
}

int	numeric_reply(int err, Server& srv){
	(void)srv;
	switch (err){
		case ERR_NOSUCHSERVER:
			std::cout << /*srv->client <<*/ " " << /*srv->name <<*/ ":No such server" << std::endl;
			break;
		case ERR_NOTOPLEVEL:
			std::cout << /*srv->client <<*/ " " << /*srv->mask <<*/ ":No toplevel domain specified" << std::endl;
			break;
		case ERR_WILDTOPLEVEL:
			std::cout << /*srv->client <<*/ " " << /*srv->mask <<*/ ":Wildcard in toplevel domain" << std::endl;
			break;
		case ERR_NOADMININFO:
			std::cout << /*srv->client <<*/ " " << /*srv <<*/ ":No administrative info available" << std::endl;
			break;
		//cases without specific info about server needed
		case ERR_NOORIGIN:
			std::cout << /*srv->client <<*/ ":No origin specified" << std::endl;
			break;
		case ERR_NOTEXTTOSEND:
			std::cout << /*srv->client <<*/ ":No text to send" << std::endl;
			break;
		case ERR_NOMOTD:
			std::cout << /*srv->client <<*/ ":MOTD File is missing" << std::endl;
			break;
		case ERR_NONICKNAMEGIVEN:
			std::cout << /*srv->client <<*/ ":No nickname given" << std::endl;
			break;
		case ERR_SUMMONDISABLED:
			std::cout << /*srv->client <<*/ ":SUMMON has been disabled" << std::endl;
			break;
		case ERR_USERSDISABLED:
			std::cout << /*srv->client <<*/ ":USERS has been disabled" << std::endl;
			break;
		case ERR_NOTREGISTERED:
			std::cout << /*srv->client <<*/ ":You have not registered" << std::endl;
			break;
		case ERR_ALREADYREGISTERED:
			std::cout << /*srv->client <<*/ ":Unauthorized command (already registered)" << std::endl;
			break;
		case ERR_NOPERMFORHOST:
			std::cout << /*srv->client <<*/ ":Your host isn't among the privileged" << std::endl;
			break;
		case ERR_PASSWDMISMATCH:
			std::cout << /*srv->client <<*/ ":Password incorrect" << std::endl;
			break;
		case ERR_YOUREBANNEDCREEP:
			std::cout << /*srv->client <<*/ ":You are banned from this server" << std::endl;
			break;
		case ERR_NOPRIVILEGES:
			std::cout << /*srv->client <<*/ ":Permission Denied- You're not an IRC operator" << std::endl;
			break;
		case ERR_CANTKILLSERVER:
			std::cout << /*srv->client <<*/ ":You cant kill a server!" << std::endl;
			break;
		case ERR_NOOPERHOST:
			std::cout << /*srv->client <<*/ ":No O-lines for your host" << std::endl;
			break;
		case ERR_UMODEUNKNOWNFLAG:
			std::cout << /*srv->client <<*/ ":Unknown MODE flag" << std::endl;
			break;
		case ERR_USERSDONTMATCH:
			std::cout << /*srv->client <<*/ ":Cant change mode for other users" << std::endl;
			break;
		case RPL_ENDOFWHOWAS:
			std::cout << /*srv->client <<*/ ":End of WHOWAS" << std::endl;
			break;
		case ERR_WASNOSUCHNICK:
			std::cout << /*srv->client <<*/ " :There was no such nickname" << std::endl;
			break;
		case RPL_UNAWAY:
			std::cout << /*srv->client <<*/ ":You are no longer marqued as being away" << std::endl;
			break;
		case RPL_NOWAWAY:
			std::cout << /*srv->client <<*/ ":You have been marked as being away" << std::endl;
			break;
		case ERR_RESTRICTED:
			std::cout << /*srv->client <<*/ ":Your connection is restricted!" << std::endl;
			break;
		case RPL_LISTEND:
			std::cout << /*srv->client <<*/ ":End of LIST" << std::endl;
			break;
		default:
			break;
	}
	return (err);
}

// int	numeric_reply(int err, std::string s/*, file f*/, Server& srv){
// 	switch (err){
// 	case ERR_FILEERROR:
// 		std::cout << /*srv->client <<*/ ":File error doing "<< s << " on " /*<< f.name */<< std::endl;
// 		break;
// 	default:
// 		break;
// 	}
// 	return (err);
// }

int	numeric_reply(int err, user* usr, channel* chan, Server& srv){
	(void)srv;
	switch (err){
		case ERR_USERNOTINCHANNEL:
			std::cout << /*srv->client <<*/ " " << usr->getNick() << " " << chan->getName() << ":They aren't on that channel" << std::endl;
			break;
		case ERR_USERONCHANNEL:
			std::cout << /*srv->client <<*/ " " << usr << " " << chan->getName() << ":is already on channel" << std::endl;
			break;
		default:
			break;
	}
	return (err);
}