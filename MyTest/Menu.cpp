#include "Menu.h"


void Menu::set_admin(string username) {
	file_editor.open(SettingsConst::PATH_TO_ADMIN_FILE, fstream::out);
	file_editor << username;
	file_editor.close();
}

void Menu::registration(bool is_admin) {
	string username, password;
	cout << "-==РЕЄСТРАЦІЯ=--\n";
	cout << "Уведи свій новий нікнейм: \n";
	cin >> username;
	cout << "Уведи свій новий пароль: \n";
	cin >> password;
	User::registration(file_editor, username, password);
	if (is_admin)
		set_admin(username);
}

void Menu::login() {
	string username, password;
	cout << "-==УВІЙТИ=--\n";
	cout << "Уведи свій нікнейм: \n";
	cin >> username;
	cout << "Уведи свій пароль: \n";
	cin >> password;
	user = User::login(file_editor, username, password);
}

void Menu::change_password() {
	string new_password;
	cout << "Новий пароль: ";
	cin >> new_password;

	file_editor.open(SettingsConst::PATH_TO_USERS + "\\" + user.get_username() + "\\data" + SettingsConst::FILE_EXTENSION, fstream::out);
	file_editor << new_password;
	file_editor.close();
}

bool Menu::check_users() {
	return !DirectoryMenu::get_directories(SettingsConst::PATH_TO_USERS).size();
}

void Menu::regular_user_menu() {
	cout << "--= USER MENU=--\n";
	cout << "0. Вийти\n";
	cout << "1. Запустити тест\n";
	cout << "2. Змінити пароль\n";
	cout << "3. Результати тестів\n";

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
		change_password();
		break;
	case 3:
		Statistic::print_statistic(file_editor, Statistic::get_user_statistic(file_editor, user.get_username()));
		break;
	}
}

void Menu::admin_menu() {
	cout << "--= ADMIN MENU=--\n";
	cout << "0. Вийти\n";
	cout << "1. Змінити нікнейм\n";
	cout << "2. Змінити пароль\n";
	cout << string(25, '=')<<"\n";
	cout << "3. Передивитися статистику користувача\n";
	cout << "4. Передивитися статистику категорії\n";
	cout << "5. Передивитися статистику конкретного тесту\n";
	cout << string(25, '=')<<"\n";
	cout << "6. Додати категорію\n";
	cout << "7. Додати тест\n";
	cout << string(25, '=')<<"\n";
	cout << "8. Видалити результати теста користувача\n";
	cout << "9. Додати користувача\n";
	cout << "10. Видалити користувача\n";

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
			cout << "Новий нікнейм: ";
			cin >> new_username;
			if (user.set_username(new_username) == 0)
				set_admin(new_username);

		}
			  break;
		case 2:
			change_password();
			break;
		case 3: {

			string path = SettingsConst::PATH_TO_USERS;
			if (DirectoryMenu::menu(path, SettingsConst::RESULT_DIRECTORY, user.get_username())) {
				Statistic::print_statistic(file_editor, Statistic::get_user_statistic(file_editor, DirectoryMenu::get_end_of_path(path, 1)));
			}
		}
			  break;
		case 4:
		{
			string path = SettingsConst::PATH_TO_TESTS;
			if (DirectoryMenu::menu(path, SettingsConst::END_DIRECTORY, "")) {
				string category = DirectoryMenu::get_end_of_path(path, 1);
				Statistic::print_statistic(file_editor, Statistic::get_category_statistic(file_editor, category));
			}
		}
		break;
		case 5:
		{
			string path = SettingsConst::PATH_TO_TESTS;
			if (DirectoryMenu::menu(path, SettingsConst::RESULT_DIRECTORY, SettingsConst::END_DIRECTORY)) {
				string category = DirectoryMenu::get_end_of_path(path, 2);
				string test = DirectoryMenu::get_end_of_path(path, 1);
				Statistic::print_statistic(file_editor, Statistic::get_test_statistic(file_editor, category, test));
			}
		}break;
		case 6: {
			_mkdir(SettingsConst::PATH_TO_TESTS.c_str());
			string directory_name;
			cout << "Назва директорії: ";
			getline(cin, directory_name);
			if (_mkdir((SettingsConst::PATH_TO_TESTS + "\\" + directory_name).c_str()) == 0 && _mkdir((SettingsConst::PATH_TO_TESTS + "\\" + directory_name + "\\" + SettingsConst::END_DIRECTORY).c_str()) == 0)
				cout << "Директорія успішно додана!\n";
			else
				cout << "Помилка створення директорії\n";


		}
			  break;
		case 7: {
			string path = SettingsConst::PATH_TO_TESTS;
			if (DirectoryMenu::menu(path, SettingsConst::END_DIRECTORY, "")) {
				Test::create(file_editor, path);
			}
		}
			  break;
		case 8:
		{
			string path = SettingsConst::PATH_TO_USERS;
			if (DirectoryMenu::menu(path, "", user.get_username(), true)) {
				Test::delete_test_result(DirectoryMenu::get_end_of_path(path, 2), DirectoryMenu::path_to_title(path, SettingsConst::FILE_EXTENSION), DirectoryMenu::get_end_of_path(path, 4));
			}
		}
		break;
		case 9:
			registration(false);
			break;
		case 10:
		{
			string path_to_user;
			string path = SettingsConst::PATH_TO_USERS;
			if (DirectoryMenu::menu(path, SettingsConst::RESULT_DIRECTORY, user.get_username())) {
				path_to_user = path;
				list<string> pathes = DirectoryMenu::get_directories(path + "\\" + SettingsConst::RESULT_DIRECTORY);
				for (auto tmp_path : pathes) {
					list<string> files = DirectoryMenu::get_files(tmp_path);
					for (auto tests : files) {
						Test::delete_test_result(DirectoryMenu::get_end_of_path(tests, 2), DirectoryMenu::path_to_title(tests, SettingsConst::FILE_EXTENSION), DirectoryMenu::get_end_of_path(tests, 4));
					}
				}
				DirectoryMenu::delete_path(path_to_user);
			}
		}
		break;
		}


	}
	catch (exception exp) {
		cout << exp.what() << "\n";
	}
}

