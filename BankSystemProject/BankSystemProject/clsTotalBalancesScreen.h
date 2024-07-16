#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsUtil.h"

using namespace std;

class clsTotalBalancesScreen : protected clsScreen {

private:

    static void _PrintClientsRecordBalanceLine(clsBankClient client) {

        cout << setw(50) << left << "";
        cout << " | " << left << setw(20) << client.getAccountNumber();
        cout << " | " << left << setw(30) << client.fullName();
        cout << " | " << left << setw(30) << client.getAccountBalance();
    }

public:

    static void showTotalBalance() {
       
        // print the main header
        system("cls");
        _DrawScreenHeader("\t\tTotal balances screen.");


        // get clients
        vector <clsBankClient> vClients = clsBankClient::getClientsList();

        // print header

        cout << setw(40) << left << "" << "\t\t\tBalances list (" << vClients.size() << ") client(s).\n\n";
        cout << setw(40) << left << "" << "-------------------------------------------------------------------------------------------\n";
        cout << setw(50) << left << "" << " | " << left << setw(20) << "Account number";
        cout << " | " << left << setw(30) << "Client name";
        cout << " | " << left << setw(30) << "Balance" << "\n";
        cout << setw(40) << left << "" << "-------------------------------------------------------------------------------------------\n";

        // get total balance
        double totalBalance = clsBankClient::getTotalBalances();

        // check if there no ckient
        if (vClients.size() == 0)
        {
            cout << setw(40) << left << "" << "\n\n\t\t\t\t\t\tNo clients available in the system!\n";
            cout << setw(40) << left << "" << "\n-------------------------------------------------------------------------------------------\n";
        }

        // print body
        else
        {
            for (clsBankClient C : vClients)
            {
                _PrintClientsRecordBalanceLine(C);
                cout << endl;
            }
            cout << setw(40) << left << "" << "-------------------------------------------------------------------------------------------\n";
        }

        cout << setw(76) << left << "" << "\t\t\t\t\tTotal balances : " << totalBalance << endl;
        cout << setw(76) << left << "" << "\t\t\t\t\t" << clsUtil::numberToText(totalBalance) << endl;

    }

};