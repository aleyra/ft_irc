#ifndef CMDS_HPP
# define CMDS_HPP

#include "tools.hpp"
#include "user.hpp"
#include "Server.hpp"
#include "channel.hpp"
#include <cstdlib>
#include <cstring>

// int	away(std::string txt, user*	usr, Server& srv);
int		invite(std::vector<std::string> params, user* askingOne,
			std::map<unsigned int, user *>& users, std::vector<channel *> &chan_vec,
			Server* srv);//si le retour est RPL_INVITING, il faut envoyer le RPL_INVITING au user correspondants a params[0]
int		list(std::string params, user* askingOne, std::vector<channel*>& chan_vec,
			std::map<unsigned int, user *>& users, Server& srv);
int		mode(std::vector<std::string> params, user* askingOne,
			std::vector<channel *> &chan_vec, std::map<unsigned int, user *> &users,
			Server& srv);
int		names(std::string params, user* askingOne, std::vector<channel*> chan_vec,
			std::map<unsigned int, user *>& users, Server& srv);
int		nick(std::vector<std::string> params, user* askingOne,
			std::map<unsigned int, user *>& users, Server& srv);
int		pass(std::string psw, user* usr, Server& srv);
int		topic(std::vector<std::string> params, user* askingOne,
			std::vector<channel*> chan_vec, Server& srv);
int		user_cmd(std::vector<std::string> params, user* usr, Server& srv);
void	pong(std::vector<std::string> params, user &user, Server &server);
void	error(user &user, Server &server, const std::string &msg);
void	quit(user &user, Server &server);
void	oper(std::vector<std::string> params, user &user, Server &server);

// Server-side commands
void	quit_server(user &user, Server &server, std::string msg);
void	ping(std::vector<std::string> params, user &user, Server &server);

#endif