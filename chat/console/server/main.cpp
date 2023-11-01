//данные User и Message реализованы в <vector>
//стартовое меню и меню чата реализованы в <map>
//g++ -std=c++2a -o server $(mysql_config --cflags) *.cpp $(mysql_config --libs)

#include "consolechat.h"

auto main() -> int
{
	setlocale(LC_ALL, "ru_RU.UTF-8");
std::cout << "start chat\n";
	ConsoleChat ConsoleChat;

	ConsoleChat.startLoad();// Запуск чата

	while (ConsoleChat.chatStarted()) // Пока чат запущен
	{
		ConsoleChat.startMenu(); // Отображать стартовое меню

		while (ConsoleChat.getOnlineUser()) // Пока в системе есть пользователь
		{
			ConsoleChat.chatMenu(); // Отображать меню чата
		}
	}

}
