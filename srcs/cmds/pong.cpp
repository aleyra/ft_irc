#include "cmds.hpp"

void	pong(std::vector<std::string> params, user &user, Server &server)//alors PONG n'a pas l'air d'envoyer quoique ce soit a user
{
	server.send("PONG ft_irc " + params[0] + "\n", user.getId());//du coup pourquoi ce send ?
}