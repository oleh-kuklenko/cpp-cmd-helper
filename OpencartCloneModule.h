#pragma once
#ifndef _CLASS_PROCESS_OPENCART_CLONE_MODULE_
#define _CLASS_PROCESS_OPENCART_CLONE_MODULE_

#include "Process.h"

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/convenience.hpp>

class OpencartCloneModule : public Process {
	public:
		void execute(vector<string>) const override;
		void setPath(string);
		bool isValid(vector<string>) const;
		bool isOpencart1_5(string) const;
		bool isOpencart2_0(string) const;
		bool isOpencart2_3(string) const;

		void doOpencart1_5(string, string) const;
		void doOpencart2_0(string, string) const;
		void doOpencart2_3(string, string) const;

		int version_compare(const string&, const string&) const;

	private:
		string path;
};

#endif _CLASS_PROCESS_OPENCART_CLONE_MODULE_