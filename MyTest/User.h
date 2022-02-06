#pragma once

#include <iostream>
#include <fstream>
#include <direct.h>
#include <string>

#include "FilePathes.h"
#include "DirectoryMenu.h"
#include "Test.h"

using namespace std;
class User
{
	string username;
	string password;
	bool admin;

	bool authorization;

	User(string username, string password) {
		this->username = username;
		this->password = password;
		admin = false;
		authorization = true;
	}

	static User check_admin(fstream& file, User user) {
		file.open(Pathes::MAIN_PATH+"\\admin.txt", fstream::in);
		string name;
		file >> name;
		file.close();

		if (name == user.username)
			user.admin = true;
		
		return user;
	}

public:
	User() {
		username = password = "guest";
		authorization = admin = false;
	}

	bool is_admin() {
		return admin;
	}
	bool is_authorization() {
		return authorization;
	}

	void exit() {
		authorization = false;
	}

	void save(fstream& file) {
		file.open(Pathes::PATH_TO_USERS + "\\" + username + "\\data.txt", fstream::out);
		file << password << "\n";
		file.close();
	}

	string get_username() {
		return username;
	}


	int set_username(string username) {
		change_user_directory(this->username, username);
		this->username = username;
		return 0;
	}
	
	static int change_user_directory(string old_username, string new_username) {
		return DirectoryMenu::change_directory_name((Pathes::PATH_TO_USERS + "\\" + old_username), (Pathes::PATH_TO_USERS + "\\" + new_username));
	}

	static void registration(fstream& file, string username, string password) {
		_mkdir(Pathes::PATH_TO_USERS.c_str());
		if (_mkdir((Pathes::PATH_TO_USERS + "\\" + username).c_str()) != 0)
			throw exception("Користувач уже існує!");
		User tmp = User(username, password);
		tmp.save(file);
	}

	static void delete_user(string username) {
		
	}

	static User login(fstream& file,string username, string password) {

		file.open(Pathes::PATH_TO_USERS+"\\" + username + "\\data.txt", fstream::in);
		if (!file.is_open())
			throw exception("Такого користувача не існує!");
		string check;
		file >> check;
		file.close();
		
		if (check == password)
			return check_admin(file,User(username, password));
		else
			throw exception("Неправильний пароль!");
	
	}

};