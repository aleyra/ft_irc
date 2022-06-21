#ifndef USER_H
# define USER_H

# include "iostream"
# include "string"
# include "algorithm"
# include "list"
# include "ctime"
// # include "channel.hpp"

class user{
//constructors anf destrutor
private:
	user();
	user(user const &src);
public:
	user(std::string usr_name);
	virtual ~user();//a ne pas mettre en private ^^"

//attributs
private:
	std::string				_nick;
	std::string				_username;
	std::string				_truename;
	std::list<std::string>	_history_nick;//liste des anciens nick de l'user, du moins ancien (au debut), au moins ancien (a la fin)
	int						_lvl;//lvl access : 0 = simple utilisateur, 1 = channel operator, 2 = irc operator
	// std::list<channel>		_chanop;//list des chan où l'user est operator
	// channel				_list_chan[10];//list des 10 (nombre recommandé) chan où l'user est ou peut être
	bool					_away;
	std::string				_away_msg;
	unsigned int			_idle_time;//temps en sec depuis la dernière activité. S'utilise avec un compteur (?)
	std::time_t				_last_activity;//save en sec du moment de la dernière activite qu'a eu l'user (depuis le Epoch) https://en.cppreference.com/w/cpp/chrono/c/time 
	std::string				_password;

//overload d'operateurs
private:
	user	&operator=(user const &src);//merci de mettre a jour cette fct quand vous ajoutez des attributs

//getters and setters
public:
	void					setNick(std::string n);
	std::string const		&getNick() const;
	void					setUsername(std::string un);
	std::string const		&getUsername() const;
	void					setTruename(std::string tn);
	std::string const		&getTruename() const;
	//set de _history_nick est remplacé par addHistory_nick dans other member functions
	std::list<std::string> const	&getHistory_nick() const;
	void					setLvl(int l);
	int const				&getLvl() const;
	void					setAway(bool a);
	bool const				&getAway() const;
	void					setAway_msg(std::string amsg);
	std::string const		&getAway_msg() const;
	//set de _idle_time est remplacé par idle_counter dans other member function
	unsigned int const		&getIdle_time() const;
	void					setLast_activity();//a utiliser des que l'user entre en ligne
	std::time_t const		&getLast_activity() const;
	void					setPassword(std::string pwd);//pour l'instant c'est une fonction nulle sans securte sur le pwd
	std::string const		&getPassword() const;

//other member functions
public:	
	void		addHistory_nick(std::string	old_nick);//push_front de _history_nick
	void		clearHistory_nick();//clear de _history_nick
	void		idle_counter();//je sais pas comment faire
	void		resetIdle_counter();//remise a 0 de _idle_time
	bool		find_in_history_nick(std::string s);//cherche si s est dans _history_nick (utile pour WHOWAS)
	bool		test_password(std::string s);//test s == password
	std::time_t	check_Idle_time();//donne le temps en secondes depuis _last_activity
};

#endif
