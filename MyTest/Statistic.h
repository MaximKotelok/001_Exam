#pragma once
#include <fstream>

#include "DirectoryMenu.h"
#include "Settings.h"


using namespace std;
class element {
	string username;
	string title;
	int correct;
	int all_questions;


public:
	element(string username, string title, int correct, int all_questions);

	friend ostream& operator<<(ostream& os, const element& el);
	friend fstream& operator<<(fstream& fout, const element& el);
};

////////////////////////////////////////////////////////////////////////////////////////

class Statistic
{
public:
	static void print_statistic(fstream& file, list<element> statistic);

	static list<element> get_user_statistic(fstream& file, string username);

	static list<element> get_category_statistic(fstream& file, string category_name);

	static list<element> get_test_statistic(fstream& file, string category_name, string test_name);

};

