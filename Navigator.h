#pragma once
#ifndef _CLASS_NAVIGATOR_
#define _CLASS_NAVIGATOR_

#include <iostream>
#include <Windows.h>
#include <string>
#include <clocale>
#include <locale>
#include <vector>

#include <direct.h>

#define GetCurrentDir _getcwd
#define GoToDir _chdir

using namespace std;

class Navigator {
	public:
		string getPath();
		string go(string);
};

#endif _CLASS_NAVIGATOR_