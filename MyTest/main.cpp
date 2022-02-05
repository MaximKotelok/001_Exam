#include <iostream>
#include <Windows.h>
#include <time.h>
#include <string>
#include "User.h"
#include "Test.h"
#include "FilePathes.h"
#include "Menu.h"
#include "Statistic.h"

ostream& operator<<(ostream& os, const element el) {
	double percent = Test::calculate_score(el.correct, el.all_questions);
	os << el.username << " - " << el.title << " | "<< el.correct <<"/" << el.all_questions << " | " << percent << "% | ÷е " << percent * 0.12 << " бал≥в\n";
	return os;
}

fstream& operator<<(fstream& fout, const element el) {
	double percent = Test::calculate_score(el.correct, el.all_questions);
	fout << el.username << " - " << el.title << " | " << el.correct << "/" << el.all_questions << " | " << percent << "% | ÷е " << percent * 0.12 << " бал≥в\n";
	return fout;
}

int main() {
	srand(time(0));
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
	////}
	// 
	Menu();
	//string directory = "/”крањнська_мова";
	//string path = Pathes::PATH_TO_TESTS + directory;
	//_mkdir(Pathes::PATH_TO_TESTS.c_str());
	//_mkdir(path.c_str());
	//fs.open(path +"/test.txt", fstream::in);
	//
	//Test t = Test::load(fs);
	//fs.close();
	//t.start(0, 0);

	return 0;
}