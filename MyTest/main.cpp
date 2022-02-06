#include <iostream>
#include <Windows.h>
#include <time.h>

#include "Menu.h"

fstream& operator<<(fstream& fout, Question& quest) {
	string tmp = quest.question;
	replace(tmp.begin(), tmp.end(), ' ', '_');
	fout << tmp << " ";
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

fstream& operator>>(fstream& fin, Question& quest) {
	fin >> quest.question;
	replace(quest.question.begin(), quest.question.end(), '_', ' ');

	fin >> quest.correct_answer;
	replace(quest.correct_answer.begin(), quest.correct_answer.end(), '_', ' ');

	string answer;
	quest.answers.clear();
	while (fin >> answer) {
		if (answer == "|")
			break;
		replace(answer.begin(), answer.end(), '_', ' ');
		quest.answers.push_back(answer);

	}

	return fin;
}

ostream& operator<<(ostream& os, const element& el) {
	double percent = Test::calculate_score(el.correct, el.all_questions);
	os << el.username << " - " << el.title << " | "<< el.correct <<"/" << el.all_questions << " | " << percent << "% | ÷е " << percent * 0.12 << " бал≥в\n";
	return os;
}

fstream& operator<<(fstream& fout, const element& el) {
	double percent = Test::calculate_score(el.correct, el.all_questions);
	fout << el.username << " - " << el.title << " | " << el.correct << "/" << el.all_questions << " | " << percent << "% | ÷е " << percent * 0.12 << " бал≥в\n";
	return fout;
}

int main() {
	srand(time(0));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Menu program;
	program.start();

	return 0;
}