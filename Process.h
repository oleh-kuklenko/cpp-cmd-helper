#pragma once
#ifndef _CLASS_PROCESS_
#define _CLASS_PROCESS_

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include "Process.h"

using namespace std;

class Process {
	public:
		virtual void execute(vector<string>) const = 0;
};

#endif _CLASS_PROCESS_

