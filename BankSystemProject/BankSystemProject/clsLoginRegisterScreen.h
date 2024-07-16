#pragma once
#include <iomanip>
#include "clsScreen.h"
#include "clsUser.h"

class clsLoginRegisterScreen : protected clsScreen {
private:

    static void _PrintLoginRecordLine(clsUser::stLoginRegisterRecord reco) {

        cout << setw(15) << left << ""
            << " | " << left << setw(35) << reco.dateTime;
        cout << " | " << left << setw(20) << reco.username;
        cout << " | " << left << setw(20) << reco.password;
        cout << " | " << left << setw(10) << reco.permission;
    }

public:

    static void showLoginRegisterScreen() {

        // Check permissions 
            if (!checkAccessRights(clsUser::enPermissions::pLoginRegister))
        {
            // if the user hasn't access, exit!
            return;
        }

        // get login register list
        vector <clsUser::stLoginRegisterRecord> vLoginRegisterRec = clsUser::getLoginRegisterList();

        // print main header
        string title = "\t\tLogin register list screen.";
        string sub = "\t  (" + to_string(vLoginRegisterRec.size()) + ") record(s).";
        _DrawScreenHeader(title, sub);

        // print header        
        cout << setw(15) << left << "" << "-------------------------------------------------------------------------------------------------------\n\n";
        cout << setw(15) << left << ""
            << " | " << left << setw(35) << "Date/Time";
        cout << " | " << left << setw(20) << "Username";
        cout << " | " << left << setw(20) << "Password";
        cout << " | " << left << setw(10) << "Permissios";
        cout << "\n\n";
        cout << setw(15) << left << "" << "-------------------------------------------------------------------------------------------------------\n\n";

        // check if there no ckient
        if (vLoginRegisterRec.size() == 0)
        {
            cout << "\n\n\t\t\t\t\t\tNo Logings available in the system!\n";
            cout << "\n----------------------------------------------------------------------------------------------------------------------------\n";

        }
        
        // print body
        else
        {
            for (clsUser::stLoginRegisterRecord record : vLoginRegisterRec)
            {
                _PrintLoginRecordLine(record);
                cout << endl;
            }
            cout << setw(15) << left << "" << "-------------------------------------------------------------------------------------------------------\n\n";

        }
    }

};