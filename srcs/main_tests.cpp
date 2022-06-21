#include "user.hpp"

int main(){
	user moi("moi");
	moi.setNick("Moi");
	std::cout << "nick = " << moi.getNick() << std::endl;
	moi.setUsername("mon usrname");
	std::cout << "username = " << moi.getUsername() << std::endl;
	moi.setTruename("mon tn");
	std::cout << "tn = " << moi.getTruename() << std::endl;
	moi.addHistory_nick("truc");
	moi.addHistory_nick("machin");
	moi.addHistory_nick("chose");
	std::list<std::string> list = moi.getHistory_nick();
	std::cout << "debut list = " << *list.begin() << std::endl;
	std::cout << "avant dernier list = " << *(--(--list.end())) << std::endl;
	std::cout << "dernier list = " << *(--list.end()) << std::endl;
	// moi.clearHistory_nick();
	// list = moi.getHistory_nick();
	// std::cout << "debut list = " << *list.begin() << std::endl;
	moi.setLvl(1);
	std::cout << "mon lvl = " << moi.getLvl() << std::endl;
	moi.setAway(true);
	if (moi.getAway() == true)
		std::cout << "je suis absente\n";
	else
		std::cout << "je suis presente\n";
	moi.setAway_msg("pas la");
	std::cout << "mon amsg = " << moi.getAway_msg() << std::endl;
	moi.idle_counter();
	std::cout << "idle time = " << moi.getIdle_time() << std::endl;
	// moi.resetIdle_counter();
	// std::cout << "idle time = " << moi.getIdle_time() << std::endl;
	moi.setPassword("motdepasse");
	std::cout << "mon pwd = " << moi.getPassword() << std::endl;
	if (moi.test_password("coucou") == true)
		std::cout << "gagne \n";
	if (moi.find_in_history_nick("chose") == true)
		std::cout << "trouve\n";
	else	
		std::cout << "inconnu\n";
	moi.setLast_activity();
	std::cout << "la = " << moi.getLast_activity() << std::endl;
	std::cout << "now - la = " << moi.check_Idle_time() << std::endl;
	std::cout << "--------------\n";
	

	return (0);
}