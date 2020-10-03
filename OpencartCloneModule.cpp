#include "OpencartCloneModule.h"

#define BOOST_FILESYSTEM_NO_DEPRECATED
#define BOOST_FILESYSTEM_VERSION 3

const string v1_5 = "1.5";
const string v2_0 = "2.0";
const string v2_3 = "2.3";

const vector<string> v1_5_directories({
	"admin\\controller\\module",
	"admin\\language\\*\\module",
	"admin\\model\\module",
	"admin\\view\\template\\module",
	"catalog\\controller\\module",
	"catalog\\language\\*\\module",
	"catalog\\model\\module",
	"admin\\view\\theme\\*\\template\\module"
});

const vector<string> v2_0_directories({
	"admin\\controller\\module",
	"admin\\language\\*\\module",
	"admin\\model\\module",
	"admin\\view\\template\\module",
	"catalog\\controller\\module",
	"catalog\\language\\*\\module",
	"catalog\\model\\module",
	"admin\\view\\theme\\*\\template\\module"
});

const vector<string> v2_3_directories({
	"admin\\controller\\extension\\module",
	"admin\\language\\*\\extension\\module",
	"admin\\model\\extension\\module",
	"admin\\view\\template\\extension\\module",
	"catalog\\controller\\extension\\module",
	"catalog\\language\\*\\extension\\module",
	"catalog\\model\\extension\\module",
	"admin\\view\\theme\\*\\template\\extension\\module"
});

void OpencartCloneModule::execute(vector<string> params) const {
	if (isValid(params)) {
		string version = params[1];
		string from_module = params[2];
		string module_name = params[3];

		if (isOpencartVersion(version, v1_5)) {
			doOpencart(v1_5, from_module, module_name);
		} else if(isOpencartVersion(version, v2_0)) {
			doOpencart(v2_0, from_module, module_name);
		} else if (isOpencartVersion(version, v2_3)) {
			doOpencart(v2_3, from_module, module_name);
		} else {
			cout << "  Текущая версия не поддерживается" << endl;
		}
	}
}

void OpencartCloneModule::setPath(string _path) {
	path = _path;
}

bool OpencartCloneModule::isValid(vector<string> params) const {
	if (params.size() < 2) {
		cout << "  Не указан параметр <opencart_version>" << endl;

		return false;
	}

	if (params.size() < 3) {
		cout << "  Не указан параметр <from_module>" << endl;

		return false;
	}

	if (params.size() < 4) {
		cout << "  Не указан параметр <module_name>" << endl;

		return false;
	}

	return true;
}

bool OpencartCloneModule::isOpencartVersion(string version, string compare) const {
	return version_compare(version, compare) == 0;
}

void OpencartCloneModule::doOpencart(string version, string from_module, string module_name) const {
	vector<filesystem::path> files({});

	cout << "  Opencart v" << version << endl << endl;

	if (version == v1_5) {
		files = searchFiles(v1_5_directories, from_module);
	}

	if (version == v2_0) {
		files = searchFiles(v2_0_directories, from_module);
	}

	if (version == v2_3) {
		files = searchFiles(v2_3_directories, from_module);
	}

	if (files.size() > 0) {
		vector<filesystem::path> module_files = copyFiles(files, from_module, module_name);

		if (module_files.size() > 0) {
			replaceModuleNames(module_files, from_module, module_name);
		}
	}
}

bool OpencartCloneModule::isPhpFile(filesystem::path file) const {
	string _file = filesystem::canonical(file).string();

	return _file.find(".php") != string::npos;
}

bool OpencartCloneModule::isTplFile(filesystem::path file) const {
	string _file = filesystem::canonical(file).string();

	return _file.find(".tpl") != string::npos;
}

string OpencartCloneModule::readFile(string file) const {
	string content("");

	ifstream in(file);

	if (in.is_open()) {
		string line = "";

		while (getline(in, line)) {
			content += line + "\n";
		}

		in.close();
	} else {
		cout << "  Не удалось открыть файл [ " << file << " ]" << endl;
	}

	return content;
}

void OpencartCloneModule::writeToFile(filesystem::path file, string content) const {
	ofstream out(filesystem::canonical(file).string());
		
	if (out.is_open()) {
		out << content;
		
		if(out.fail()) {
			cout << "  Произошла ошибка при записи в файл [ " << file << " ] " << endl;
		}

		out.close();
	} else {
		cout << "  Не удалось открыть файл [ " << file << " ] " << endl;
	}
}

void OpencartCloneModule::replaceModuleNames(vector<filesystem::path> files, string from_module, string module_name) const {
	cout << endl << "  Результат:" << endl;

	for (filesystem::path& file : files) {
		bool isReady = true;
		
		string file_content = readFile(filesystem::canonical(file).string());

		if (isPhpFile(file)) {
			replaceModuleNameController(file_content, from_module, module_name);
			replaceModuleName(file_content, from_module, module_name);
		}

		if (isTplFile(file)) {
			replaceModuleName(file_content, from_module, module_name);
		}

		writeToFile(file, file_content);

		cout << "  Файл [ " << file << " ] - готов" << endl;
	}
}

