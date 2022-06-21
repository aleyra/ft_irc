#include "user.hpp"

user::user(){
	this->_away = false;
	this->_idle_time = 0;
}

user::user(user const &src){
	*this = src;
}

user::user(std::string usr_name){
	this->_username = usr_name;
	this->_away = false;
	this->_idle_time = 0;
}

user::~user(){
}

user	&user::operator=(user const &src){
	this->_nick = src._nick;
	this->_username = src._username;
	this->_truename = src._truename;
	this->_history_nick = src._history_nick;
	this->_lvl = src._lvl;
	// this->_chanop = src._chqnop;
	// this->_list_chan = src._list_chan;
	this->_away = src._away;
	this->_away_msg = src._away_msg;
	this->_idle_time = src._idle_time;
	return (*this);
}

void	user::setNick(std::string n){
	this->_nick = n;
}

std::string const	&user::getNick() const{
	return (this->_nick);
}

void	user::setUsername(std::string un){
	this->_username = un;
}

std::string const	&user::getUsername() const{
	return (this->_username);
}

void	user::setTruename(std::string tn){
	this->_truename = tn;
}

std::string const	&user::getTruename() const{
	return (this->_truename);
}

std::list<std::string> const	&user::getHistory_nick() const{
	return (this->_history_nick);
}

void	user::setLvl(int l){//on s'assure que le lvl est entre 0 et 2
	if (l > 2){l = 2;}
	if (l < 0){l = 0;}
	this->_lvl = l;
}

int const	&user::getLvl() const{
	return (this->_lvl);
}

void	user::setAway(bool a){
	this->_away = a;
}

bool const	&user::getAway() const{
	return (this->_away);
}

void	user::setAway_msg(std::string amsg){
	this->_away_msg = amsg;
}

std::string const	&user::getAway_msg() const{
	return (this->_away_msg);
}

unsigned int const	&user::getIdle_time() const{
	return (this->_idle_time);
}

void	user::setLast_activity(){
	this->_last_activity = std::time(nullptr);
}

std::time_t const	&user::getLast_activity() const{
	return (this->_last_activity);
}

void	user::setPassword(std::string pwd){
	//on pourra eventuellement faire des tests de verification pour que le pwd respecte certaines regles
	this->_password = pwd;
}

std::string const	&user::getPassword() const{
	return (this->_password);
}

void	user::addHistory_nick(std::string	old_nick){
	this->_history_nick.push_front(old_nick);
}

void	user::clearHistory_nick(){
	this->_history_nick.clear();
}

void	user::idle_counter(){//a faire
	//c'est un compteur en sec depuis la derniere activite du user
	this->_idle_time = 30;//
}

void	user::resetIdle_counter(){
	this->_idle_time = 0;
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
	std::cout << "Mot de Passe incorrect\n";
	return (false);
}

std::time_t	user::check_Idle_time(){
	std::time_t now = std::time(nullptr);
	return (now - this->getLast_activity());
}
