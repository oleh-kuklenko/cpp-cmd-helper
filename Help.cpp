#include "Help.h"

void Help::execute(vector<string> params) const {
	if (params.size() > 1) {
		if (params[1] == "ocm") {
			cout << "  ���������: ocm <opencart_version> <from_module> <new_module_name>" << endl;
		} else if (params[1] == "exit") {
			cout << "  ���������: exit" << endl;
		} else {
			cout << "  ������� " << params[1] << " �� ����������" << endl;
		}
	} else {
		cout << "  ��������� �������: " << endl;
		cout << "    ocm - ������������ ������� Opencart" << endl;
		cout << "    exit - ����� �� ����������" << endl;
	}
}
