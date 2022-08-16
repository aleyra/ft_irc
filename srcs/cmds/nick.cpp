#include "cmds.hpp"

int	nick(std::vector<std::string> params, user& usr, std::map<int, user *>& users, Server& srv){
	if (params.size() == 0)
		return (numeric_reply(ERR_NEEDMOREPARAMS, "NICK", srv));
	//no indication on how to handle when there's more than 1 param -> ignored
	if (usr.getMode() == 'r')
		return (numeric_reply(ERR_RESTRICTED, srv));
	std::string nick(params[0]);
	//checking nick is valid
	if (nick.find(",") != std::string::npos ||
		nick.find("*") != std::string::npos ||
		nick.find("?") != std::string::npos ||
		nick.find("!") != std::string::npos ||
		nick.find("@") != std::string::npos){
		std::cout << nick << " :Erroneous nickname" <<std::endl;
		return (ERR_ERRONEUSNICKNAME);
	}
	if (nick.find("$") == 0 || nick.find(":") == 0){
		std::cout << nick << " :Erroneous nickname" <<std::endl;
		return (ERR_ERRONEUSNICKNAME);
	}
	if (nick.find("#") == 0 || nick.find("&") == 0){
		std::cout << nick << " :Erroneous nickname" <<std::endl;
		return (ERR_ERRONEUSNICKNAME);
	}
	if (nick.find(".") != std::string::npos){
		std::cout << nick << " :Erroneous nickname" <<std::endl;
		return (ERR_ERRONEUSNICKNAME);
	}
	if (nick.compare(usr.getNick()) == 0)
		return (numeric_reply(ERR_NICKNAMEINUSE, nick, srv));
	if (searchUserByNick(nick, users) != NULL)
		return (numeric_reply(ERR_UNAVAILRESOURCE, nick, srv));
	usr.addHistory_nick(usr.getNick());
	usr.setNick(nick);
	return (EXIT_SUCCESS);
}