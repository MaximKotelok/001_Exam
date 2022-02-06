#pragma once
#include <list>
#include <iostream>
#include <filesystem>

#include <direct.h>


namespace fs = std::filesystem;
using namespace std;

class DirectoryMenu {
	static int get_index_of_directory(string path, list<string> directories) {
		auto it = directories.begin();
		for (int i = 0; i < directories.size(); i++, it++) {
			it->erase(it->begin(), it->begin() + path.length());
			it->erase(remove(it->begin(), it->end(), '\\'), it->end());
			auto pos = it->find(".txt");
			if (pos != std::string::npos)
				it->erase(it->find(".txt"), 4);
			cout << i + 1 << ". " << *it << "\n";
		}
		int choice;
		do {
			(cin >> choice).get();

		} while (choice < 0 || choice > directories.size());
		return choice - 1;
	}


public:

	static string path_to_title(string path, string extension) {
		int index = -1;
		for (int i = 0; i < path.size(); i++)
			if (path[i] == '\\')
				index = i;

		return path.substr(index + 1, path.size() - index - 1 - extension.size());
	}

	static string remove_end_of_path(string path) {
		int index = -1;
		for (int i = 0; i < path.size(); i++)
			if (path[i] == '\\')
				index = i;
		if (index != -1)
			path.erase(path.begin() + index, path.end());
		return path;
	}

	static string get_end_of_path(string path, int number) {
		for (int i = 1; i < number; i++)
			path = remove_end_of_path(path);
		int index = -1;
		for (int i = 0; i < path.size(); i++)
			if (path[i] == '\\')
				index = i;
		if (index != -1) {

			path.erase(path.begin(), path.begin() + index+1);
		
			return path;
		}
		
	}

	static bool delete_path(string path) {
		fs::remove_all(path);
		
		bool res = true;
		auto check = get_all_from_directories(remove_end_of_path(path));
		for_each(check.begin(), check.end(), [&res, path](const string& tmp_path) {if (path == tmp_path)res = false; });
		return res;
	}

	static list<string> get_all_from_directories(string path) {
		list<string> directories;
		if (_mkdir(path.c_str()) == 0) {
			_rmdir(path.c_str());
		}
		else {

			for (const auto& entry : fs::directory_iterator(path)) {
				string directory = entry.path().string();

				directories.push_back(directory);

			}
		}
		return directories;
	}

	static list<string>get_files(string path) {
		list<string> directories = get_all_from_directories(path);
		directories.remove_if([](string& str) {
			return (str.find(".txt") == string::npos);
			});
		return directories;
	}

	static list<string> get_directories(string path) {
		list<string> directories = get_all_from_directories(path);
		directories.remove_if([](string& str) {
			return !(str.find(".txt") == string::npos);
			});
		return directories;
	}

	static int change_directory_name(string old_path, string new_path) {
		return rename(old_path.c_str(), new_path.c_str());
	}

	static bool menu(string& path, string end, string ignore, bool file_rewiew = false) {
		string basic_path = path;
		list<string> directories;
		list<string>::iterator it;
		int index;
		bool is_stop = false;

		do {
			if (!is_stop) {

				directories = DirectoryMenu::get_directories(path);
				directories.remove(path + "\\" + ignore);
			}
			else
				break;
			auto found = find(directories.begin(), directories.end(), path + "\\" + end);


			if (found != directories.end())
				break;

			if (file_rewiew && directories.size() == 0) {
					directories = DirectoryMenu::get_files(path);
					is_stop = true;
			}

			
			if (directories.size() != 0) {

				cout << "0. Назад\n";
				index = get_index_of_directory(path, directories);
			}
			else {
				index = -1;
				cout << "Директорія порожня\n";
			}

			if (index != -1) {
				it = directories.begin();
				advance(it, index);
				path = *it;
			}

			else {
				if (path == basic_path)
					return false;

				path = remove_end_of_path(path);
				is_stop = false;
			}
		} while (true);

		return true;

	}
};