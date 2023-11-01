#pragma once
#include <string>

class User
{
public:
	User(std::string& login, std::string& password, std::string& name);
	~User() = default;

	//int getId() const;int id,
	std::string getLogin() const;
	std::string getPassword() const;
	std::string getName() const;
private:
	//int _id;
	std::string _login;
	std::string _password;
	std::string _name;
};
