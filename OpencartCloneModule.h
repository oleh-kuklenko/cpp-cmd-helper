#pragma once
#ifndef _CLASS_PROCESS_OPENCART_CLONE_MODULE_
#define _CLASS_PROCESS_OPENCART_CLONE_MODULE_

#include "Process.h"

#include <boost/algorithm/string.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/convenience.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/locale.hpp>
#include <fstream>

using namespace boost;

class OpencartCloneModule : public Process {
	public:
		void execute(vector<string>) const override;
		void setPath(string);
		bool isValid(vector<string>) const;

		bool isOpencartVersion(string, string) const;
		void doOpencart(string, string, string) const;
		bool isPhpFile(filesystem::path) const;
		bool isTplFile(filesystem::path) const;
		string readFile(string) const;
		void writeToFile(filesystem::path, string) const;
		void replaceModuleNames(vector<filesystem::path>, string, string) const;
		void replaceModuleNameController(string&, string, string) const;
		void replaceModuleNameLoad(string&, string, string) const;
		void replaceModuleNameProperty(string&, string, string) const;
		void replaceModuleName(string&, string, string) const;

		vector<filesystem::path> searchFiles(vector<string>, string) const;
		vector<filesystem::path> copyFiles(vector<filesystem::path>, string, string) const;
		filesystem::path replaceModuleName(filesystem::path, string, string) const;

		vector<string> splitStr(string, string) const;
		vector<string> eachFirstToUpper(vector<string>) const;

		int version_compare(const string&, const string&) const;

	private:
		string path;
};

#endif _CLASS_PROCESS_OPENCART_CLONE_MODULE_