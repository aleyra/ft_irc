#include "user.hpp"

int main(){
	user moi("moi");
	moi.setNick("Moi");
	std::cout << "nick = " << moi.getNick() << std::endl;
	moi.setUsername("mon usrname");
	std::cout << "username = " << moi.getUsername() << std::endl;
	moi.setTruename("mon tn");
	std::cout << "tn = " << moi.getTruename() << std::endl;
	moi.addHistory_nick("vieux pseudo1");
	moi.addHistory_nick("vieux pseudo2");
	moi.addHistory_nick("vieux pseudo3");
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
	std::cout << "--------------\n";
	
	user jumeau(moi);
	std::cout << "nick = " << jumeau.getNick() << std::endl;
	std::cout << "username = " << jumeau.getUsername() << std::endl;
	std::cout << "tn = " << jumeau.getTruename() << std::endl;
	list = jumeau.getHistory_nick();
	std::cout << "debut list = " << *list.begin() << std::endl;
	std::cout << "avant dernier list = " << *(--(--list.end())) << std::endl;
	std::cout << "dernier list = " << *(--list.end()) << std::endl;
	std::cout << "mon lvl = " << jumeau.getLvl() << std::endl;
	if (jumeau.getAway() == true)
		std::cout << "je suis absente\n";
	else
		std::cout << "je suis presente\n";
	std::cout << "mon amsg = " << jumeau.getAway_msg() << std::endl;
	std::cout << "idle time = " << jumeau.getIdle_time() << std::endl;

	return (0);
}