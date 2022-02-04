#pragma once
#include <iostream>
#include <fstream>
#include <algorithm>
#include <direct.h>
#include <string>
#include <filesystem>
#include <list>
#include "FilePathes.h"
#include "Test.h"
#include "User.h"
namespace fs = std::filesystem;


class Menu
{
	fstream fs;
	User user;

	void create_basic_admin() {
		fs.open(Pathes::MAIN_PATH + "\\admin.txt", fstream::out);
		fs << "admin";
		fs.close();
		_mkdir((Pathes::PATH_TO_USERS + "\\admin").c_str());
		fs.open(Pathes::PATH_TO_USERS + "\\admin\\data.txt", fstream::out);
		fs << "admin";
		fs.close();

	}

	void regestration() {
		string username, password;
		cout << "-==ÐÅªÑÒÐÀÖ²ß=--\n";
		cout << "Óâåäè ñâ³é íîâèé í³êíåéì: \n";
		cin >> username;
		cout << "Óâåäè ñâ³é íîâèé ïàðîëü: \n";
		cin >> password;
		user = User::regestration(fs, username, password);
	}

	void login() {
		string username, password;
		cout << "-==ÓÂ²ÉÒÈ=--\n";
		cout << "Óâåäè ñâ³é í³êíåéì: \n";
		cin >> username;
		cout << "Óâåäè ñâ³é ïàðîëü: \n";
		cin >> password;
		user = User::login(fs, username, password);
	}

	int check_users() {
		return get_directories(Pathes::PATH_TO_USERS).size();
	}

public:
	list<string> get_all_from_directories(string path) {
		list<string> directories;
		for (const auto& entry : fs::directory_iterator(path)) {
			string directory = entry.path().string();

			directories.push_back(directory);

		}
		return directories;
	}

	list<string>get_files(string path) {
		list<string> directories = get_all_from_directories(path);
		directories.remove_if([](string& str) {
			return (str.find(".txt") == string::npos);
			});
		return directories;
	}

	list<string> get_directories(string path) {
		list<string> directories = get_all_from_directories(path);
		directories.remove_if([](string& str) {
			return !(str.find(".txt") == string::npos);
			});
		return directories;
	}

	int get_index_of_directory(string path, list<string> directories) {
		auto it = directories.begin();
		for (int i = 0; i < directories.size(); i++, it++) {
			it->erase(it->begin(), it->begin() + path.length());
			it->erase(remove(it->begin(), it->end(), '\\'), it->end());
			auto pos = it->find(".txt");
			if (pos != std::string::npos)
				it->erase(it->find(".txt"), 4);
			cout << i + 1 << ". " << *it << "\n";
		}
		int choice;
		do {
			(cin >> choice).get();

		} while (choice < 1 || choice > directories.size());
		return choice - 1;
	}

	void lunch_test() {
		list<string> directories = get_directories(Pathes::PATH_TO_TESTS);
		auto it = directories.begin();
		advance(it, get_index_of_directory(Pathes::PATH_TO_TESTS, directories));
		string path = *it;
		directories.clear();
		directories = get_files(path);
		it = directories.begin();
		advance(it, get_index_of_directory(path, directories));

		fs.open(*it, fstream::in);
		Test t = Test::load(fs);
		t.start(0, 0);
		fs.close();

	}

	Menu() {
		do {
			try {

				if (_mkdir(Pathes::MAIN_PATH.c_str()) == 0 || _mkdir(Pathes::PATH_TO_USERS.c_str()) == 0 || check_users() <= 1) {
					create_basic_admin();
					regestration();
				}
				else
					login();
			}
			catch (exception exp) {
				cout << exp.what() << "\n";
			}
		} while (!user.is_authorization());

		cout << user.is_admin();

	}
};

