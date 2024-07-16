#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"

using namespace std;

class clsListUserScreen : protected clsScreen {

private:

	static void _PrintUsersRecord(clsUser user) {

		cout << setw(15) << left << ""
			<< " | " << left << setw(15) << user.userName;
		cout << " | " << left << setw(20) << user.fullName();
		cout << " | " << left << setw(12) << user.phone;
		cout << " | " << left << setw(20) << user.email;
		cout << " | " << left << setw(10) << user.password;
		cout << " | " << left << setw(12) << user.permissions;
	}

public:

	static void showListUsers() {
		
		// get users
		vector <clsUser> vUsers = clsUser::getUsersList();

		// Print the main header
		string title = "\t\tUsers list screen.";
		string sub = "\t  (" + to_string(vUsers.size()) + ") user(s).";
		_DrawScreenHeader(title, sub);

		// print header        
		cout << setw(15) << left << "" << "-------------------------------------------------------------------------------------------------------\n\n";

		cout << setw(15) << left << ""
			<< " | " << left << setw(15) << "Username";
		cout << " | " << left << setw(20) << "Full name";
		cout << " | " << left << setw(12) << "Phone";
		cout << " | " << left << setw(20) << "Email";
		cout << " | " << left << setw(10) << "Password";
		cout << " | " << left << setw(12) << "Permissions";
		cout << "\n\n";
		cout << setw(15) << left << "" << "-------------------------------------------------------------------------------------------------------\n\n";

		// check if there no user
		if (vUsers.size() == 0)
		{
			cout << "\n\n\t\t\t\t\t\tNo users available in the system!\n";
			cout << "\n----------------------------------------------------------------------------------------------------------------------------\n";

		}
		
		// print body
		else
		{
			for (clsUser U : vUsers)
			{
				_PrintUsersRecord(U);
				cout << endl;
			}
			cout << setw(15) << left << "" << "-------------------------------------------------------------------------------------------------------\n\n";

		}

	}

};