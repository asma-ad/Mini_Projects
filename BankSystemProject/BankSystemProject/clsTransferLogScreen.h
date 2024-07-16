#pragma once
#include <iomanip>
#include "clsScreen.h"
#include "clsBankClient.h"

using namespace std;

class clsTransferLogScreen : protected clsScreen {

private:

    static void _PrintTransferRecordLine(clsBankClient::stTrnsferLogRecord reco) {

        cout << setw(35) << left << ""
            << " | " << left << setw(25) << reco.dateTime;
        cout << " | " << left << setw(10) << reco.SourceClient;
        cout << " | " << left << setw(10) << reco.DestanitionClient;
        cout << " | " << left << setw(10) << reco.amount;
        cout << " | " << left << setw(10) << reco.srcBalance;
        cout << " | " << left << setw(10) << reco.DestBalance;
        cout << " | " << left << setw(10) << reco.username;
    }

public:

    static void showTransferRegisterScreen() {

        // get transfer register list
        vector <clsBankClient::stTrnsferLogRecord> vTransferLogRec = clsBankClient::getTransfersLogList();

        // print main header
        string title = "\t\tTransfer register list screen.";
        string sub = "\t  (" + to_string(vTransferLogRec.size()) + ") record(s).";
        _DrawScreenHeader(title, sub);

        // print header
        cout << setw(35) << left << "" << "-------------------------------------------------------------------------------------------------------\n\n";
        cout << setw(35) << left << ""
            << " | " << left << setw(25) << "Date/Time";
        cout << " | " << left << setw(10) << "S. Account";
        cout << " | " << left << setw(10) << "D. Account";
        cout << " | " << left << setw(10) << "Amount";
        cout << " | " << left << setw(10) << "S. Balance";
        cout << " | " << left << setw(10) << "D. Balance";
        cout << " | " << left << setw(10) << "User";
        cout << "\n\n";
        cout << setw(35) << left << "" << "-------------------------------------------------------------------------------------------------------\n\n";

        // check if there no data
        if (vTransferLogRec.size() == 0)
        {
            cout << "\n\n\t\t\t\t\t\tNo Transfers data available in the system!\n\n";
            cout << setw(35) << left << "" << "-------------------------------------------------------------------------------------------------------\n";
        }

        // print body
        else
        {
            for (clsBankClient::stTrnsferLogRecord record : vTransferLogRec)
            {
                _PrintTransferRecordLine(record);
                cout << endl;
            }
            cout << setw(35) << left << "" << "-------------------------------------------------------------------------------------------------------\n\n";

        }

    }

};