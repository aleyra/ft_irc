#include "user.hpp"
#include <list>
#include <map>

// #pragma region constructors destructor
user::user(){
	this->_isaway = false;
	// this->_idle_time = 0;
}

user::user(user const &src){*this = src;}

user::user(std::string usr_name, unsigned int id){
	this->_username = usr_name;
	this->_isaway = false;//? je suis pas sure de : a quoi correspond usr_name dans la class usr
	this->_username = usr_name;//? idem
	this->_truename = usr_name;//? idem
	this->_lvl = 0;
	this->_isaway = false;
	this->setLast_activity();
	this->_isop = false;
	this->_id = id;
	this->_mode = 0;
	// this->_idle_time = 0;
}

user::~user(){
	this->_history_nick.clear();
}
// #pragma endregion constructors destrcutor

// #pragma region overload d operateurs
user	&user::operator=(user const &src){
	this->_nick = src._nick;
	this->_username = src._username;
	this->_truename = src._truename;
	this->_history_nick = src._history_nick;
	this->_lvl = src._lvl;
	if (!this->_list_chan.empty())
		this->_list_chan.clear();
	for (size_t i = 0; i < src._list_chan.size(); ++i){
		this->_list_chan.push_back(src._list_chan[i]);
	}
	this->_isaway = src._isaway;
	this->_away_msg = src._away_msg;
	this->_last_activity = src._last_activity;
	this->_password = src._password;
	this->_isop = src._isop;
	return (*this);
}
// #pragma endregion overload d operateurs

// #pragma region getters and setters
void	user::setNick(std::string n){
	if (!this->_nick.empty()){
		this->addHistory_nick(this->_nick);
	}
	this->_nick = n;
}

std::string const	&user::getNick() const{return (this->_nick);}

void	user::setUsername(std::string un){this->_username = un;}

std::string const	&user::getUsername() const{return (this->_username);}

void	user::setTruename(std::string tn){this->_truename = tn;}

std::string const	&user::getTruename() const{return (this->_truename);}

std::list<std::string> const	&user::getHistory_nick() const{
	return (this->_history_nick);
}

void	user::setLvl(int l){//on s'assure que le lvl est entre 0 et 2
	if (l > 2){l = 2;}
	if (l < 0){l = 0;}
	this->_lvl = l;
}

int const	&user::getLvl() const{return (this->_lvl);}

std::vector<channel*> const &	user::getList_chan() const{
	return (this->_list_chan);
}

void	user::setIsaway(bool a){this->_isaway = a;}

bool const	&user::getIsaway() const{return (this->_isaway);}

void	user::setIsaway_msg(std::string amsg){this->_away_msg = amsg;}

std::string const	&user::getAway_msg() const{return (this->_away_msg);}


void	user::setLast_activity(){this->_last_activity = std::time(NULL);}

std::time_t const	&user::getLast_activity() const{
	return (this->_last_activity);
}

void	user::setPassword(std::string pwd){
	//on pourra eventuellement faire des tests de verification pour que le pwd respecte certaines regles
	this->_password = pwd;
}

std::string const	&user::getPassword() const{return (this->_password);}

void	user::setIsop(bool b){this->_isop = b;}

bool const	&user::getIsop() const{return (this->_isop);}

unsigned int const &	user::getId() const{return this->_id;}

void	user::setMode(char c){
	this->_mode = c;
}

char const &	user::getMode() const{
	return (this->_mode);
}

void	user::setIsonline(bool b){
	this->_isonline = b;
}

bool const &	user::getIsonline() const{
	return (this->_isonline);
}

// #pragma endregion getters and setters

// #pragma region other member functions
void	user::addHistory_nick(std::string	old_nick){
	this->_history_nick.push_front(old_nick);
}

void	user::clearHistory_nick(){
	this->_history_nick.clear();
}

bool	user::find_in_history_nick(std::string s){
	std::list<std::string>	list = this->_history_nick;
	std::list<std::string>::iterator ret = std::find(list.begin(), list.end(), s);
	if (ret == list.end())
		return (false);
	return (true);
}

bool	user::test_password(std::string s){
	if (s == this->getPassword())
		return (true);
	std::cout << "Mot de Passe incorrect" << std::endl;
	return (false);
}

std::time_t	user::check_Idle_time(){
	std::time_t now = std::time(NULL);
	return (now - this->getLast_activity());
}

void	user::addList_chan(channel* nc){//gerer que max 10
	this->_list_chan.push_back(nc);
}
void	user::rmList_chan(channel* c){
	std::vector<channel*>::iterator f = std::find(this->_list_chan.begin(),
			this->_list_chan.end(), c);
		if (f == this->_list_chan.end())
			this->_list_chan.erase(f);
}


// #pragma endregion other member functions

// #pragma region non-member functions

bool	operator==(user const & lhs, user const & rhs){return (lhs.getId() == rhs.getId());}
bool	operator!=(user const & lhs, user const & rhs){return (lhs.getId() != rhs.getId());}
bool	operator>(user const & lhs, user const & rhs){return (lhs.getId() > rhs.getId());}
bool	operator>=(user const & lhs, user const & rhs){return (lhs.getId() >= rhs.getId());}
bool	operator<(user const & lhs, user const & rhs){return (lhs.getId() < rhs.getId());}
bool	operator<=(user const & lhs, user const & rhs){return (lhs.getId() <= rhs.getId());}

user*	searchUserByNick(std::string mask, std::vector<user*> usr_vec){
	for (size_t i = 0; i < usr_vec.size(); ++i){
		if (usr_vec[i]->getNick().compare(mask) == 0)
			return usr_vec[i];
	}
	return NULL;
}

char	display_isaway(user* usr){
	if (usr->getIsaway() == true)
		return 'G';
	return 'H';
}

bool	has1channelInCommon(user* u1, user* u2){
	std::vector<channel*> list_chan1 = u1->getList_chan();
	std::vector<channel*> list_chan2 = u2->getList_chan();
	for (size_t i = 0; i < list_chan1.size(); ++i){
		if (searchChannelByName(list_chan1[i]->getName(), list_chan2) != NULL)
			return true;
	}
	return false;
}


// #pragma endregion non-member functions
