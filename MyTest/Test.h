#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
#include <direct.h>

#include "DirectoryMenu.h"
#include "Settings.h"
using namespace std;



class Question {
	string question;
	vector<string> answers;
	string correct_answer;
public:
	Question();

	Question(string question, vector<string> answers, string correct_answer);
	
	void set_random_positions();

	void print(int number);

	int number_of_answers();

	bool is_correct(int answer);

	friend fstream& operator<<(fstream& fout, Question& quest);

	friend fstream& operator>>(fstream& fin, Question& quest);
};
class Test
{
	string title;
	vector<Question> questions;
	int question_now;
	int stat;
	string path;

	Test();
	
	Test(string title, vector<Question> questions, string path);

	void save(fstream& file);


	string get_path_to_result();


public:


	static double calculate_score(int stat, int size);

	string get_title();

	static bool delete_test_result(string category, string test_name, string username);

	string start(fstream& file, string username);


	static Test create(fstream& file, string path);

	static Test load(fstream& file, string path);
	
};

