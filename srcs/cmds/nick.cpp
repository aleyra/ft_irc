#include "cmds.hpp"

int	nick(std::vector<std::string> params, user* askingOne, user& usr,
	std::map<unsigned int, user *>& users, Server& srv){
	if (params.size() == 0)
		return (numeric_reply(ERR_NEEDMOREPARAMS, askingOne, "NICK", srv));
	//no indication on how to handle when there's more than 1 param -> ignored
	if (usr.hasMode('r') == true)
		return (numeric_reply(ERR_RESTRICTED, askingOne, srv));
	std::string nick(params[0]);
	//checking nick is valid
	if (nick.find(",") != std::string::npos ||
		nick.find("*") != std::string::npos ||
		nick.find("?") != std::string::npos ||
		nick.find("!") != std::string::npos ||
		nick.find("@") != std::string::npos){
		std::cout << /*srv->client <<*/ << ERR_ERRONEUSNICKNAME << " " << askingOne->getNick() << " ";
		std::cout << nick << " :Erroneous nickname" <<std::endl;
		return (ERR_ERRONEUSNICKNAME);
	}
	if (nick.find("$") == 0 || nick.find(":") == 0){
		std::cout << /*srv->client <<*/ << ERR_ERRONEUSNICKNAME << " " << askingOne->getNick() << " ";
		std::cout << nick << " :Erroneous nickname" <<std::endl;
		return (ERR_ERRONEUSNICKNAME);
	}
	if (nick.find("#") == 0 || nick.find("&") == 0){
		std::cout << /*srv->client <<*/ << ERR_ERRONEUSNICKNAME << " " << askingOne->getNick() << " ";
		std::cout << nick << " :Erroneous nickname" <<std::endl;
		return (ERR_ERRONEUSNICKNAME);
	}
	if (nick.find(".") != std::string::npos){
		std::cout << /*srv->client <<*/ << ERR_ERRONEUSNICKNAME << " " << askingOne->getNick() << " ";
		std::cout << nick << " :Erroneous nickname" <<std::endl;
		return (ERR_ERRONEUSNICKNAME);
	}
	if (nick.compare(usr.getNick()) == 0)
		return (numeric_reply(ERR_NICKNAMEINUSE, askingOne, nick, srv));
	if (searchUserByNick(nick, users) != NULL)
		return (numeric_reply(ERR_UNAVAILRESOURCE, askingOne, nick, srv));
	usr.addHistory_nick(usr.getNick());
	usr.setNick(nick);
	return (EXIT_SUCCESS);
}