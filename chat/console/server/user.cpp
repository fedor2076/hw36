#include "user.h"

User::User(std::string& login,std::string& password, std::string& name) :_login(login), _password(password), _name(name)
{
}
//int User::getId() const// int id, _id(id),
//{
//	return _id;
//}

std::string User::getLogin() const
{
	return _login;
}
std::string  User::getPassword() const
{
	return _password;
}
std::string  User::getName() const
{
	return _name;
}
