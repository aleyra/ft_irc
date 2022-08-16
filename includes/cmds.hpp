#ifndef CMDS_HPP
# define CMDS_HPP

#include "tools.hpp"
#include "user.hpp"
#include "Server.hpp"
#include "channel.hpp"
#include <cstdlib>
#include <cstring>

// int	away(std::string txt, user*	usr, Server& srv);
int		names(std::string params, std::vector<channel*> chan_vec,
			std::map<unsigned int, user *>& users, Server& srv);
int		nick(std::vector<std::string> params, user& usr,
			std::map<unsigned int, user *>& users,Server& srv);
int		pass(std::string psw, user* usr, Server& srv);
int		user_cmd(std::vector<std::string> params, user* usr, Server& srv);
void	ping(std::vector<std::string> params, user &user, Server &server);
void	pong(std::vector<std::string> params, user &user, Server &server);
void	error(user &user, Server &server, const std::string &msg);
void	quit(std::vector<std::string> params, user &user, Server &server);

#endif