void OpencartCloneModule::replaceModuleNameController(string& content, string from_module, string module_name) const {
	boost::locale::generator gen;
	std::locale loc = gen("");
	std::locale::global(loc);

	vector<string> chankFrom = eachFirstToUpper(splitStr(from_module, "_"));
	vector<string> chankTo = eachFirstToUpper(splitStr(module_name, "_"));

	string find = "Module" + algorithm::join(chankFrom, "");
	string replace = "Module" + algorithm::join(chankTo, "");

	replace_all(content, find, replace);
}

void OpencartCloneModule::replaceModuleNameLoad(string& content, string from_module, string module_name) const {
	boost::locale::generator gen;
	std::locale loc = gen("");
	std::locale::global(loc);

	replace_all(content, "/" + from_module, "/" + module_name);
}

void OpencartCloneModule::replaceModuleNameProperty(string& content, string from_module, string module_name) const {
	boost::locale::generator gen;
	std::locale loc = gen("");
	std::locale::global(loc);

	replace_all(content, "_" + from_module, "_" + module_name);
}

void OpencartCloneModule::replaceModuleName(string& content, string from_module, string module_name) const {
	boost::locale::generator gen;
	std::locale loc = gen("");
	std::locale::global(loc);

	replace_all(content, from_module, module_name);
}

vector<filesystem::path> OpencartCloneModule::searchFiles(vector<string>version_directories, string from_module) const {
	vector<filesystem::path> files({});

	try {
		vector<filesystem::path> pathes{ filesystem::recursive_directory_iterator((filesystem::path)path), {} };

		for (filesystem::path& p : pathes) {
			string _path = filesystem::canonical(p).string();

			for (string search_directory : version_directories) {
				string file = search_directory + "\\" + from_module;

				if (search_directory.find("*") != string::npos) {
					vector<string> chanks = splitStr(search_directory, "*");

					if (_path.find(chanks[0]) != string::npos && _path.find(chanks[1] + "\\" + from_module) != string::npos) {
						files.push_back(p);
					}
				} else {
					if (_path.find(file) != string::npos) {
						files.push_back(p);
					}
				}
			}
		}
	} catch (const filesystem::filesystem_error& e) {
		cerr << "  " << e.what() << endl;
	}

	cout << "  Результат поиска:" << endl;

	if (files.size() > 0) {
		for (filesystem::path& file : files) {
			cout << "  " << file << endl;
		}
	} else {
		cout << "  Не найдены файлы модуля [ " << from_module << " ]" << endl;
	}

	return files;
}

vector<filesystem::path> OpencartCloneModule::copyFiles(vector<filesystem::path> files, string from_module, string module_name) const {
	vector<filesystem::path> copied({});

	try {
		for (filesystem::path& file : files) {
			filesystem::path new_file = replaceModuleName(file, from_module, module_name);

			filesystem::copy_file(file, new_file, filesystem::copy_option::overwrite_if_exists);

			copied.push_back(new_file);
		}
	} catch (const filesystem::filesystem_error& e) {
		cerr << "  " << e.what() << endl;
	}

	cout << endl << "  Скопированные файлы:" << endl;

	if (copied.size() > 0) {
		for (filesystem::path& copy : copied) {
			cout << "  " << copy << endl;
		}
	} else {
		cout << "  Не удалось скопировать файлы модуля [ " << from_module << " ]" << endl;
	}

	return copied;
}

filesystem::path OpencartCloneModule::replaceModuleName(filesystem::path file, string from_module, string module_name) const {
	string sFile = filesystem::canonical(file).string();
		   sFile.replace(sFile.find(from_module), from_module.length(), module_name);

	return filesystem::path(sFile);
}

vector<string> OpencartCloneModule::splitStr(string str, string separator) const {
	std::vector<std::string> chanks;

	split(chanks, str, is_any_of(separator), token_compress_on);

	return chanks;
}

vector<string> OpencartCloneModule::eachFirstToUpper(vector<string> strings) const {
	vector<string> results({});

	for (string str : strings) {
		string tmp = str;
			   tmp[0] = toupper(tmp[0]);
		
		transform(tmp.begin() + 1, tmp.end(), tmp.begin() + 1, tolower);

		results.push_back(tmp);
	}

	return results;
}

int OpencartCloneModule::version_compare(const string& a, const string& b) const {
    // First, split the string.
    std::vector<std::string> va, vb;
    split(va, a, is_any_of("."));
    split(vb, b, is_any_of("."));

    // Compare the numbers step by step, but only as deep as the version
    // with the least elements allows.
    const int depth = std::min(va.size(), vb.size());
    
	int ia, ib;

    for (int i = 0; i < depth; ++i) {
        ia = atoi(va[i].c_str());
        ib = atoi(vb[i].c_str());
	
		if (ia != ib) {
            break;
		}
    }

    // Return the required number.
    if (ia > ib) {
        return 1;
    } else if (ia < ib) {
        return -1;
    } else {
        // In case of equal versions, assumes that the version
        // with the most elements is the highest version.
		if (va.size() > vb.size()) {
            return 1;
		} else if (va.size() < vb.size()) {
            return -1;
		}
    }

    // Everything is equal, return 0.
    return 0;
}