#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
#include <direct.h>

using namespace std;



class Question {
	string question;
	vector<string> answers;
	string correct_answer;
public:
	Question() {
	}

	Question(string question, vector<string> answers, string correct_answer) {
		this->question = question;
		this->answers = answers;
		this->correct_answer = correct_answer;
	}
	
	void set_random_positions() {
		int new_pos;
		string tmp;
		int loop = rand() % 5;
		for (; loop >= 0; loop--) {
			for (int i = 0; i < answers.size(); i++) {
				do {
					new_pos = rand() % answers.size();
				} while (new_pos == i);
				tmp = answers[i];
				answers[i] = answers[new_pos];
				answers[new_pos] = tmp;
			}

		}
	}

	void print(int number) {

		cout << number << ". " << question << "\n";
		for (int i = 0; i < answers.size(); i++) {
			cout << (i + 1) << ") " << answers[i]<<"\n";
		}
	}

	int number_of_answers() {
		return answers.size();
	}

	bool is_correct(int answer) {
		bool res = (correct_answer == answers[answer - 1]);
		if (res)
			cout << "Правильно!\n";
		else
			cout << "Неправильно! Правильна відповідь: " + correct_answer << "\n";
		return res;
	}

	friend fstream& operator<<(fstream& fout, Question& quest) {
		string tmp = quest.question;
		replace(tmp.begin(), tmp.end(), ' ', '_');
		fout << tmp<<" ";
		tmp = quest.correct_answer;
		replace(tmp.begin(), tmp.end(), ' ', '_');
		fout << tmp << " ";

		for (auto it : quest.answers) {
			replace(it.begin(), it.end(), ' ', '_');
			fout << it << " ";
		}

		fout << "|\n";
		return fout;
	}

	friend fstream& operator>>(fstream& fin, Question& quest) {
		fin>>quest.question;
		replace(quest.question.begin(), quest.question.end(), '_', ' ');

		fin>> quest.correct_answer;
		replace(quest.correct_answer.begin(), quest.correct_answer.end(), '_', ' ');

		string answer;
		quest.answers.clear();
		while (fin>> answer) {
			if (answer == "|")
				break;
			replace(answer.begin(), answer.end(), '_', ' ');
			quest.answers.push_back(answer);

		}

		return fin;
	}
};
class Test
{
	string title;
	vector<Question> questions;
	int question_now;
	int stat;
	string path;

	Test() {}
	
	Test(string title, vector<Question> questions, string path) {
		this->title = title;
		this->questions = questions;
		this->path = path;
		question_now = 0;
		stat = 0;
	}

	void save(fstream& file) {
		file.open(path+"\\test.txt", fstream::out);
		string tmp = title;
		replace(tmp.begin(), tmp.end(), ' ', '_');
		file << tmp<<"\n";
		for (auto it = questions.begin(); it != questions.end(); it++) {
			file << *it;
			if (it != --questions.end())
				file << "next\n";
		}
		file << "end\n";
		file.close();

	}


	string get_path_to_result() {
		string res = path;
		int index = -1;
		for (int i = 0; i < res.length(); i++)
			if (res[i] == '\\')
				index = i;
		res.erase(res.begin() + index, res.end());
		res += "\\results";
		return res;
	}


public:


	static double calculate_score(int stat, int size) {
		double total = stat;
		total /= size;
		total *= 100;
		return total;
	}

	string get_title() {
		return title;
	}

	string start(fstream& file,string username) {
		_mkdir(get_path_to_result().c_str());
		string result_path = get_path_to_result()+ "\\" + username + "_result.txt";
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

		for (; question_now < questions.size(); question_now++) {
			file.open(result_path, fstream::out);

			file << "not_ended " << question_now << " " << stat << "\n";
			file.close();
			questions[question_now].set_random_positions();
			questions[question_now].print(question_now +1);
			do {
				cin >> choice;

			} while (choice <= 0 || choice > questions[question_now].number_of_answers());

			this->stat += questions[question_now].is_correct(choice);

		}
		file.open(result_path, fstream::out);
		result = to_string(stat) + " " + to_string(questions.size()) + "\n";
		file << "ended " << result;
		file.close();
		}
		else {
			file >> stat;
			file.close();

		}
		double percent = calculate_score(stat, questions.size());
		cout << username << " - " << title << " | " << stat << "/" << questions.size() << " | " << percent << "% | Це " << percent * 0.12 << " балів\n";
		return result;
	}


	static Test create(fstream& file, string path) {
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
			cout << "Питання: ";
			getline(cin, question);
			if (question == "EXIT")
				break;
			answers.clear();

			do{
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
		_mkdir((path + "\\results").c_str());
		t.save(file);
		return t;
	}

	static Test load(fstream& file, string path) {
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
	
};

