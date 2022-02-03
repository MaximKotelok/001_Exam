#include <iostream>
#include <Windows.h>
#include "User.h"

#define PATH "/my_test"

fstream User::file;
string User::path;
int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	User::init(PATH);
	try {
		//User::regestration("Maxim", "maxim15102003");
		User::login("Maxim", "maxim15102003");

	}
	catch (exception exp) {
		cout << exp.what();
	}


	return 0;
}