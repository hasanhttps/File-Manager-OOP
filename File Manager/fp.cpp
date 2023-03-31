#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <direct.h>
#include <stdio.h>
#include <conio.h>
#include <string>
#include <io.h>
#include <Windows.h>
#include <ctime>

using namespace std;
#pragma warning(disable : 4996)

#include "personalExceptins.h"
#include "Classes.h"
#include "Interface menu.h"
#include "command.h"
#include "interface.h"


int main() {
	
	if (CommandInterface() == 0) {
		system("cls");
		FM::start();
	}
	else {
		system("cls");
		FM::start2();
	}
	
}




