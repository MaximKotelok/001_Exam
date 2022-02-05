#pragma once
#include <string>
using namespace std;
class Pathes {
public:
	inline static const string MAIN_PATH = "my_test";
	inline static const string PATH_TO_USERS = MAIN_PATH + "\\users";
	inline static const string PATH_TO_TESTS = MAIN_PATH + "\\tests";
	inline static const string PATH_TO_STATISTIC = MAIN_PATH + "\\statistic.txt";
};
