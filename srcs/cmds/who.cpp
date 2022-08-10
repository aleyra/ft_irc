#include "user.hpp"//en attendant un .hpp qui inclu user.hpp
#include <list>
#include <map>
#include "numeric_reply.hpp"
//srv.hostname = is the name of the server (as used in message prefixes).

int	who(std::string name, server* srv){
	user*				usr;
	// std::list<vector*>	list_chan;
	if (name.empty()){
		std::map<int, user*> usr_list;//a changer // recup la liste des user notee ici usr_list
		for (std::map<int, user*>::iterator it = usr_list.begin();
				 it != usr_list.end(); ++it){
			usr = *it;

		}
	}
	else {
		usr = searchUser(name);
		if (usr == NULL){
			std::cout << "<client>" << " " << name <<" :End of WHO list" << std::endl;//RPl_ENDOFWHO//<client> a modifier
			return RPL_ENDOFWHO;
		}
		std::cout << "<client>" << " ";
		std::vector<channel*> &	list_chan = usr->getList_chan();
		if (!list_chan.empty())
			std::cout << list_chan.front()->getName();
		else 
			std::cout << "*";
		std::cout << " " << usr->getUsername();
		// std::cout << " " <<"<host>";//<host> a modifier //????qu'est-ce que le host ici ?
		std:: cout << " " << srv->hostname;//<server>
		std::cout << " " << usr->getNick() << " ";//<nick>//
		if (usr->getAway() == true)//<flags>
			std::cout << "G";//G for gone
		else
			std::cout << "H";//H for here
		if (usr->getLvl() == 2)
			std::cout <<"*";//means is en srv op
		for (std::map<int, user*>::iterator it = usr_list.begin();
				 it != usr_list.end(); ++it){
			usr = *it;
			//la suite ???? on est sur les flags
		}
		//:<hopcount> <realname> ;
	}

	
}

int	who(std::string name, char o, server* srv){
	if (o != 'o')
		return EXIT_FAILURE;//chercher dans la doc comment reagir dans le cas ou l'option o n'est pas la bonne
	
	user*	usr;
	if (name.empty()){
		std::map<int, user*> usr_list;//a changer // recup la liste des user notee ici usr_list
		for (std::map<int, user*>::iterator it = usr_list.begin(); it != usr_list.end(); it++){
			usr = *it;	
			if (usr->getIsop() == true){

			}
		}
	}

	return RPL_ENDOFWHO;
}