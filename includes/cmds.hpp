#ifndef CMDS_HPP
# define CMDS_HPP

#include "tools.hpp"
#include "user.hpp"
#include "Server.hpp"
#include "channel.hpp"
#include <cstdlib>
#include <cstring>

// int	away(std::string txt, user*	usr, Server& srv);
int	list(std::string params, std::vector<channel*>& chan_vec, Server& srv);
int	names(std::string params, std::vector<channel*> chan_vec, std::map<unsigned int, user *>& users, Server& srv);
int	nick(std::vector<std::string> params, user& usr, Server& srv);
int	pass(std::string psw, user* usr, Server& srv);
int	topic(std::vector<std::string> params, user* usr, Server& srv);
int	user_cmd(std::vector<std::string> params, user* usr, Server& srv);

#endif