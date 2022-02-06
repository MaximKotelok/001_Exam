#include "User.h"

User::User(string username, string password) {
	this->username = username;
	this->password = password;
	admin = false;
	authorization = true;
}

User User::check_admin(fstream& file, User user) {
	string username = user.username;
	file.open(SettingsConst::MAIN_PATH + "\\admin.txt", fstream::in);
	string name;
	file >> name;
	file.close();

	if (name == user.username)
		user.admin = true;

	return user;
}

User::User() {
	username = password = "guest";
	authorization = admin = false;
}

bool User::is_admin() {
	return admin;
}
bool User::is_authorization() {
	return authorization;
}

void User::exit() {
	authorization = false;
}

void User::save(fstream& file) {
	_mkdir((SettingsConst::PATH_TO_USERS + "\\" + username + "\\" + SettingsConst::RESULT_DIRECTORY).c_str());
	file.open(SettingsConst::PATH_TO_USERS + "\\" + username + "\\data.txt", fstream::out);
	file << password << "\n";
	file.close();
}

string User::get_username() {
	return username;
}


int User::set_username(string username) {
	transform(username.begin(), username.end(), username.begin(),
		[](char& c) { return std::tolower(c); });
	if (DirectoryMenu::change_directory_name((SettingsConst::PATH_TO_USERS + "\\" + this->username), (SettingsConst::PATH_TO_USERS + "\\" + username)) != 0) {
		if (DirectoryMenu::get_files(SettingsConst::PATH_TO_USERS + "\\" + username).size() != 0)
			throw exception("Цей нікнейм зайнятий!");
		else
			throw exception("ERROR");
	}
	this->username = username;
	return 0;
}


void User::registration(fstream& file, string& username, string password) {
	transform(username.begin(), username.end(), username.begin(),
		[](char& c) { return std::tolower(c); });
	_mkdir(SettingsConst::PATH_TO_USERS.c_str());
	if (_mkdir((SettingsConst::PATH_TO_USERS + "\\" + username).c_str()) != 0)
		throw exception("Користувач уже існує!");
	User tmp = User(username, password);
	tmp.save(file);
}

User User::login(fstream& file, string username, string password) {
	transform(username.begin(), username.end(), username.begin(),
		[](char& c) { return std::tolower(c); });
	file.open(SettingsConst::PATH_TO_USERS + "\\" + username + "\\data.txt", fstream::in);
	if (!file.is_open())
		throw exception("Такого користувача не існує!");
	string check;
	file >> check;
	file.close();

	if (check == password)
		return check_admin(file, User(username, password));
	else
		throw exception("Неправильний пароль!");

}
