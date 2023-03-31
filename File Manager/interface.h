#pragma once

namespace FM {
	void start2() {
		FileManager m2;
		while (true) {
			cout << "\n\t\t\t\t\tCurrent Folder: " << m2.getCurrentRoot() << endl;
			int choice = Interface();
			if (choice == 1) {
				string cr;
				cout << "Enter Dir Name: ";
				getline(cin, cr);
				m2.mkdir(cr);
			}
			else if (choice == 2) {
				string rm;
				cout << "Enter Dir Name: ";
				getline(cin, rm);
				m2.rmdir(rm);
			}
			else if (choice == 3) {
				string stander, mover;
				cout << "Enter Dir Name1: ";
				getline(cin, stander);
				cout << "Enter Dir Name2: ";
				getline(cin, mover);
				m2.move(stander, mover);
			}
			else if (choice == 4) {
				string old, new_;
				cout << "Enter Dir Name1: ";
				getline(cin, old);
				cout << "Enter Dir Name2: ";
				getline(cin, new_);
				m2.rename(old, new_);
			}
			else if (choice == 5) {
				string new_;
				cout << "Enter Dir Name: ";
				getline(cin, new_);
				if (new_ == "..") m2.cd_backwards();
				else m2.cd(new_);
			}
			else if (choice == 6) {
				m2.dir_s();
			}
			else if (choice == 7) {
				string op;
				cout << "Enter Dir Name: ";
				getline(cin, op);
				m2.open(op);
			}
			else if (choice == 8) {
				string sorting;
				cout << "Enter Sort Name: ";
				getline(cin, sorting);
				if (sorting == "name") m2.sortF(false);
				else if (sorting == "size") m2.sortF();
			}
			else if (choice == 9) {
				m2.help();
			}
			else if (choice == 10) break;
			cout << "Enter to go back to menu ";
			while (true) {
				if (_kbhit()) {
					_getch();
					system("cls");
					break;
				};
			}
		}
		
	}
}