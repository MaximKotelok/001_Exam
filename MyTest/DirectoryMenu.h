#pragma once
#include <list>
#include <iostream>
#include <filesystem>
#include <direct.h>

#include "Settings.h"

namespace fs = std::filesystem;
using namespace std;

class DirectoryMenu {
	static int get_index_of_directory(string path, list<string> directories);
public:

	static string path_to_title(string path, string extension);

	static string remove_end_of_path(string path);

	static string get_end_of_path(string path, int number);

	static bool delete_path(string path);

	static list<string> get_all_from_directories(string path);

	static list<string>get_files(string path);

	static list<string> get_directories(string path);

	static int change_directory_name(string old_path, string new_path);

	static bool menu(string& path, string end, string ignore, bool file_rewiew = false);
};