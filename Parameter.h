#pragma once
#ifndef _CLASS_PARAMETER_
#define _CLASS_PARAMETER_

#include <string>
#include <vector>
#include <sstream>
#include <utility>

using namespace std;

class Parameter {
	public:
		Parameter(string);
		vector<string> getParameters();

	private:
		vector<string> parameters;
		vector<string> explode(string const&, char);
};

#endif _CLASS_PARAMETER_
