#include "tools.hpp"

int	numeric_reply(int err, user* askingOne, user* usr, Server& srv){
	switch (err){
		case ERR_ERRONEUSNICKNAME:
			srv.send(to_string(err) + " " + askingOne->getNick() + " " + usr->getNick() + " :Erroneus nickname", askingOne->getId());
			break;
		case ERR_NICKCOLLISION:
			srv.send(to_string(err) + " " + askingOne->getNick() + " " + usr->getNick() + " :Nickname collision KILL", askingOne->getId());
			break;
		case ERR_NOLOGIN:
			srv.send(to_string(err) + " " + askingOne->getNick() + " " + usr->getNick() + " :User not logged in", askingOne->getId());
			break;
		case RPL_UMODEIS:
			srv.send(to_string(err) + " " + askingOne->getNick() + " +" + usr->getMode(), askingOne->getId());
			break;
		default:
			break;
	}
	return (err);
}

int	numeric_reply(int err, user* askingOne, channel* chan, Server& srv){
	switch (err){
		case ERR_CANNOTSENDTOCHAN:
			srv.send(to_string(err) + " " + askingOne->getNick() + " " + chan->getName() + " :Cannot send to channel", askingOne->getId());
			break;
		case ERR_TOOMANYCHANNELS:
			srv.send(to_string(err) + " " + askingOne->getNick() + " " + chan->getName() + " :You have joined too many channels", askingOne->getId());
			break;
		case ERR_WASNOSUCHNICK:
			srv.send(to_string(err) + " " + askingOne->getNick() + " " + chan->getName() + " :There was no such nickname", askingOne->getId());
			break;
		case ERR_NOTONCHANNEL:
			srv.send(to_string(err) + " " + askingOne->getNick() + " " + chan->getName() + " :You're not on that channel", askingOne->getId());
			break;
		case ERR_KEYSET:
			srv.send(to_string(err) + " " + askingOne->getNick() + " " + chan->getName() + " :Channel key already set", askingOne->getId());
			break;
		case ERR_CHANNELISFULL:
			srv.send(to_string(err) + " " + askingOne->getNick() + " " + chan->getName() + " :Cannot join channel (+l)", askingOne->getId());
			break;
		case ERR_INVITEONLYCHAN:
			srv.send(to_string(err) + " " + askingOne->getNick() + " " + chan->getName() + " :Cannot join channel (+i)", askingOne->getId());
			break;
		case ERR_BANNEDFROMCHAN:
			srv.send(to_string(err) + " " + askingOne->getNick() + " " + chan->getName() + " :Cannot join channel (+b)", askingOne->getId());
			break;
		case ERR_BADCHANNELKEY:
			srv.send(to_string(err) + " " + askingOne->getNick() + " " + chan->getName() + " :Cannot join channel (+k)", askingOne->getId());
			break;
		case ERR_CHANOPRIVSNEEDED:
			srv.send(to_string(err) + " " + askingOne->getNick() + " " + chan->getName() + " :You're not channel operator", askingOne->getId());
			break;
		case RPL_NOTOPIC:
			srv.send(to_string(err) + " " + askingOne->getNick() + " " + chan->getName() + " :No topic is set", askingOne->getId());
			break;
		case RPL_TOPIC:
			srv.send(to_string(err) + " " + askingOne->getNick() + " " + chan->getName() + " :" + chan->getTopic(), askingOne->getId());
			break;
		case ERR_NOCHANMODES:
			srv.send(to_string(err) + " " + askingOne->getNick() + " " + chan->getName() + " :Channel doesn't support modes", askingOne->getId());
			break;
		case RPL_CHANNELMODEIS://"<client> <channel> <modestring> <mode arguments>..."
			{
				srv.send(to_string(err) + " " + askingOne->getNick() + " " + chan->getName() + " +" + chan->getMode(), askingOne->getId());
				//<mode arguments> ?????
			}
			break;
		default:
			break;
	}
	return (err);
}

