#include "OpencartCloneModule.h"

#define BOOST_FILESYSTEM_NO_DEPRECATED
#define BOOST_FILESYSTEM_VERSION 3

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
	vector<string> directories;

	vector<boost::filesystem::path> pathes{ boost::filesystem::recursive_directory_iterator(path), {} };
	
	for (auto& p : pathes) {
		cout << p << endl;
	}
}

void OpencartCloneModule::doOpencart2_0(string from_module, string module_name) const {
	cout << "do v2.0" << endl;
}

void OpencartCloneModule::doOpencart2_3(string from_module, string module_name) const {
	cout << "do v2.3" << endl;
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