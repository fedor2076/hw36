#include "consolechat.h"


Server_socket server;
std::string query;

//----------------------------------------------------------------------------------------
void ConsoleChat::initSql()
{
  mysql_init(&mysql);
  if (&mysql == nullptr)
  {
    std::cout << "Error: can't create MySQL-descriptor" << std::endl;// Если дескриптор не получен — выводим сообщение об ошибке
  }
  if (!mysql_real_connect(&mysql, "localhost", "admin", "!Patriot1", "chatdb", 0, NULL, 0))
	//if (!mysql_real_connect(&mysql, "localhost", "root", "!Patriot1", "chatdb", 0, NULL, 0))  // Подключаемся к серверу
  {
		std::cout << "Error: can't connect to database " << mysql_error(&mysql) << std::endl;		// Если нет возможности установить соединение с БД выводим сообщение об ошибке
	}
	mysql_set_character_set(&mysql, "utf8mb4");
}

void ConsoleChat::querySql(const std::string &str)
{
  const char *cstr = str.c_str();
	mysql_query(&mysql, cstr);
}
std::string  ConsoleChat::getSql(std::string& login)
{
  if (res = mysql_store_result(&mysql))
  {
  row = mysql_fetch_row(res);
  return row[0];

  }
  else return "no user";
}
std::shared_ptr<User> ConsoleChat::getUserByLogin(const std::string login) //const
{
  query = "SELECT * FROM users";
  querySql(query);

  std::string slogin, hash_password, email;

  if (res = mysql_store_result(&mysql))
  {
    while (row = mysql_fetch_row(res))
    {
        slogin = row[1];
        if (slogin==login)
        {
        hash_password =row[2];
        email = row[3];
        return shared_ptr<User>(new User(slogin, hash_password, email));
        }
    }
  }
return nullptr;
}

std::string  ConsoleChat::getIdLoginSql(std::string login)
{
query = "SELECT id FROM users WHERE login ='"+login+"'";
querySql(query);
return  getSql(login);
}


std::string  ConsoleChat::getLoginIdSql(std::string id)
{
query = "SELECT login FROM users WHERE id ='"+id+"'";
querySql(query);
return  getSql(id);
}


void ConsoleChat::outSql()
{
  if (res = mysql_store_result(&mysql))
  {
      while (row = mysql_fetch_row(res))
      {
        for (int i = 1; i < mysql_num_fields(res); i++)
        {
          server.insock(row[i]);
        }
        server.insock("\n");

      }
    }
  else
    std::cout << "Ошибка MySql номер " << mysql_error(&mysql);
}
//---------------------------------------------------------------------------------------
std::string ConsoleChat::genSalt() const
{
	std::string salt;
	static const char charset[] = {"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz" };
	random_device rd;
	mt19937 gen(rd());
	for (int i = 0; i < 32; ++i)
	{
			salt += charset[gen() % (sizeof(charset) - 1)];
	}
	return salt;
}
bool ConsoleChat::chatStarted() const
{
	return _chatStarted;
}

void ConsoleChat::start()
{
	_chatStarted = true;
}

string ConsoleChat::hashPassword(const std::string& password)
{
	uint* digest = sha1(password.c_str(), password.length());
	string hash_string;
	for(int i = 0; i<SHA1HASHLENGTHUINTS; ++i)
	{
		hash_string += to_string(digest[i]);
  }
	delete[] digest;
	return hash_string;
}

bool ConsoleChat::hashCompare(const std::string& password, const std::string& hash_password, const std::string& salt)
{
	return (hashPassword(salt + password + salt) == hash_password);
}

void ConsoleChat::startLoad()
{
	initSql();//

		query ="CREATE TABLE IF NOT EXISTS users(id SERIAL PRIMARY KEY, login VARCHAR(50) \
	 	NOT NULL, hash_password VARCHAR(60) NOT NULL, email VARCHAR(50) NOT NULL, \
	 	 salt VARCHAR(50) NOT NULL, date_registration DATETIME DEFAULT NOW(), ban_user BOOLEAN NOT NULL DEFAULT FALSE)";// DEFAULT '1'

 	querySql(query);

	query = "CREATE TABLE IF NOT EXISTS messages(id SERIAL PRIMARY KEY, from_user_id INT NOT NULL, \
	 to_user_id INT NOT NULL, message TEXT, date DATETIME DEFAULT NOW())";
	querySql(query);
  std::string all = "Всем";
  if (!(getIdLoginSql(all)=="0"))
  {
  	   query = "INSERT INTO users(id, login,  hash_password, email, salt, date_registration, ban_user) \
  	   VALUES(0, 'Всем', 0, 0, 0, DEFAULT, DEFAULT)";
  	   querySql(query);
   }
 	start();
}

int ConsoleChat::searchValue(const std::string& name, const std::map<std::string, std::string>& my_map)
{
	int i = 1;
	for (auto& element : my_map)
		{
			if (name == element.first)
					return i;
			++i;
		}
	return 0;
}

void ConsoleChat::startMenu()//главное меню
{
	std::string action;
	server.insock("\tДобро пожаловать в чат!\n\n Выберите действие: \n\n") ;

	for (auto& element : main_menu)
		{
				action = element.first + " " + element.second + "\n";
				server.insock(action) ;
		}

	server.insock("~");
	action = server.outsock();
	switch (searchValue(action, main_menu))
		{
			case 1:
				signUp();
						break;
			case 2:
				logIn();
						break;
			case 3:
				server.insock("end");
						break;
			default:
				server.insock("Please check that the characters you are entering are correct.\n");
					break;
		}
};

