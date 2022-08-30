#ifndef USER_HPP
# define USER_HPP

# include <iostream>
# include <string>
# include <algorithm>
# include <vector>
# include <ctime>
# include <list>
# include "channel.hpp"

class channel;
class Server;

class user{
	private:
		std::string					_nick;
		std::string					_username;
		std::string					_truename;
		std::list<std::string>		_history_nick;//liste des anciens nick de l'user, du moins ancien (au debut), au moins ancien (a la fin)
		int							_lvl;//lvl access
		std::vector<channel*>		_list_chan;//list des 10 (nombre recommandé) chan où l'user est
		bool						_isaway;
		std::string					_away_msg;
		std::time_t					_last_activity;//save en sec du moment de la dernière activite qu'a eu l'user (depuis le Epoch) https://en.cppreference.com/w/cpp/chrono/c/time 
		std::string					_password;
		bool						_isop;//is operator
		unsigned int				_id;
		std::string					_mode;
		std::string					_ip;
		bool						_isonline;
		bool						_hasSetPass; //user used the pass command
		bool						_sentConnectionMessage;
	
	// #pragma region constructors destructor
	private:
		user();
		user(user const &src);
	public:
		user(std::string usr_name, unsigned int id);
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
		std::vector<channel*> &			getList_chan();
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
		// void							setMode(char c);//remplace par addMode et rmMode
		std::string const &				getMode() const;
		void							setIsonline(bool b);
		bool const &					getIsonline() const;
		bool const &					getHasConnected() const;
		void							connect();
		void							setIp(std::string ip);
		std::string const &				getIp() const;
		void							setSentConnectionMessage(bool b);
		bool const						&getSentConnectionMessage() const;
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
		void		addMode(char c);
		void		rmMode(char c);
		bool		hasMode(char c);
	// #pragma endregion other member functions
};

bool	operator==(user const & lhs, user const & rhs);
bool	operator!=(user const & lhs, user const & rhs);
bool	operator>(user const & lhs, user const & rhs);
bool	operator>=(user const & lhs, user const & rhs);
bool	operator<(user const & lhs, user const & rhs);
bool	operator<=(user const & lhs, user const & rhs);

user*	searchUserByNick(std::string mask, std::map<unsigned int, user *>& users);
user*	searchUserByID(unsigned int id, std::map<unsigned int, user *>& users);
char	display_isaway(user& usr);
bool	has1channelInCommon(user& u1, user& u2);
bool	isIn1VisibleChannel(user* u);
void	sendToAllInChanOfAskingOne(user *askingOne, std::string msg, Server &srv);

#endif