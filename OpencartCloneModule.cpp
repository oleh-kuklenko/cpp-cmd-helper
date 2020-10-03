#include "OpencartCloneModule.h"

#define BOOST_FILESYSTEM_NO_DEPRECATED
#define BOOST_FILESYSTEM_VERSION 3

const vector<string> opencart1_5_directories({
	"admin\\controller\\module",
	"admin\\language\\*\\module",
	"admin\\model\\module",
	"admin\\view\\template\\module",
	"catalog\\controller\\module",
	"catalog\\language\\*\\module",
	"catalog\\model\\module",
	"admin\\view\\theme\\*\\template\\module"
});

void OpencartCloneModule::execute(vector<string> params) const {
	if (isValid(params)) {
		string version = params[1];
		string from_module = params[2];
		string module_name = params[3];

		if (isOpencart1_5(version)) {
			doOpencart1_5(from_module, module_name);
		} else if(isOpencart2_0(version)) {
			doOpencart2_0(from_module, module_name);
		} else if (isOpencart2_3(version)) {
			doOpencart2_3(from_module, module_name);
		} else {
			cout << "  ������� ������ �� ��������������" << endl;
		}
	}
}

void OpencartCloneModule::setPath(string _path) {
	path = _path;
}

bool OpencartCloneModule::isValid(vector<string> params) const {
	if (params.size() < 2) {
		cout << "  �� ������ �������� <opencart_version>" << endl;

		return false;
	}

	if (params.size() < 3) {
		cout << "  �� ������ �������� <from_module>" << endl;

		return false;
	}

	if (params.size() < 4) {
		cout << "  �� ������ �������� <module_name>" << endl;

		return false;
	}

	return true;
}

bool OpencartCloneModule::isOpencart1_5(string version) const {
	return version_compare(version, "1.5") == 0;
}

bool OpencartCloneModule::isOpencart2_0(string version) const {
	return version_compare(version, "2.0") >= 0 && version_compare(version, "2.3") < 0;
}

bool OpencartCloneModule::isOpencart2_3(string version) const {
	return version_compare(version, "2.3") == 0;
}

void OpencartCloneModule::doOpencart1_5(string from_module, string module_name) const {
	vector<boost::filesystem::path> files = searchFiles(from_module);

	cout << "  ��������� ������:" << endl;

	if (files.size() > 0) {
		for (boost::filesystem::path& file : files) {
			cout << "  " << file << endl;
		}
	} else {
		cout << "  �� ������� ����� ������ [ " << from_module << " ]" << endl;
	}
}

void OpencartCloneModule::doOpencart2_0(string from_module, string module_name) const {
	cout << "do v2.0" << endl;
}

void OpencartCloneModule::doOpencart2_3(string from_module, string module_name) const {
	cout << "do v2.3" << endl;
}

vector<boost::filesystem::path> OpencartCloneModule::searchFiles(string from_module) const {
	vector<boost::filesystem::path> files({});

	vector<boost::filesystem::path> pathes{ boost::filesystem::recursive_directory_iterator((boost::filesystem::path)path), {} };

	for (boost::filesystem::path& p : pathes) {
		string _path = boost::filesystem::canonical(p).string();

		for (string search_directory : opencart1_5_directories) {
			string file = search_directory + "\\" + from_module;

			if (search_directory.find("*") != string::npos) {
				std::vector<std::string> chanks;

				boost::split(chanks, search_directory, boost::is_any_of("*"), boost::token_compress_on);

				string left = chanks[0];
				string right = chanks[1] + "\\" + from_module;

				if (_path.find(left) != string::npos && _path.find(right) != string::npos) {
					files.push_back(p);
				}
			} else {
				if (_path.find(file) != string::npos) {
					files.push_back(p);
				}
			}
		}
	}

	return files;
}

int OpencartCloneModule::version_compare(const string& a, const string& b) const {
    // First, split the string.
    std::vector<std::string> va, vb;
    boost::split(va, a, boost::is_any_of("."));
    boost::split(vb, b, boost::is_any_of("."));

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