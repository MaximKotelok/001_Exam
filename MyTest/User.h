#pragma once
#include <fstream>

#include "Settings.h"
#include "DirectoryMenu.h"
#include "Test.h"

using namespace std;
class User
{
	string username;
	string password;
	bool admin;

	bool authorization;

	User(string username, string password);

	static User check_admin(fstream& file, User user);

public:
	User();

	bool is_admin();

	bool is_authorization();

	void exit();

	void save(fstream& file);

	string get_username();


	int set_username(string& username);


	static void registration(fstream& file, string& username, string password);

	static User login(fstream& file, string username, string password);

};