#include "Help.h"

void Help::execute(vector<string> params) const {
	if (params.size() > 1) {
		if (params[1] == "ocm") {
			cout << "  Syntax: ocm <opencart_version> <from_module> <new_module_name>" << endl;
		} else if (params[1] == "exit") {
			cout << "  Syntax: exit" << endl;
		} else {
			cout << "  Command " << params[1] << " not defined" << endl;
		}
	} else {
		cout << "  Allowed commands: " << endl;
		cout << "    ocm - clone module of opencart" << endl;
		cout << "    exit - exit application" << endl;
	}
}
