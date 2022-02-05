#pragma once
#include <fstream>

#include "DirectoryMenu.h"
#include "FilePathes.h"


using namespace std;
class element {
	string username;
	string title;
	int correct;
	int all_questions;


public:
	element(string username, string title, int correct, int all_questions) {
		this->username = username;
		this->title = title;
		this->correct = correct;
		this->all_questions = all_questions;
	}

	friend ostream& operator<<(ostream& os, const element el);
	friend fstream& operator<<(fstream& fout, const element el);
};

class Statistic
{
	static string path_to_title(string path, string extension) {
		int index = -1;
		for (int i = 0; i < path.size(); i++)
			if (path[i] == '\\')
				index = i;

		return path.substr(index + 1, path.size() - index - 1 - extension.size());
	}
public:
	static void print_statistic(fstream& file, list<element> statistic) {
		file.open(Pathes::PATH_TO_STATISTIC, fstream::out);
		for_each(statistic.begin(), statistic.end(), [&file](element& el) {
			file << el;
			cout << el;
			});
		file.close();
	}


	static list<element> get_user_statistic(fstream& file, string username) {
		list<element> result;
		list<string> directories = DirectoryMenu::get_directories(Pathes::PATH_TO_USERS + "\\" + username+"\\results");
		if (directories.size() == 0)
			throw exception("Користувач не знайден");
		for (auto path : directories) {
			list<string> files = DirectoryMenu::get_files(path);
			for (auto results : files) {

			file.open(results, fstream::in);
			string title = path_to_title(results, ".txt");
			int correct, all_questions;
			file >> correct >> all_questions;

			result.push_back({ username, title, correct, all_questions });
			file.close();
			}

		}
		return result;



	}

	static list<element> get_category_statistic(fstream& file, string category_name) {
		list<element> result;
		list<string> tests = DirectoryMenu::get_directories(Pathes::PATH_TO_TESTS + "\\" + category_name);
		if (tests.size() == 0)
			throw exception("Категорія не знайдена");
		for (auto path : tests) {
			list<element> second_result = get_test_statistic(file, category_name, path_to_title(path, ""));
			copy(second_result.begin(), second_result.end(), back_inserter(result));

		}
		return result;
	}

	static list<element> get_test_statistic(fstream& file, string category_name, string test_name) {
		list<element> result;
		list<string> files = DirectoryMenu::get_files(Pathes::PATH_TO_TESTS + "\\" + category_name + "\\"+test_name+"\\results");
		for (auto file_name : files) {
			file.open(file_name, fstream::in);
			string status;
			file >> status;
			if (status == "ended") {
				int correct, all_questions;
				file >> correct >> all_questions;
				string username = path_to_title(file_name, "_result.txt");
				string title = test_name;

				result.push_back({ username , title, correct, all_questions });
			}
			file.close();
		}
		return result;
	}

};

