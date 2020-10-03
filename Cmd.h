#pragma once
#ifndef _CLASS_CMD_
#define _CLASS_CMD_

#include <iostream>
#include <string>
#include <conio.h>

using namespace std;

#include "Parameter.h"
#include "Navigator.h"

#include "Help.h"
#include "OpencartCloneModule.h"

class Cmd {
	public:
		string path = "";

	public:
		Cmd(int, char**);
		int iterator();
		void process(string);

	private:
		Navigator navigator = Navigator();
};

#endif _CLASS_CMD_