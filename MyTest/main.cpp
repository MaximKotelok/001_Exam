#include <iostream>
#include <Windows.h>
#include <string>
#include "User.h"
#include "Test.h"
#include "FilePathes.h"


const string Pathes::MAIN_PATH = "/my_test";
const string Pathes::PATH_TO_USERS = MAIN_PATH + "/users";
const string Pathes::PATH_TO_TESTS = MAIN_PATH + "/tests";

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
	string directory = "/Українська_мова";
	string path = Pathes::PATH_TO_TESTS + directory;
	_mkdir(Pathes::PATH_TO_TESTS.c_str());
	_mkdir(path.c_str());
	fs.open(path +"/test.txt", fstream::in);
	
	Test t = Test::load(fs);
	fs.close();
	t.start(0, 0);

	return 0;
}