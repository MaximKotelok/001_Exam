#include <iostream>
#include <Windows.h>
#include "User.h"

#define PATH "/my_test"

fstream User::file;
string User::path;
string User::abstract_path;

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	User::init(PATH);
	try {
		//User::regestration("Maxim", "maxim15102003");
		User us = User::login("Maxim", "maxim15102003");
		if (us.is_admin())
			cout << "User is admin\n";
		else
			cout << "User is not admin\n";

	}
	catch (exception exp) {
		cout << exp.what();
	}


	return 0;
}