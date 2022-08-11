#include "tools.hpp"
#include "user.hpp"
// #include "server.hpp"
#include "channel.hpp"
#include <cstdlib>


int	away(std::string txt, user*	usr, server* srv);
int	nick(std::vector<std::string> params, user* usr, server* srv);
int whowas(std::vector<std::string> params, server* srv);