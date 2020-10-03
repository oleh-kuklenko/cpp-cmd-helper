#include "Help.h"

void Help::execute(vector<string> params) const {
	if (params.size() > 1) {
		if (params[1] == "ocm") {
			cout << "  Синтаксис: ocm <opencart_version> <from_module> <new_module_name>" << endl;
		} else if (params[1] == "exit") {
			cout << "  Синтаксис: exit" << endl;
		} else {
			cout << "  Команда " << params[1] << " не определена" << endl;
		}
	} else {
		cout << "  Доступные команды: " << endl;
		cout << "    ocm - клонирование модулей Opencart" << endl;
		cout << "    exit - выход из приложения" << endl;
	}
}
