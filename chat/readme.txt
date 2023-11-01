server:
	g++ -std=c++2a -o server $(mysql_config --cflags) *.cpp $(mysql_config --libs)


client:
	g++ -std=c++2a -o client *.cpp

driver MySql Qt5:
  libqt5sql5-mysql

"localhost", "root", "!Patriot1", "chatdb",

Linux ubunts20 5.15.0-67-generic #74~20.04.1-Ubuntu SMP

GUI клиентской части приложения 
только форма


