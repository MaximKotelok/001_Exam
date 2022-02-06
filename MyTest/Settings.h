#pragma once
#include <string>
using namespace std;
class SettingsConst {
public:
	inline static const string FILE_EXTENSION = ".txt";
	inline static const string RESULT_DIRECTORY = "results";
	inline static const string END_DIRECTORY = "end";

	inline static const string MAIN_PATH = "my_test";
	inline static const string PATH_TO_USERS = MAIN_PATH + "\\users";
	inline static const string PATH_TO_TESTS = MAIN_PATH + "\\tests";
	inline static const string PATH_TO_ADMIN_FILE = MAIN_PATH + "\\admin"+ FILE_EXTENSION;
	inline static const string PATH_TO_STATISTIC = MAIN_PATH + "\\statistic" + FILE_EXTENSION;
};
