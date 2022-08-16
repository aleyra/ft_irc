#include "cmds.hpp"

int	nick(std::vector<std::string> params, user* usr, std::map<int, user *>& users, Server* srv){
	//ERR_RESTRICTED ":Your connection is restricted!"
	/*Sent by the server to a user upon connection to indicate the restricted
		nature of the connection (user mode "+r").*/
	if (params.size() == 0)
		return (numeric_reply(ERR_NEEDMOREPARAMS, "NICK", srv));
	//pas de precision sur comment gerer quand plus de 1 param

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
	if (nick.compare(usr->getNick()) == 0)
		return (numeric_reply(ERR_NICKNAMEINUSE, usr, srv));
	if (searchUserByNick(nick, users) != NULL)
		return (numeric_reply(ERR_UNAVAILRESOURCE, nick, srv));
	usr->addHistory_nick(usr->getNick());
	usr->setNick(nick);
	return (EXIT_SUCCESS);
}