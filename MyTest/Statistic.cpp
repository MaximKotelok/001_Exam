#include "Statistic.h"

/* ELEMENT */
element::element(string username, string title, int correct, int all_questions) {
	this->username = username;
	this->title = title;
	this->correct = correct;
	this->all_questions = all_questions;
}


/* STATISTIC */

void Statistic::print_statistic(fstream& file, list<element> statistic) {
	file.open(SettingsConst::PATH_TO_STATISTIC, fstream::out);
	for_each(statistic.begin(), statistic.end(), [&file](element& el) {
		file << el;
		cout << el;
		});
	file.close();
}


list<element> Statistic::get_user_statistic(fstream& file, string username) {
	list<element> result;
	_mkdir((SettingsConst::PATH_TO_USERS + "\\" + username + "\\" + SettingsConst::RESULT_DIRECTORY).c_str());
	list<string> directories = DirectoryMenu::get_directories(SettingsConst::PATH_TO_USERS + "\\" + username + "\\" + SettingsConst::RESULT_DIRECTORY);
	if (directories.size() == 0)
		throw exception("Тестів не знайдено");
	for (auto path : directories) {
		list<string> files = DirectoryMenu::get_files(path);
		for (auto results : files) {

			file.open(results, fstream::in);
			string title = DirectoryMenu::path_to_title(results, SettingsConst::FILE_EXTENSION);
			int correct, all_questions;
			file >> correct >> all_questions;

			result.push_back({ username, title, correct, all_questions });
			file.close();
		}

	}
	return result;



}

list<element> Statistic::get_category_statistic(fstream& file, string category_name) {
	list<element> result;
	list<string> tests = DirectoryMenu::get_directories(SettingsConst::PATH_TO_TESTS + "\\" + category_name);
	if (tests.size() == 0)
		throw exception("Категорія не знайдена");
	for (auto path : tests) {
		list<element> second_result = get_test_statistic(file, category_name, DirectoryMenu::path_to_title(path, ""));
		copy(second_result.begin(), second_result.end(), back_inserter(result));

	}
	return result;
}

list<element> Statistic::get_test_statistic(fstream& file, string category_name, string test_name) {
	list<element> result;
	list<string> files = DirectoryMenu::get_files(SettingsConst::PATH_TO_TESTS + "\\" + category_name + "\\" + test_name + "\\" + SettingsConst::RESULT_DIRECTORY);
	for (auto file_name : files) {
		file.open(file_name, fstream::in);
		string status;
		file >> status;
		if (status == "ended") {
			int correct, all_questions;
			file >> correct >> all_questions;
			string username = DirectoryMenu::path_to_title(file_name, "_result" + SettingsConst::FILE_EXTENSION);
			string title = test_name;

			result.push_back({ username , title, correct, all_questions });
		}
		file.close();
	}
	return result;
}

