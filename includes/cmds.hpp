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
			Server& srv);
int		join(std::string t, user* askingOne, std::vector<channel*>& chan_vec,
			std::map<unsigned int, user *> &users, Server& srv);
int		kick(std::vector<std::string> params, user *askingOne,
			std::vector<channel *> &chan_vec, std::map<unsigned int, user *>& users, 
			Server &srv);
int		list(std::string params, user* askingOne, std::vector<channel*>& chan_vec,
			std::map<unsigned int, user *>& users, Server& srv);
int		mode(std::vector<std::string> params, user* askingOne,
			std::vector<channel *> &chan_vec, std::map<unsigned int, user *> &users,
			Server& srv);
int		names(std::string params, user* askingOne, std::vector<channel*> chan_vec,
			std::map<unsigned int, user *>& users, Server& srv);
int		nick(std::vector<std::string> params, user* askingOne,
			std::map<unsigned int, user *>& users, Server& srv);
void	oper(std::vector<std::string> params, user &user, Server &server);
int		part(std::vector<std::string> paramsEtMsg, user* askingOne,
			std::vector<channel *> &chan_vec, Server& srv);
void	pass(std::vector<std::string> params, user &user,
	Server& server, std::string password);
void	pong(std::vector<std::string> params, user &user, Server &server);
int		topic(std::vector<std::string> params, user* askingOne,
			std::vector<channel*> chan_vec, Server& srv);
int		user_cmd(std::vector<std::string> params, user* usr, Server& srv);
void	quit(std::vector<std::string> params, user &askingOne,
	std::vector<channel*> chan_vec, Server &server);
void	notice(std::vector<std::string> params, user &askingOne,
			std::vector<channel*> chan_vec,
			std::map<unsigned int, user*> &users, Server &server);
void	privmsg(std::vector<std::string> params, user &askingOne,
			std::vector<channel*> chan_vec,
			std::map<unsigned int, user*> &users, Server &server);
void	error(user &askingOne, Server &server, const std::string &msg);

// Server-side commands
void	quit_server(user &user, Server &server, std::string msg);
void	ping(std::vector<std::string> params, user &user, Server &server);

#endif