std::shared_ptr<User>  ConsoleChat::getOnlineUser() const
{
	return _onlineUser;
}

void ConsoleChat::logIn()//вход в чат
{
	std::string login, password, salt, hash_password, ban ;

	server.insock("Пожалуйста, введите логин: ");
	server.insock("~");
	login = server.outsock();

	server.insock("Введите пароль: ");
	server.insock("~");
	password = server.outsock();

	_onlineUser = getUserByLogin(login);
  if (_onlineUser == nullptr)
    {
      server.insock("Неверный логин, пожалуйста, повторите попытку\n");
    }
  else
    {
      query = "SELECT salt FROM users WHERE login =  '" + login + "';";
	    querySql(query);
	    salt = getSql(login);
      query = "SELECT hash_password FROM users WHERE login =  '" + login + "';";
      querySql(query);
	    hash_password = getSql(login);
      query = "SELECT ban_user FROM users WHERE login =  '" + login + "';";
      querySql(query);
      ban = getSql(login);
      bool b = hashCompare(password, _onlineUser->getPassword() , salt);
	    if (!b )
		    {
			    _onlineUser = nullptr;
			    server.insock("Неверный пароль, пожалуйста, повторите попытку\n");
		    }
        else if (ban!="0")
        {
          _onlineUser = nullptr;
			    server.insock("Вы заблокированы, пожалуйста, обратитесь к администратору\n");
        }
    }
}

void ConsoleChat::signUp()//регистрация
{
	std::string login, password, email;

	server.insock("Пожалуйста, введите логин: ");
	server.insock("~");
	login =  server.outsock() ;

	server.insock("Введите пароль: ");
	server.insock("~");
	password = server.outsock();

	server.insock("Введите свой адрес электронной почты: ");
	server.insock("~");
	email = server.outsock();

	try
		{
			if (getUserByLogin(login) || login == "Всем")
				{
					throw LoginException("Ошибка: ");
				}
		}
	catch (const LoginException& ex)
		{
			std::cerr << "\n\n (" << ex.what() << ") \n\n";
			server.insock(ex.what());
			server.insock("\n");
			return;
		}

		 std::string salt = genSalt();
	   password = hashPassword(salt + password + salt);
	   User user = User(login, password, email);
	   _onlineUser = std::make_shared<User>(user);

	   query = "INSERT INTO users(id, login,  hash_password, email, salt, date_registration) \
	   VALUES(DEFAULT, '" + login + "', '" + password + "', '" + email+ "', '" + salt + "', DEFAULT)";
	   querySql(query);
	   server.insock("\nПоздравляем! Вы успешно зарегистрировались!\n");
}

void ConsoleChat::openChat() //вывод сообщений чата
{
	std::string sender, recipient;
	server.insock("------------------------------\n");
  query = _onlineUser->getLogin();
  sender=getIdLoginSql(query);

  query ="SELECT * from messages WHERE  \
  from_user_id = " + sender + " or to_user_id = " +sender+ " or to_user_id = 0  ORDER by date;" ;
  querySql(query);
  outSql();
  server.insock("---------------------------------\n\n");
}

void ConsoleChat::sendMessage() //отправка сообшения
{
	std::string recipient, text, from, to;
	server.insock("Кому (0-всем)");

	server.insock("~");
	recipient = server.outsock();

	server.insock("~");
	text = "'" + server.outsock() + "'";
  char a =static_cast<char>(39);//замена симввола -> '
  char b =static_cast<char>(32);//на символ -> space
  std::replace( text.begin()+1, text.end()-1, a , b);
  if  (recipient == _onlineUser->getLogin())
    {
      server.insock("ошибка сообщение себе -- " + recipient + "\n");
      return;
    }
	if (!(recipient == "0" || getUserByLogin(recipient)))
		{
			server.insock("ошибка нет такого пользователя -- " + recipient + "\n");
  		return;
		}
	if (recipient == "0")
		{
		  from = getIdLoginSql(_onlineUser->getLogin());
      text = "INSERT INTO messages (id, from_user_id, to_user_id, message, date) values( default, " + from + " , 0, " + text + " , now());";
      querySql(text);
		}
	else
		{
			from = getIdLoginSql(_onlineUser->getLogin());
      to = getIdLoginSql(getUserByLogin(recipient)->getLogin());
      text = "INSERT INTO messages (id, from_user_id, to_user_id, message, date) values(default, " + from + ", " + to +", " + text + " , now());";
			querySql(text);
			server.insock("message send -  " + recipient + ":\n ");
		}
}

void ConsoleChat::chatMenu() //меню чата
{
	std::string action;
	action = "Добро пожаловать " + _onlineUser->getName() + "\n";
	server.insock(action);

	do
	{
		openChat();
		server.insock("\nВыберите действие: \n");

		for (auto& element : chat_menu)
			{
				server.insock(element.first + " " + element.second + "\n");
			}

		server.insock("~");
		action = server.outsock();

		if(action[0]=='1')
			{
				sendMessage();
			}
		else if (action[0]=='2')
			{
				_onlineUser = nullptr;
			}
		}
		while (_onlineUser);
}
