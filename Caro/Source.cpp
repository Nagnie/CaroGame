﻿#include "Data.h"
#include "Control.h"
#include "View.h"

int main() {
	HideCursor(1);
	FixConsoleWindow();
	changeFont(23);
	while (true) {
		MainMenu();
	}
	return 0;
}
