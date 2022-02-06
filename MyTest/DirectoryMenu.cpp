#include "DirectoryMenu.h"

int DirectoryMenu::get_index_of_directory(string path, list<string> directories) {
	auto it = directories.begin();
	for (size_t i = 0, size = directories.size(); i < size; i++, it++) {
		it->erase(it->begin(), it->begin() + path.length());
		it->erase(remove(it->begin(), it->end(), '\\'), it->end());
		auto pos = it->find(SettingsConst::FILE_EXTENSION);
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


string DirectoryMenu::path_to_title(string path, string extension) {
	int index = -1;
	for (size_t i = 0, size = path.size(); i < size; i++) 
		if (path[i] == '\\')
			index = i;

	return path.substr(index + 1, path.size() - index - 1 - extension.size());
}

string DirectoryMenu::remove_end_of_path(string path) {
	int index = -1;
	for (size_t i = 0, size = path.size(); i < size; i++) 
		if (path[i] == '\\')
			index = i;
	if (index != -1)
		path.erase(path.begin() + index, path.end());
	return path;
}

string DirectoryMenu::get_end_of_path(string path, int number) {
	for (int i = 1; i < number; i++)
		path = remove_end_of_path(path);

	int index = -1;
	for (size_t i = 0, size = path.size(); i < size; i++) 
		if (path[i] == '\\')
			index = i;

	if (index != -1) 
		path.erase(path.begin(), path.begin() + index + 1);

		return path;

}

bool DirectoryMenu::delete_path(string path) {
	fs::remove_all(path);

	bool res = true;
	auto check = get_all_from_directories(remove_end_of_path(path));
	for_each(check.begin(), check.end(), [&res, path](const string& tmp_path) {if (path == tmp_path)res = false; });
	return res;
}

list<string> DirectoryMenu::get_all_from_directories(string path) {
	list<string> directories;
	if (_mkdir(path.c_str()) == 0) 
		_rmdir(path.c_str());
	
	else {

		for (const auto& entry : fs::directory_iterator(path)) {
			string directory = entry.path().string();

			directories.push_back(directory);

		}
	}
	return directories;
}

list<string> DirectoryMenu::get_files(string path) {
	list<string> directories = get_all_from_directories(path);
	directories.remove_if([](string& str) {
		return (str.find(SettingsConst::FILE_EXTENSION) == string::npos);
		});
	return directories;
}

list<string> DirectoryMenu::get_directories(string path) {
	list<string> directories = get_all_from_directories(path);
	directories.remove_if([](string& str) {
		return !(str.find(SettingsConst::FILE_EXTENSION) == string::npos);
		});
	return directories;
}

int DirectoryMenu::change_directory_name(string old_path, string new_path) {
	return rename(old_path.c_str(), new_path.c_str());
}

bool DirectoryMenu::menu(string& path, string end, string ignore, bool file_rewiew) {
	string basic_path = path;
	list<string> directories;
	list<string>::iterator it;
	int index;
	bool is_stop = false;

	system("cls");
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
			system("pause");
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
		system("cls");
	} while (true);

	return true;

}
