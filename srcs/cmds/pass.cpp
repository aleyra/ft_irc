#include "cmds.hpp"

void	pass(std::vector<std::string> params, user &user,
	Server& server, std::string password)
{
	if (params.size() == 0)
	{
		numeric_reply(ERR_NEEDMOREPARAMS, &user, "PASS", server);
		return;
	}
	if (user.getHasConnected())
	{
		std::cout << "1" <<std::endl;
		numeric_reply(ERR_ALREADYREGISTERED, &user, server);
		return;
	}
	if (params[0] == password)
	{
		user.connect();
		return;
	}
	else
	{
		numeric_reply(ERR_PASSWDMISMATCH, &user, server);
		std::cout << params[0] << std::endl;
		return;
	}
}