int	numeric_reply(int err, user* askingOne, std::string s, Server& srv){//s for cmd, operation, charactere, string
	switch (err){
		case ERR_NOSUCHCHANNEL:
			{
				if (!s.empty())
					srv.send(to_string(err) + " " + askingOne->getNick() + " " + s + " :No such channel", askingOne->getId());
				else
					srv.send(to_string(err) + " " + askingOne->getNick() + " :No such channel", askingOne->getId());
			break;
		case ERR_NOSUCHNICK:
			{
				if (!s.empty())
					srv.send(to_string(err) + " " + askingOne->getNick() + " " + s + " :No such nick/channel", askingOne->getId());
				else
					srv.send(to_string(err) + " " + askingOne->getNick() + " :No such nick/channel", askingOne->getId());
			}
			break;
		case ERR_TOOMANYTARGETS:
			{
				if (!s.empty())
					srv.send(to_string(err) + " " + askingOne->getNick() + " " + s + " :Duplicate recipients. No message delivered", askingOne->getId());
				else
					srv.send(to_string(err) + " " + askingOne->getNick() + " :Duplicate recipients. No message delivered", askingOne->getId());
			}
			break;
		case ERR_NORECIPIENT:
			srv.send(to_string(err) + " " + askingOne->getNick() + " " + ":No recipient given (" + s + ")", askingOne->getId());
			break;
		case ERR_UNKNOWNCOMMAND:
			{
				if (!s.empty())
					srv.send(to_string(err) + " " + askingOne->getNick() + " " + s + " :Unknown command", askingOne->getId());
				else
					srv.send(to_string(err) + " " + askingOne->getNick() + " :Unknown command", askingOne->getId());
			}
			break;
		case ERR_NEEDMOREPARAMS:
			{
				if (!s.empty())
					srv.send(to_string(err) + " " + askingOne->getNick() + " " + s + " :Not enough parameters", askingOne->getId());
				else
					srv.send(to_string(err) + " " + askingOne->getNick() + " " + s + " :Not enough parameters", askingOne->getId());
			}
			break;
		case ERR_UNKNOWNMODE:
			{
				if (!s.empty())
					srv.send(to_string(err) + " " + askingOne->getNick() + " " + s + " :is unknown mode char to me", askingOne->getId());
				else
					srv.send(to_string(err) + " " + askingOne->getNick() + " :is unknown mode char to me", askingOne->getId());
			}
			break;
		case RPL_ENDOFWHO:
			{
				if (!s.empty())
					srv.send(to_string(err) + " " + askingOne->getNick() + " " + s + " :End of WHO list", askingOne->getId());
				else
					srv.send(to_string(err) + " " + askingOne->getNick() + " :End of WHO list", askingOne->getId());
			}
			break;
		case ERR_UNAVAILRESOURCE:
			{
				if (!s.empty())
					srv.send(to_string(err) + " " + askingOne->getNick() + " " + s + " :Nick/channel is temporarily unavailable", askingOne->getId());
				else
					srv.send(to_string(err) + " " + askingOne->getNick() + " :Nick/channel is temporarily unavailable", askingOne->getId());
			}
			break;
		case ERR_NICKNAMEINUSE:
			{
				if (!s.empty())
					srv.send(to_string(err) + " " + askingOne->getNick() + " " + s + " :Nickname is already in use", askingOne->getId());
				else
					srv.send(to_string(err) + " " + askingOne->getNick() + " :Nickname is already in use", askingOne->getId());
			}
			break;
		case RPL_ENDOFNAMES://avec s comme param car le chan->getName() s peut de pas exister;
			{
				if (!s.empty())
					srv.send(to_string(err) + " " + askingOne->getNick() + " " + s + " :End of NAMES list", askingOne->getId());
				else
					srv.send(to_string(err) + " " + askingOne->getNick() + " :End of NAMES list", askingOne->getId());
			}
			break;
		case RPL_YOUREOPER:
			{
				if (!s.empty())
					srv.send(to_string(err) + " " + askingOne->getNick() + " " + s + " :You are now an IRC operator", askingOne->getId());
				else
					srv.send(to_string(err) + " " + askingOne->getNick() + " :You are now an IRC operator", askingOne->getId());
			}
			break;
		default:
			break;
	}
	return (err);
}

int	numeric_reply(int err, user* askingOne, Server& srv){
	switch (err){
		case RPL_WELCOME:
			srv.send("001 " + askingOne->getNick() + " " + ":Welcome to the ft_irc Network, " + askingOne->getNick() + "!", askingOne->getId());
			break;
		case RPL_YOURHOST:
			srv.send("002 " + askingOne->getNick() + " " + ":Your host is ft_irc, running version -1", askingOne->getId());
			break;
		case RPL_CREATED:
			srv.send("003 " + askingOne->getNick() + " " + ":This server was created: way too long ago", askingOne->getId());
			break;
		case RPL_MYINFO:
			srv.send("004 " + askingOne->getNick() + " " + askingOne->getIp() + " ft_irc -1 iro ovimpst", askingOne->getId());
			break;
		case ERR_NOSUCHSERVER:
			srv.send(to_string(err) + " " + askingOne->getNick() + " " + /*srv->name +*/ ":No such server", askingOne->getId());
			break;
		case ERR_NOTOPLEVEL:
			srv.send(to_string(err) + " " + askingOne->getNick() + " " + /*srv->mask +*/ ":No toplevel domain specified", askingOne->getId());
			break;
		case ERR_WILDTOPLEVEL:
			srv.send(to_string(err) + " " + askingOne->getNick() + " " + /*srv->mask +*/ ":Wildcard in toplevel domain", askingOne->getId());
			break;
		case ERR_NOADMININFO:
			srv.send(to_string(err) + " " + askingOne->getNick() + " " + /*srv +*/ ":No administrative info available", askingOne->getId());
			break;
		//cases without specific info about server needed
		case ERR_NOORIGIN:
			srv.send(to_string(err) + " " + askingOne->getNick() + " " + ":No origin specified", askingOne->getId());
			break;
		case ERR_NOTEXTTOSEND:
			srv.send(to_string(err) + " " + askingOne->getNick() + " " + ":No text to send", askingOne->getId());
			break;
		case ERR_NOMOTD:
			srv.send(to_string(err) + " " + askingOne->getNick() + " " + ":MOTD File is missing", askingOne->getId());
			break;
		case ERR_NONICKNAMEGIVEN:
			srv.send(to_string(err) + " " + askingOne->getNick() + " " + ":No nickname given", askingOne->getId());
			break;
		case ERR_SUMMONDISABLED:
			srv.send(to_string(err) + " " + askingOne->getNick() + " " + ":SUMMON has been disabled", askingOne->getId());
			break;
		case ERR_USERSDISABLED:
			srv.send(to_string(err) + " " + askingOne->getNick() + " " + ":USERS has been disabled", askingOne->getId());
			break;
		case ERR_NOTREGISTERED:
			srv.send(to_string(err) + " " + askingOne->getNick() + " " + ":You have not registered", askingOne->getId());
			break;
		case ERR_ALREADYREGISTERED:
			srv.send(to_string(err) + " " + askingOne->getNick() + " " + ":Unauthorized command (already registered)", askingOne->getId());
			break;
		case ERR_NOPERMFORHOST:
			srv.send(to_string(err) + " " + askingOne->getNick() + " " + ":Your host isn't among the privileged", askingOne->getId());
			break;
		case ERR_PASSWDMISMATCH:
			srv.send(to_string(err) + " " + askingOne->getNick() + " " + ":Password incorrect", askingOne->getId());
			break;
		case ERR_YOUREBANNEDCREEP:
			srv.send(to_string(err) + " " + askingOne->getNick() + " " + ":You are banned from this server", askingOne->getId());
			break;
		case ERR_NOPRIVILEGES:
			srv.send(to_string(err) + " " + askingOne->getNick() + " " + ":Permission Denied- You're not an IRC operator", askingOne->getId());
			break;
		case ERR_CANTKILLSERVER:
			srv.send(to_string(err) + " " + askingOne->getNick() + " " + ":You cant kill a server!", askingOne->getId());
			break;
		case ERR_NOOPERHOST:
			srv.send(to_string(err) + " " + askingOne->getNick() + " " + ":No O-lines for your host", askingOne->getId());
			break;
		case ERR_UMODEUNKNOWNFLAG:
			srv.send(to_string(err) + " " + askingOne->getNick() + " " + ":Unknown MODE flag", askingOne->getId());
			break;
		case ERR_USERSDONTMATCH:
			srv.send(to_string(err) + " " + askingOne->getNick() + " " + ":Cant change mode for other users", askingOne->getId());
			break;
		case RPL_ENDOFWHOWAS:
			srv.send(to_string(err) + " " + askingOne->getNick() + " " + ":End of WHOWAS", askingOne->getId());
			break;
		case ERR_WASNOSUCHNICK:
			srv.send(to_string(err) + " " + askingOne->getNick() + " " + " :There was no such nickname", askingOne->getId());
			break;
		case RPL_UNAWAY:
			srv.send(to_string(err) + " " + askingOne->getNick() + " " + ":You are no longer marqued as being away", askingOne->getId());
			break;
		case RPL_NOWAWAY:
			srv.send(to_string(err) + " " + askingOne->getNick() + " " + ":You have been marked as being away", askingOne->getId());
			break;
		case ERR_RESTRICTED:
			srv.send(to_string(err) + " " + askingOne->getNick() + " " + ":Your connection is restricted!", askingOne->getId());
			break;
		case RPL_LISTEND:
			srv.send(to_string(err) + " " + askingOne->getNick() + " " + ":End of LIST", askingOne->getId());
			break;
		default:
			break;
	}
	return (err);
}

int	numeric_reply(int err, user* askingOne, user* usr, channel* chan, Server& srv){
	switch (err){
		case ERR_USERNOTINCHANNEL:
			srv.send(to_string(err) + " " + askingOne->getNick() + " " + usr->getNick() + " " + chan->getName() + " :They aren't on that channel", askingOne->getId());
			break;
		case ERR_USERONCHANNEL:
			srv.send(to_string(err) + " " + askingOne->getNick() + " " + usr->getNick() + " " + chan->getName() + " :is already on channel", askingOne->getId());
			break;
		case RPL_INVITING:
			srv.send(to_string(err) + " " + askingOne->getNick() + " " + chan->getName() + " " + usr->getNick(), askingOne->getId());
			break;
		default:
			break;
	}
	return (err);
}