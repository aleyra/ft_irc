#include "cmds.hpp"

//travail en cours

// int who(std::vector<std::string> params, Server* srv){
// 	if (params.size() == 0){
// 		/*In the absence of the <mask> parameter, all visible (users who aren't 
// 			invisible (user mode +i) and who don't have a common channel with
// 			the requesting client) are listed. */
// 		/*list des user*/user*	usr;//?
// 		for(debut de la liste, fin){//?
// 			if (usr->getIsonline() == true && usr->getMode() != 'i'){
// 				std::cout << usr->getList_chan()[0]->getName() << " "
// 					<< usr->getNick() << " "//<user>//?
// 					<< "<host>" << " "//a modifier "<host>"//?
// 					// << srv << //<server> //?
// 					<< usr->getNick() << " "//<nick> 
// 					<< display_isaway(usr) << " ";//( "H" / "G" > ["*"] [ ( "@" / "+" ) ] :<hopcount> <real name>"
// 					if (usr->getIsop() == true)
// 						std::cout << "* ";
// 					//a finir
// 			}
// 		}/**/
// 	}
	

// 	return (numeric_reply(RPL_ENDOFWHO, params[0], srv));
// }