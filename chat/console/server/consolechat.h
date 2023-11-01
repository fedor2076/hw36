#pragma once
#include <map>
#include <random>
#include <vector>
#include <memory>
#include "message.h"
#include <iostream>
//#include <fstream>
//#include <filesystem>
#include "serversocket.h"
#include "sha1.h"
#include <mysql.h>

//namespace fs = std::filesystem;

class LoginException :public std::exception
{
public:
	LoginException(const std::string& msg) :_msg(msg) {}
	virtual const char* what() const noexcept override
	{
		return "error: user login already exists ";
	}
private:
	std::string _msg;
};

class ConsoleChat: public Server_socket
{
public:

	void start();
	bool chatStarted() const;
	void startMenu();
	void signUp();
	void logIn();
	std::shared_ptr<User> getOnlineUser() const;
	void chatMenu();
	void sendMessage();
	int searchValue(const std::string& name, const std::map<std::string, std::string>& my_map);
	void startLoad();
	std::string genSalt() const;
	string hashPassword(const string& password);
	bool hashCompare(const string& password, const string& hash_password, const string& salt);
///------------------------------------------------------
  void initSql();
	void querySql(const std::string& str);
	void outSql();
	std::string getIdLoginSql(std::string login);
	std::string getLoginIdSql(std::string id);
	std::string getSql(std::string& login);
	//std::string  getBanLoginSql(std::string login);
	MYSQL mysql;
	MYSQL_RES* res;
	MYSQL_ROW row;

private:
	std::shared_ptr<User> _onlineUser = nullptr;
	bool _chatStarted = false;
	std::shared_ptr<User> getUserByLogin(const std::string login);
	void openChat() ;
	std::map <std::string, std::string>
		main_menu = {
		{"1", "Регистрация"},
		{"2", "Войти в чат"},
		{"3", "Выход"},
	};
		std::map <std::string, std::string>
		chat_menu = {
		{"1", "Написать сообщение"},
		{"2", "Выход"},
	};

};
