#include "tools.hpp"
#include "user.hpp"
// #include "Server.hpp"
#include "channel.hpp"
#include <cstdlib>


int	away(std::string txt, user*	usr, Server* srv);
int	nick(std::vector<std::string> params, user* usr, Server* srv);
int whowas(std::vector<std::string> params, Server* srv);
