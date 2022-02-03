#pragma once

#include <iostream>
#include <fstream>
#include <direct.h>
#include <string>

#define PATH "/users/"
#define PATH_ADMIN "/admin.txt"

using namespace std;
class User
{
	string username;
	string password;
	bool admin;


	static fstream file;
	static string path;
	static string abstract_path;

	User(string username, string password) {
		this->username = username;
		this->password = password;
		admin = false;
	}

	static User check_admin(User user) {
		file.open(abstract_path + PATH_ADMIN, fstream::in);
		string name;
		file >> name;
		file.close();

		if (name == user.username)
			user.admin = true;
		return user;
	}

public:
	bool is_admin() {
		return admin;
	}

	void save() {
		file.open(path + username + "/data.txt", fstream::out);
		file << password << "\n";
		file.close();
	}

	static User regestration(string username, string password) {
		if (_mkdir((path + username).c_str()) != 0)
			throw exception("Користувач уже існує!");
		User tmp = User(username, password);
		tmp.save();
		return tmp;
	}

	static User login(string username, string password) {

		file.open(path + username + "/data.txt", fstream::in);
		if (!file.is_open())
			throw exception("Такого користувача не існує!");
		string check;
		file >> check;
		file.close();
		
		if (check == password)
			return check_admin(User(username, password));
		else
			throw exception("Неправильний пароль!");

	}

	static void init(string new_path) {
		abstract_path = new_path;
		path = new_path+PATH;
		
		if(_mkdir(new_path.c_str()) == 0 && _mkdir(path.c_str()) == 0)
			throw exception("Перший запуск");
	}

};