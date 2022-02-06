#pragma once
#include <iostream>
#include <fstream>
#include <algorithm>
#include <direct.h>
#include <string>
#include <list>

#include "User.h"
#include "FilePathes.h"
#include "Test.h"
#include "Statistic.h"



class Menu
{
	fstream fs;
	User user;

	void create_basic_admin(string username) {
		fs.open(Pathes::MAIN_PATH + "\\admin.txt", fstream::out);
		fs << username;
		fs.close();
	}

	void registration(bool is_admin) {
		string username, password;
		cout << "-==РЕЄСТРАЦІЯ=--\n";
		cout << "Уведи свій новий нікнейм: \n";
		cin >> username;
		cout << "Уведи свій новий пароль: \n";
		cin >> password;
		User::registration(fs, username, password);
		if (is_admin)
			create_basic_admin(username);
	}

	void login() {
		string username, password;
		cout << "-==УВІЙТИ=--\n";
		cout << "Уведи свій нікнейм: \n";
		cin >> username;
		cout << "Уведи свій пароль: \n";
		cin >> password;
		user = User::login(fs, username, password);
	}

	int check_users() {
		return DirectoryMenu::get_directories(Pathes::PATH_TO_USERS).size();
	}

	void regular_user_menu() {
		cout << "--= USER MENU=--\n";
		cout << "0. Вийти\n";
		cout << "1. Запустити тест\n";
		cout << "2. Результати тестів\n";

		int choice;

		(cin >> choice).get();

		if (choice == 0) {
			user.exit();
			return;
		}

		switch (choice) {

		case 1: 
			lunch_test();
			  break;
		case 2:
			Statistic::print_statistic(fs, Statistic::get_user_statistic(fs, user.get_username()));
			break;
		}
	}

	void admin_menu() {
		cout << "--= ADMIN MENU=--\n";
		cout << "0. Вийти\n";
		cout << "1. Змінити ім'я\n";
		cout << "2. Змінити пароль\n";
		cout << "3. Передивитися статистику користувача\n";
		cout << "4. Передивитися статистику категорії\n";
		cout << "5. Передивитися статистику конкретного тесту\n";
		cout << "6. Додати категорію\n";
		cout << "7. Додати тест\n";
		cout << "8. Додати користувача\n";
		cout << "9. Видалити користувача\n";
		cout << "10. Видалити результати теста користувача\n";

		int choice;

		(cin >> choice).get();

		if (choice == 0) {
			user.exit();
			return;
		}
		try {

			switch (choice) {
			case 1: {
				string new_username;
				cin >> new_username;
				if (user.set_username(new_username) == 0) {
					fs.open(Pathes::MAIN_PATH + "\\admin.txt", fstream::out);
					fs << new_username;
					fs.close();
				}

			}
				  break;
			case 2:
			{
				string new_password;
				cin >> new_password;

				fs.open(Pathes::PATH_TO_USERS + "\\" + user.get_username() + "\\data.txt", fstream::out);
				fs << new_password;
				fs.close();

			}
			break;
			case 3: {

				string path = Pathes::PATH_TO_USERS;
				if (DirectoryMenu::menu(path, "results", user.get_username())) {
					Statistic::print_statistic(fs, Statistic::get_user_statistic(fs, DirectoryMenu::get_end_of_path(path, 1)));
				}
			}
				  break;
			case 4:
			{
				string path = Pathes::PATH_TO_TESTS;
				if (DirectoryMenu::menu(path, "end", "")) {
					string category = DirectoryMenu::get_end_of_path(path, 1);
					Statistic::print_statistic(fs, Statistic::get_category_statistic(fs, category));
				}
			}
			break;
			case 5:
			{
				string path = Pathes::PATH_TO_TESTS;
				if (DirectoryMenu::menu(path, "results", "end")) {
					string category = DirectoryMenu::get_end_of_path(path, 2);
					string test = DirectoryMenu::get_end_of_path(path, 1);
					Statistic::print_statistic(fs, Statistic::get_test_statistic(fs, category, test));
				}
			}break;
			case 6: {
				string directory_name;
				cout << "Назва директорії: ";
				getline(cin, directory_name);
				if (_mkdir((Pathes::PATH_TO_TESTS + "\\" + directory_name).c_str()) == 0)_mkdir((Pathes::PATH_TO_TESTS + "\\" + directory_name + "\\" + "end").c_str());

			}
				  break;
			case 7: {
				string path = Pathes::PATH_TO_TESTS;
				if (DirectoryMenu::menu(path, "end", "")) {
					Test::create(fs, path);
				}
			}
				  break;
			case 8:
				registration(false);
				break;
			case 9:
			{
				string path_to_user;
				string path = Pathes::PATH_TO_USERS;
				if (DirectoryMenu::menu(path, "results", user.get_username())) {
					path_to_user = path;
					list<string> pathes = DirectoryMenu::get_directories(path + "\\results");
					for (auto tmp_path : pathes) {
						list<string> files = DirectoryMenu::get_files(tmp_path);
						for (auto tests : files) {
							Test::delete_test_result(DirectoryMenu::get_end_of_path(tests, 2), DirectoryMenu::path_to_title(tests, ".txt"), DirectoryMenu::get_end_of_path(tests, 4));
						}
					}
				}
				DirectoryMenu::delete_path(path_to_user);
			}
				break;
			case 10:
			{
				string path = Pathes::PATH_TO_USERS;
				if (DirectoryMenu::menu(path, "", user.get_username(),true)) {
					Test::delete_test_result(DirectoryMenu::get_end_of_path(path, 2), DirectoryMenu::path_to_title(path, ".txt"), DirectoryMenu::get_end_of_path(path, 4));
				}
			}
			break;
			}


		}
		catch (exception exp) {
			cout << exp.what() << "\n";
		}
	}


public:


	void lunch_test() {
		string path = Pathes::PATH_TO_TESTS;
		if (DirectoryMenu::menu(path, "results", "end")) {
			path += "\\test.txt";


		Test my_test = Test::load(fs, path);
		string score = my_test.start(fs, user.get_username());
		string title = DirectoryMenu::get_end_of_path(path, 3);
		cout << title<<"---------";
		_mkdir((Pathes::PATH_TO_USERS + "\\" + user.get_username() + "\\results").c_str());
		_mkdir((Pathes::PATH_TO_USERS + "\\" + user.get_username() + "\\results\\"+ title).c_str());
		fs.open(Pathes::PATH_TO_USERS + "\\" + user.get_username() + "\\results\\" + title+"\\"+ my_test.get_title() + ".txt", fstream::out);
		fs << score;
		fs.close();
		}

	}

	Menu() {
		do {
			try {

				if (_mkdir(Pathes::MAIN_PATH.c_str()) == 0 || _mkdir(Pathes::PATH_TO_USERS.c_str()) == 0 || check_users() == 0)
					registration(check_users() == 0);
				
				else
					login();
			}
			catch (exception exp) {
				cout << exp.what() << "\n";
			}
		} while (!user.is_authorization());

		do {
			cout << "--=" << user.get_username() << "=--\n";
			if (user.is_admin())
				admin_menu();
			else
				regular_user_menu();
		} while (user.is_authorization());

	}
};

