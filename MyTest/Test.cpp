#include "Test.h"
/*QUESTION*/
Question::Question() {
}

Question::Question(string question, vector<string> answers, string correct_answer) {
	this->question = question;
	this->answers = answers;
	this->correct_answer = correct_answer;
}

void Question::set_random_positions() {
	int new_pos;
	string tmp;
	int loop = rand() % 5;
	for (; loop >= 0; loop--) {
		for (size_t i = 0, size = answers.size(); i < size; i++) {
			do {
				new_pos = rand() % answers.size();
			} while (new_pos == i);
			tmp = answers[i];
			answers[i] = answers[new_pos];
			answers[new_pos] = tmp;
		}

	}
}

void Question::print(int number) {

	cout << number << ". " << question << "\n";
	for (size_t i = 0, size = answers.size(); i < size; i++) {
		cout << (i + 1) << ") " << answers[i] << "\n";
	}
}

int Question::number_of_answers() {
	return answers.size();
}

bool Question::is_correct(int answer) {
	bool res = (correct_answer == answers[answer - 1]);
	if (res)
		cout << "Правильно!\n";
	else
		cout << "Неправильно! Правильна відповідь: " + correct_answer << "\n";
	return res;
}

/* TEST */
Test::Test() {
	title = "EMPTY_TEST";
	question_now = 0;
	stat = 0;
	path = "";
}

Test::Test(string title, vector<Question> questions, string path) {
	this->title = title;
	this->questions = questions;
	this->path = path;
	question_now = 0;
	stat = 0;
}

void Test::save(fstream& file) {
	file.open(path + "\\test" + SettingsConst::FILE_EXTENSION, fstream::out);
	string tmp = title;
	replace(tmp.begin(), tmp.end(), ' ', '_');
	file << tmp << "\n";
	for (auto it = questions.begin(); it != questions.end(); it++) {
		file << *it;
		if (it != --questions.end())
			file << "next\n";
	}
	file << "end\n";
	file.close();

}


string Test::get_path_to_result() {
	string res = path;
	int index = -1;
	for (size_t i = 0, size = res.size(); i < size; i++)
		if (res[i] == '\\')
			index = i;
	res.erase(res.begin() + index, res.end());
	res += "\\" + SettingsConst::RESULT_DIRECTORY;
	return res;
}


double Test::calculate_score(int stat, int size) {
	double total = stat;
	total /= size;
	total *= 100;
	return total;
}

string Test::get_title() {
	return title;
}

bool Test::delete_test_result(string category, string test_name, string username) {
	DirectoryMenu::delete_path(SettingsConst::PATH_TO_USERS + "\\" + username + "\\" + SettingsConst::RESULT_DIRECTORY + "\\" + category + "\\" + test_name + SettingsConst::FILE_EXTENSION);
	DirectoryMenu::delete_path(SettingsConst::PATH_TO_TESTS + "\\" + category + "\\" + test_name + "\\" + SettingsConst::RESULT_DIRECTORY + "\\" + username + "_result" + SettingsConst::FILE_EXTENSION);
	return true;
}

string Test::start(fstream& file, string username) {
	_mkdir(get_path_to_result().c_str());
	string result_path = get_path_to_result() + "\\" + username + "_result" + SettingsConst::FILE_EXTENSION;
	file.open(result_path, fstream::in);
	string status;
	string result;
	if (!file.is_open()) {
		this->question_now = 0;
		this->stat = 0;
	}
	else {
		file >> status;
		if (status == "not_ended")
			file >> question_now >> stat;
	}
	if (status != "ended") {

		file.close();
		int choice;

		for (size_t size = questions.size(), now = question_now; now < size; now++) {
			question_now = now;
			file.open(result_path, fstream::out);

			file << "not_ended " << now << " " << stat << "\n";
			file.close();
			questions[now].set_random_positions();
			questions[now].print(now + 1);
			do {
				cin >> choice;

			} while (choice <= 0 || choice > questions[question_now].number_of_answers());

			this->stat += questions[now].is_correct(choice);

			system("pause");
			system("cls");

		}
	}
	else {
		file >> stat;
		file.close();

	}
	file.open(result_path, fstream::out);
	result = to_string(stat) + " " + to_string(questions.size()) + "\n";
	file << "ended " << result;
	file.close();
	double percent = calculate_score(stat, questions.size());
	cout << username << " - " << title << " | " << stat << "/" << questions.size() << " | " << percent << "% | Це " << percent * 0.12 << " балів\n";
	return result;
}


Test Test::create(fstream& file, string path) {
	string title;
	string question;
	string answer;
	vector<string> answers;
	vector<Question> questions;

	cout << "Назва тесту: ";
	getline(cin, title);
	path += "\\" + title;
	_mkdir(path.c_str());
	do {
		system("cls");
		cout << "Питання: ";
		getline(cin, question);
		if (question == "EXIT")
			break;
		answers.clear();

		do {
			cout << "Введи неправильну відповідь: ";
			getline(cin, answer);
			if (answer == "EXIT") {
				if (answers.size() != 0) {

					cout << "Введи правильну відповідь: ";
					getline(cin, answer);
					answers.push_back(answer);
					break;
				}
				else {
					cout << "Має бути мінімум одна неправильна відповідь!\n";
					continue;
				}
			}
			answers.push_back(answer);
		} while (true);
		questions.push_back(Question(question, answers, answer));

	} while (true);
	Test t = Test(title, questions, path);
	t.path = path;
	_mkdir((path + "\\" + SettingsConst::RESULT_DIRECTORY).c_str());
	t.save(file);
	return t;
}

Test Test::load(fstream& file, string path) {
	file.open(path, fstream::in);
	Test t;
	file >> t.title;
	replace(t.title.begin(), t.title.end(), '_', ' ');
	vector<Question> questions;
	Question el;
	string check_end;

	do {

		file >> el;
		questions.push_back(el);
		file >> check_end;

	} while (check_end != "end");
	t.questions = questions;
	t.path = path;
	file.close();
	return t;
}

