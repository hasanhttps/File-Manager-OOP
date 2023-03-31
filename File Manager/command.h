#pragma once


namespace FM {
	void start() {
		FileManager m1;
		cout << "Microsoft Windows [Version 10.0.19043.1645]\n(c)Microsoft Corporation.All rights reserved.\n";
		while (true) {
			string command;
			cout << "\n" << m1.getCurrentRoot() << ">";
			getline(cin, command);
			if (command.substr(0, command.find(" ")) == "mkdir") {
				m1.mkdir(command.substr(command.find(" ") + 1));
			}
			else if (command.substr(0, command.find(" ")) == "rmdir") {
				m1.rmdir(command.substr(command.find(" ") + 1));
			}
			else if (command.substr(0, command.find(" ")) == "cd") {
				m1.cd(command.substr(command.find(" ") + 1));
			}
			else if (command == "cd..") {
				m1.cd_backwards();
			}
			else if (command == "dir") {
				m1.dir_s();
			}
			else if (command.substr(0, command.find(" ")) == "open") {
				m1.open(command.substr(command.find(" ") + 1));
			}
			else if (command.substr(0, command.find(" ")) == "type_nul") {
				m1.type_nul(command.substr(command.find(" ") + 1));
			}
			else if (command.substr(0, command.find(" ")) == "del/f") {
				m1.rmdir(command.substr(command.find(" ") + 1));
			}
			else if (command.substr(0, command.find(" ")) == "move") {
				m1.move(command.substr(command.find(" ") + 1, command.rfind(" ") - command.find(" ") - 1), command.substr(command.rfind(" ") + 1));
			}
			else if (command.substr(0, command.find(" ")) == "rename") {
				m1.rename(command.substr(command.find(" ") + 1, command.rfind(" ") - command.find(" ") - 1), command.substr(command.rfind(" ") + 1));
			}
			else if (command == "datetime") {
				time_t now = time(0);
				char* date_time = ctime(&now);
				cout << "The current date and time is: " << date_time;
			}
			else if (command.substr(0, command.find(" ")) == "type") {
				m1.type(command.substr(command.find(" ") + 1));
			}
			else if (command == "shutdown") {
				system("C:\\windows\\system32\\shutdown /s /t 5 \n\n");
			}
			else if (command.substr(0, command.find(" ")) == "compare") {
				m1.compare(command.substr(command.find(" ") + 1, command.rfind(" ") - command.find(" ") - 1), command.substr(command.rfind(" ") + 1));
			}
			else if (command.substr(0, command.find(" ")) == "write") {
				m1.write(command.substr(command.find(" ") + 1));
			}
			else if (command.substr(0, command.find(" ")) == "append") {
				m1.append(command.substr(command.find(" ") + 1));
			}
			else if (command == "sort/s") {
				m1.sortF();
			}
			else if (command == "sort/n") {
				m1.sortF(false);
			}
			else if (command == "cls") system("cls");
			else if (command.substr(0, command.find(" ")) == "color") system(command.c_str());
			else if (command == "exit") exit(0);
			else if (command == "help") m1.help();
			else cout << "This is not an operatable command.Type 'help' and learn all commands" << endl;
		}
	}
}






