#include "cmds.hpp"

/**
* Description:
* 	Set the operator's values from config.ini file.
* 
* Args:
* 	None.
* 
* Return:
* 	None.
* 
* Notes:
* 	Format of the file:
* 		OPERNAME=<name>
* 		OPERPASS=<password>
**/

std::pair<std::string, std::string>	get_oper()
{
	std::ifstream f;
	f.open("./config/config.ini", std::ios::in);
	std::string line;
	std::pair<std::string, std::string> oper;
	if (f.is_open())
	{
		while (std::getline(f, line))
		{
			if (line.substr(0, line.find("=")) == "OPERNAME")
				oper.first = line.substr(9, line.find_first_of(" \t\n") - 9);
			else if (line.substr(0, line.find("=")) == "OPERPASS")
				oper.second = line.substr(9, line.find_first_of(" \t\n") - 9);
		}
	}
	else
		throw std::invalid_argument("Can't open config file");
	if (oper.first.empty() || oper.second.empty())
		throw std::invalid_argument(
			"Invalid config file: OPERNAME and/or OPERPASS not found");
	return (oper);
}

/**
* Description:
* 	Set the allowed_host's value from config.ini file.
* 
* Args:
* 	None.
* 
* Return:
* 	None.
* 
* Notes:
* 	Format of the file:
* 		ALLOWED_HOST=127.0.0.1
**/

std::string	get_allowed_host()
{
	std::ifstream f;
	f.open("./config/config.ini", std::ios::in);
	std::string line;
	std::string	ret;
	if (f.is_open())
	{
		while (std::getline(f, line))
		{
			if (line.substr(0, line.find("=")) == "ALLOWED_HOST")
				ret = line.substr(13, line.find_first_of(" \t\n") - 13);
		}
	}
	else
		throw std::invalid_argument("Can't open config file");
	if (ret.empty())
		throw std::invalid_argument(
			"Invalid config file: ALLOWED_HOST not found");
	return (ret);
}

void	oper(std::vector<std::string> params, user &user, Server &server)
{
	std::pair<std::string, std::string> oper;
	std::string	allowed_host;
	try
	{
		oper = get_oper();
		allowed_host = get_allowed_host();
	}
	catch (std::exception &e)
	{
		std::cout << "Oper failed for the following reason: " << e.what() << std::endl;
		return;
	}
	server.client_ip(user.getId());
	std::cout << params.size() << std::endl;
	if (params.size() < 2)
	{
		numeric_reply(ERR_NEEDMOREPARAMS, &user, "OPER", server);
		return;
	}
	if (allowed_host != server.client_ip(user.getId()))
	{
		numeric_reply(ERR_NOOPERHOST, &user, server);
		return;
	}
	if (params[0] == oper.first && params[1] == oper.second)
	{
		user.setLvl(2);
		user.setIsop(true);
		numeric_reply(RPL_YOUREOPER, &user, "OPER", server);
		numeric_reply(RPL_UMODEIS, &user, &user, server);
	}
	else
		numeric_reply(ERR_PASSWDMISMATCH, &user, server);
}