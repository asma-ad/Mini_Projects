#pragma once
#include "clsScreen.h"
#include "clsUtil.h"
#include "clsUser.h"


class clsFindUserScree : protected clsScreen  {
private:

    //---print user info---
    static void _PrintUser(clsUser user)
    {
        cout << "\nUser info    :";
        cout << "\n-----------------------------------------";
        cout << "\nFirst name       :" << user.firstName;
        cout << "\nLast name        :" << user.lastName;
        cout << "\nFull name        :" << user.fullName();
        cout << "\nEmail            :" << user.email;
        cout << "\nPhone            :" << user.phone;
        cout << "\nUsername         :" << user.userName;
        cout << "\nPassword         :" << user.password;
        cout << "\nPermissions      :" << user.permissions;
        cout << "\n-----------------------------------------\n";
    }

public:

	static void showFindUsersScreen() {
		
        // print the main header
        _DrawScreenHeader("\t\tFind user screen.");

       // Read username
        string username = "";
        cout << "\nPlease, enter username: ";
        username = clsInputValidate::readString();

        // check if the username exists
        while (!clsUser::isUserExist(username)) {
            cout << "\nUsername not found!\nPlease, enter again the username: ";
            username = clsInputValidate::readString();
        }

        // create an obj of user
        clsUser user = clsUser::Find(username);

        // Search if user exists
        if (!user.isEmpty()) {
            cout << "\n\nUser found :)\n\n";
        }
        else
        {
            cout << "\n\nUser not found :(\n\n";
        }

        // Print user info
        _PrintUser(user);

	}

};