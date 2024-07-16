#pragma once
#include <iomanip>
#include "clsScreen.h"
#include "clsBankClient.h"

class clsClientListScreen : protected clsScreen {
private:

    static void _PrintClientsRecord(clsBankClient client) {

        cout << setw(15) << left << ""
             << " | " << left << setw(15) << client.getAccountNumber();
        cout << " | " << left << setw(20) << client.fullName();
        cout << " | " << left << setw(12) << client.phone;
        cout << " | " << left << setw(20) << client.email;
        cout << " | " << left << setw(10) << client.pinCode;
        cout << " | " << left << setw(12) << client.accountBalance;
    }

public:

    static void showClientsList() {

        // Check permissions 
        if (!checkAccessRights(clsUser::enPermissions::pListClient))
        {
            // if the user hasn't access, exit!
            return;
        }

        // get clients
        vector <clsBankClient> vClients = clsBankClient::getClientsList();

        // print main header
        string title = "\t\tClient list screen.";
        string sub = "\t  (" + to_string(vClients.size()) + ") Client(s).";
        _DrawScreenHeader(title, sub);

        // print header        
        cout << setw(15) << left << "" << "-------------------------------------------------------------------------------------------------------\n\n";

        cout << setw(15) << left << ""
             << " | " << left << setw(15) << "Account number";
        cout << " | " << left << setw(20) << "Client name";
        cout << " | " << left << setw(12) << "Phone";
        cout << " | " << left << setw(20) << "Email";
        cout << " | " << left << setw(10) << "PIN code";
        cout << " | " << left << setw(12) << "Balance";
        cout << "\n\n";
        cout << setw(15) << left << "" << "-------------------------------------------------------------------------------------------------------\n\n";

        // check if there no ckient
        if (vClients.size() == 0)
        {
            cout << "\n\n\t\t\t\t\t\tNo clients available in the system!\n";
            cout << "\n----------------------------------------------------------------------------------------------------------------------------\n";

        }
        // print body
        else
        {
            for (clsBankClient C : vClients)
            {
                _PrintClientsRecord(C);
                cout << endl;
            }
            cout << setw(15) << left << "" << "-------------------------------------------------------------------------------------------------------\n\n";

        }
    }

};