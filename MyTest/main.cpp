#include <iostream>
#include <Windows.h>
#include "User.h"
#include "Test.h"

#define MAIN_PATH "/my_test"
#define PATH_TO_USERS "/my_test/users"
#define PATH_TO_TESTS "/my_test/tests"


int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	fstream fs;
	//User::init(PATH);
	//try {
	//	//User::regestration("Maxim", "maxim15102003");
	//	User us = User::login("Maxim", "maxim15102003");
	//	if (us.is_admin())
	//		cout << "User is admin\n";
	//	else
	//		cout << "User is not admin\n";

	//}
	//catch (exception exp) {
	//	cout << exp.what();
	//}
	string directory = "/Історія";
	string path = PATH_TO_TESTS + directory;
	_mkdir(PATH_TO_TESTS);
	_mkdir(path.c_str());
	fs.open(path +"/test.txt", fstream::in);
	
	Test t = Test::create(fs);
	fs.close();
	t.start(0, 0);

	return 0;
}