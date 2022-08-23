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
		if (!askingOne->getNick().empty())
			return (numeric_reply(ERR_UNAVAILRESOURCE, askingOne, nick, srv));
		//send :NickServ!NickServ@services.libera.chat NOTICE airi :This nickname is registered. Please choose a different nickname, or identify via /msg NickServ IDENTIFY daru <password>
		//envoyer apres avoir donner acces au server (donc apres NICK + USER) mais laisser le nick s'enregistrer. ca n'empechera pas l'utilisation du server par la suite
	}
	//update nick
	askingOne->addHistory_nick(askingOne->getNick());
	askingOne->setNick(nick);
	if (askingOne->getFirstNickGiven() == false)
		askingOne->setFirstNickGiven(true);
	sendToAllInChanOfAskingOne(askingOne, "NICK :" + nick, srv);
	return (EXIT_SUCCESS);
}