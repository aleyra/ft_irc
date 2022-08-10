#include "user.hpp"//en attendant un .hpp qui inclu user.hpp


//srv.host =
//usr.chan[10] = il faut un tableau de channel dans lequel le usr est 
//usr.idle_time = time since last activity in seconds
int WhoisCmd(/*list of params = usr.mask*/, server srv){
	User tmp;
	if (/*list empty*/)
		return (numeric_reply(ERR_NONICKNAMEGIVEN));
	for(/*each param of WHOIS*/){
		tmp = srv.findUser(/*a param*/)//chercher un nickname correspondant dans la liste des user ONLINE
		if (tmp != NULL){//if there is display :
			std::cout << usr.getNick() << "@" << usr << srv.host << "*:" << usr.getTruename() << std::endl;//RPL_WHOISUSER
			std::cout << usr.getNick() << ":";//RPL_WHOISCHANNELS
			for (int i = 0; i < 10; i++) {
				if (i != 0 && usr.chan[i] != NULL)
					std::cout << " ";
				if (usr.chan[i] == NULL)//ce n'est pas un channel où est le usr
					i = 10;
				else{
					//if it's a moderated channel and usr is allowed to speak
						std::cout << "+";
					/*else*/ if (usr.getLvl() > 0)//est un operateur du chan???
						std::cout << "@" ;//a verif
					std::cout << usr.chan[i];
				}
			}
			std::cout << std::endl;
			std::cout << usr.getNick() << ": " << usr.idle_time << "seconds idle" << std::endl;//RPL_WHOISIDLE
			if (/*is an irc op*/)//RPL_WHOISOPERATOR
				std::cout << usr.getNick() << "is an IRC operator" << std::endl;
		}
		else
			numeric_reply(ERR_NOSUCHNICK, /*param de WHOIS*/);
	}
	return (EXIT_SUCCESS);
}