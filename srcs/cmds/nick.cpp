#include "cmds.hpp"

int	nick(std::vector<std::string> params, user* askingOne,
	std::map<unsigned int, user *>& users, Server& srv){
	if (params.size() == 0)
		return (numeric_reply(ERR_NEEDMOREPARAMS, askingOne, "NICK", srv));
	//no indication on how to handle when there's more than 1 param -> ignored
	if (askingOne->hasMode('r') == true)
		return (numeric_reply(ERR_RESTRICTED, askingOne, srv));
	std::string nick(params[0]);
	//checking nick is valid
	if (nick.find(",") != std::string::npos ||
		nick.find("*") != std::string::npos ||
		nick.find("?") != std::string::npos ||
		nick.find("!") != std::string::npos ||
		nick.find("@") != std::string::npos){
		std::cout << /*srv->client <<*/ ERR_ERRONEUSNICKNAME << " " << askingOne->getNick() << " ";
		std::cout << nick << " :Erroneous nickname" <<std::endl;
		return (ERR_ERRONEUSNICKNAME);
	}
	if (nick.find("$") == 0 || nick.find(":") == 0){
		std::cout << /*srv->client <<*/ ERR_ERRONEUSNICKNAME << " " << askingOne->getNick() << " ";
		std::cout << nick << " :Erroneous nickname" <<std::endl;
		return (ERR_ERRONEUSNICKNAME);
	}
	if (nick.find("#") == 0 || nick.find("&") == 0){
		std::cout << /*srv->client <<*/ ERR_ERRONEUSNICKNAME << " " << askingOne->getNick() << " ";
		std::cout << nick << " :Erroneous nickname" <<std::endl;
		return (ERR_ERRONEUSNICKNAME);
	}
	if (nick.find(".") != std::string::npos){
		std::cout << /*srv->client <<*/ ERR_ERRONEUSNICKNAME << " " << askingOne->getNick() << " ";
		std::cout << nick << " :Erroneous nickname" <<std::endl;
		return (ERR_ERRONEUSNICKNAME);
	}
	//check if nick != actual_nick
	if (nick.compare(askingOne->getNick()) == 0)
			return (numeric_reply(ERR_NICKNAMEINUSE, askingOne, nick, srv));
	//check if there is already a user with this nick
	if (searchUserByNick(nick, users) != NULL){
			return (numeric_reply(ERR_UNAVAILRESOURCE, askingOne, nick, srv));
	}
	//update nick
	askingOne->setNick(nick);
	askingOne->addHistory_nick(askingOne->getNick());
	sendToAllInChanOfAskingOne(askingOne, askingOne->getNick() + "!~" + askingOne->getHistory_nick().front() + "@" + askingOne->getIp() + " " + "NICK :" + nick, srv);
	if (askingOne->getList_chan().empty() && askingOne->getHistory_nick().size() > 1)
		srv.send(":" + askingOne->getNick() + "!~" + askingOne->getHistory_nick().front() + "@" + askingOne->getIp() + " " + "NICK : " + nick, askingOne->getId());
	return (EXIT_SUCCESS);
}