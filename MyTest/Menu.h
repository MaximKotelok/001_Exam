#pragma once
#include <iostream>
#include <fstream>
#include <algorithm>
#include <direct.h>
#include <string>
#include <list>

#include "User.h"
#include "Settings.h"
#include "Test.h"
#include "Statistic.h"



class Menu
{
	fstream file_editor;
	User user;

	void set_admin(string username);

	void registration(bool is_admin);

	void login();

	void change_password();

	bool check_users();

	void regular_user_menu();

	void admin_menu();

public:

	void lunch_test();

	void start();
};

