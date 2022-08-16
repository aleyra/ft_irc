#pragma once

# include <iostream>
# include <string>
# include <algorithm>
# include <vector>
# include <ctime>
# include "channel.hpp"

class channel;

class user{
	private:
		std::string					_nick;
		std::string					_username;
		std::string					_truename;
		std::list<std::string>		_history_nick;//liste des anciens nick de l'user, du moins ancien (au debut), au moins ancien (a la fin)
		int							_lvl;//lvl access : 0 = simple utilisateur, 1 = channel operator, 2 = irc operator
		std::vector<channel*>		_list_chan;//list des 10 (nombre recommandé) chan où l'user est ou peut être
		bool						_isaway;
		std::string					_away_msg;
		std::time_t					_last_activity;//save en sec du moment de la dernière activite qu'a eu l'user (depuis le Epoch) https://en.cppreference.com/w/cpp/chrono/c/time 
		std::string					_password;
		bool						_isop;//is operator
		unsigned int				_id;
		char						_mode;
		bool						_isonline;
	
	// #pragma region constructors destructor
	private:
		user();
	public:
		user(std::string usr_name, unsigned int id);
		user(user const &src);
		~user();//a ne pas mettre en private ^^"
	// #pragma endregion constructors destrcutor


	// #pragma region overload d operateurs
	private:
		user	&operator=(user const &src);//merci de mettre a jour cette fct quand vous ajoutez des attributs
	// #pragma endregion overload d operateurs

	// #pragma region getters and setters
	public:
		void							setNick(std::string n);
		std::string const &				getNick() const;
		void							setUsername(std::string un);
		std::string const &				getUsername() const;
		void							setTruename(std::string tn);
		std::string const &				getTruename() const;
		//set de _history_nick est remplacé par addHistory_nick dans other member functions
		std::list<std::string> const &	getHistory_nick() const;
		void							setLvl(int l);
		int const &						getLvl() const;
		//set de _list_chan est remplace par addList_chan et rmList_chan
		std::vector<channel*> const &	getList_chan() const;//en attente de channel.hpp
		void							setIsaway(bool a);
		bool const &					getIsaway() const;
		void							setIsaway_msg(std::string amsg);
		std::string const &				getAway_msg() const;
		void							setLast_activity();//a utiliser des que l'user entre en ligne
		std::time_t const &				getLast_activity() const;
		void							setPassword(std::string pwd);//pour l'instant c'est une fonction nulle sans securte sur le pwd
		std::string const &				getPassword() const;
		void							setIsop(bool b);
		bool const &					getIsop() const;
		unsigned int const &			getId() const;
		void							setMode(char c);
		char const &					getMode() const;
		void							setIsonline(bool b);
		bool const &					getIsonline() const;
	// #pragma endregion getters and setters
	// #pragma region other member functions
	public:	
		void		addHistory_nick(std::string	old_nick);//push_front de _history_nick
		void		clearHistory_nick();//clear de _history_nick
		bool		find_in_history_nick(std::string s);//cherche si s est dans _history_nick (utile pour WHOWAS)
		bool		test_password(std::string s);//test s == password
		std::time_t	check_Idle_time();//donne le temps en secondes depuis _last_activity
		void		addList_chan(channel* nc);//le plus recent est a la fin
		void		rmList_chan(channel* c);
	// #pragma endregion other member functions
};

bool	operator==(user const & lhs, user const & rhs);
bool	operator!=(user const & lhs, user const & rhs);
bool	operator>(user const & lhs, user const & rhs);
bool	operator>=(user const & lhs, user const & rhs);
bool	operator<(user const & lhs, user const & rhs);
bool	operator<=(user const & lhs, user const & rhs);

user*	searchUserByNick(std::string mask, std::vector<user*> usr_vec);
char	display_isaway(user* usr);
bool	has1channelInCommon(user* u1, user* u2);

