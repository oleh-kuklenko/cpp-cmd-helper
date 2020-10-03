#include "Cmd.h"

Cmd::Cmd(int argc, char** argv) {
	if (argc > 1) {
		path = argv[1];
	} else {
		path = navigator.getPath();
	}
}

void Cmd::getCommand(string& command) {
	cout << " " << path << "> ";

	getline(cin, command);

	if (cin.fail()) {
		cout << " Error while entering command, please retype." << endl;
		cout << " " << path << "> ";

		command = "";
	}

	while (cin.fail()) {
		getline(cin, command);
	}
}

int Cmd::iterator() {
	string command = "";

	do {
		getCommand(command);
	} while (process(command));

	return 1;
}

bool Cmd::process(string command) {
	bool exit = command == "exit";

	vector<string> params = (Parameter(command)).getParameters();

	if (params.size() > 0) {
		string cmd = params[0];

		if (cmd == "cd") {
			path = navigator.go(params[params.size() > 1 ? 1 : 0]);
		} else if (cmd == "help") {
			Help process = Help();

			process.execute(params);
		} else if (cmd == "ocm") {
			OpencartCloneModule process = OpencartCloneModule();

			process.setPath(path);
			process.execute(params);
		} else {
			if (!exit) {
				cout << " Command " << command << " not defined" << endl;
			}
		}

		if (!exit) {
			cout << endl;
		}
	}
	
	return !exit;
}