void Menu::lunch_test() {
	string path = SettingsConst::PATH_TO_TESTS;
	if (DirectoryMenu::menu(path, SettingsConst::RESULT_DIRECTORY, SettingsConst::END_DIRECTORY)) {
		path += "\\test" + SettingsConst::FILE_EXTENSION;


		Test my_test = Test::load(file_editor, path);
		string score = my_test.start(file_editor, user.get_username());
		string title = DirectoryMenu::get_end_of_path(path, 3);
		_mkdir((SettingsConst::PATH_TO_USERS + "\\" + user.get_username() + "\\" + SettingsConst::RESULT_DIRECTORY).c_str());
		_mkdir((SettingsConst::PATH_TO_USERS + "\\" + user.get_username() + "\\" + SettingsConst::RESULT_DIRECTORY + "\\" + title).c_str());
		file_editor.open(SettingsConst::PATH_TO_USERS + "\\" + user.get_username() + "\\" + SettingsConst::RESULT_DIRECTORY + "\\" + title + "\\" + my_test.get_title() + SettingsConst::FILE_EXTENSION, fstream::out);
		file_editor << score;
		file_editor.close();
	}

}

void Menu::start() {

	do {
		try {

			if (_mkdir(SettingsConst::MAIN_PATH.c_str()) == 0 || _mkdir(SettingsConst::PATH_TO_USERS.c_str()) == 0 || check_users())
				registration(check_users());

			else
				login();
		}
		catch (exception exp) {
			cout << exp.what() << "\n";
			system("pause");
			system("cls");
		}

	} while (!user.is_authorization());
	system("cls");
	do {
		try {

			cout << "Ваш нікнейм: " << user.get_username() << "\n";
			if (user.is_admin())
				admin_menu();
			else
				regular_user_menu();
		}
		catch (exception exp) {
			cout << exp.what() << "\n";
		}
		system("pause");
		system("cls");
	} while (user.is_authorization());
}

