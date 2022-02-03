#pragma once

#include <iostream>
#include <fstream>
#include <direct.h>
#include <string>

#define PATH "/users/"

using namespace std;
class User
{
	string username;
	string password;
	static fstream file;
	static string path;
	User(string username, string password) {
		this->username = username;
		this->password = password;
	}
public:

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
			return User(username, password);
		else
			throw exception("Wrong password!");

	}

	static void init(string new_path) {

		path = new_path+PATH;
		
		_mkdir(new_path.c_str());
		_mkdir(path.c_str());
	}

	void save() {
		file.open(path+username + "/data.txt", fstream::out);
		file << password << "\n";
		file.close();
	}
	

};

