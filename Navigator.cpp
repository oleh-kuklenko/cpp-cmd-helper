#include "Navigator.h"

string Navigator::getPath() {
	char buff[FILENAME_MAX];

	GetCurrentDir(buff, FILENAME_MAX);

	string current_working_dir(buff);

	return current_working_dir;
}

string Navigator::go(string path) {
	GoToDir(path.c_str());

	return getPath();
}
