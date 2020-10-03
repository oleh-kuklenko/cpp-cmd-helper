#include "Cmd.h"

Cmd::Cmd(int argc, char** argv) {
	if (argc == 2) {
		path = (const char*)argv;
	} else {
		path = navigator.getPath();
	}
}

int Cmd::iterator() {
	string command = "";

	do {
		cout << " " << path << "> ";

		getline(cin, command);

		if (cin.fail()) {
			cout << " Произошла ошибка при вводе комманды. Повторите ввод." << endl;
			cout << path << "> ";

			command = "";
		}

		while (cin.fail()) {
			getline(cin, command);
		}

		process(command);
	} while (command != "exit");

	return 1;
}

void Cmd::process(string command) {
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

			process.execute(params);
		} else {
			cout << " Команда " << command << " не определена" << endl;
		}

		cout << endl;
	}
}
