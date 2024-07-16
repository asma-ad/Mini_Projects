#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsMainScreen.h"
#include "Global.h"

using namespace std;

class clsLoginScreen : protected clsScreen {

private:

	static bool _Login() {
		
		string username, password;
		bool loginFailed = false;
		int fialedCount = 3;

		// Login  (Lock the System after 3 failed Logins)
		do {

			if (loginFailed)
			{
				fialedCount--;

				cout << "\nInvalid username/password ...\n";
				cout << "\nYou have " << fialedCount << " trial(s) to login\n\n";
			}

			// Lock the System after 3 failed Logins
			if (fialedCount == 0)
			{
				cout << "\nYou are locked after 3 failed trials\n\n";
				return false;
			}

			cout << "\nEnter username: ";
			cin >> username;

			cout << "\nEnter password: ";
			cin >> password;

			currentUser = clsUser::Find(username, password);

			loginFailed = currentUser.isEmpty();

		} while (loginFailed);

		// Register logins in a log file
		currentUser.registerLoginInLogFile();

		// show menu screen
		clsMainScrenn::showMainMenu();
		return true;
	}

public:

	static bool showLoginScreen() {
	
		system("cls");
		_DrawScreenHeader("\t\tLogin screen.");
		return _Login();
		
	}

};