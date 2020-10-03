#include <iostream>
#include <conio.h>
#include <string>

#include "Cmd.h"

using namespace std;

int main(int argc, char ** argv) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	return (Cmd(argc, argv)).iterator();
}