void changePass(_Student* Node) {
	string old, new;
	cout << "Please input password: " << endl;
	getline(cin, old);
	while (true) {
		if (old != Node->data.student_Account.password) {
			cout << "Incorrect password... Please try again..." << endl;
			getline(cin, old);
		}
		else {
			cout << "Please input new password: ";
			get(cin, new);
			int check = 1; int check2 = 1;
			for (int i = 0; i < new.length(), i++) {
				if (int(s[i]) > 64 && int(s[i]) < 91)
					check *= 0;
				else check *= 1;
				if (int(s[i]) > 47 && int(s[i]) < 58)
					check2 *= 0;
				else check2 *= 1;
			}
			while (true) {
				if (check == 1 || check2 == 1 || s[i].length < 8) {
					cout << "Password must include capital character(s) and number(s)..." << endl << "Please try another password..." << endl;
					get(cin, new);
				}
				else {
					string confirm;
					cout << "Please input new password again to confirm..." << endl;
					while (true) {
						if (confirm == new) {
							Node->data.student_Account.password = new;
							break;
						}
						else {
							cout << "Confirm not match... One more time please! ";
							cin >> confirm;
						}
					}
					break;
				}

			}
			break;
		}
	}
}