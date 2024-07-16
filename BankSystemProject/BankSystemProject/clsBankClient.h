#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "clsPerson.h"
#include "clsString.h"
#include "Global.h"

using namespace std;

string fileName = "Clients.txt";

class clsBankClient : public clsPerson
{
private:

    enum enMode
    { 
        emptyMode = 0, updateMode = 1, addNewMode = 2
    };
    enMode _Mode;

    string _AccountNumber;
    string _PinCode;
    float _AccountBalance;
    bool _MarkForDelete = false;

    //---Convert line to object---
    static clsBankClient _ConvertLineToClientObject(string line, string seperator = "#//#")
    {
        vector<string> vClientData;
        vClientData = clsString::Split(line, seperator);

        return clsBankClient(enMode::updateMode, vClientData[0], vClientData[1], vClientData[2], vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));
    }

    //---Convert Client_Object to line (record)---
    static string _ConvertClientObjectToLine(clsBankClient client, string seperator = "#//#") {
        string clientRecord = "";

        clientRecord += client.firstName + seperator;
        clientRecord += client.lastName + seperator;
        clientRecord += client.email + seperator;
        clientRecord += client.phone + seperator;
        clientRecord += client.getAccountNumber() + seperator;
        clientRecord += client.pinCode + seperator;
        clientRecord += to_string(client.accountBalance);

        return clientRecord;
    }

    //---Convert transfer register line to record---
    struct stTrnsferLogRecord;
    static stTrnsferLogRecord _ConvertTransferLogLineToRecord(string line, string seperator = "#//#") {

        stTrnsferLogRecord trnsferLogRecord; // record

        vector <string> vTransferRegisterLine = clsString::Split(line, seperator);

        trnsferLogRecord.dateTime = vTransferRegisterLine[0];
        trnsferLogRecord.SourceClient = vTransferRegisterLine[1];
        trnsferLogRecord.DestanitionClient = vTransferRegisterLine[2];
        trnsferLogRecord.amount = stod(vTransferRegisterLine[3]);
        trnsferLogRecord.srcBalance = stod(vTransferRegisterLine[4]);
        trnsferLogRecord.DestBalance = stod(vTransferRegisterLine[5]);
        trnsferLogRecord.username = vTransferRegisterLine[6];

        return trnsferLogRecord;

    }

    //---Get empty object---
    static clsBankClient _GetEmptyClientObject()
    {
        return clsBankClient(enMode::emptyMode, "", "", "", "", "", "", 0);
    }

    //---Load client data from file---
    static vector<clsBankClient> _LoadClientsDataFromFile() {

        vector<clsBankClient> vClients;

        fstream myFile;
        myFile.open(fileName, ios::in);

        if (myFile.is_open())
        {
            string line = "";
            while (getline(myFile, line))
            {
                clsBankClient client = _ConvertLineToClientObject(line);
                vClients.push_back(client);
            }
            myFile.close();
        }
        return vClients;
    }

    //--- _SaveClientsDataToFile---
    static void  _SaveClientsDataToFile(vector<clsBankClient> vClients) {
        
        fstream myFile;
        myFile.open(fileName, ios::out); // overwrite

        string line = "";

        if (myFile.is_open())
        {
            for (clsBankClient C : vClients)
            {
                if (C._MarkForDelete == false)
                {
                    line = _ConvertClientObjectToLine(C);
                    myFile << line << endl;
               }
            }
            myFile.close();
        }
    }

    //---Update---
    void _Update() {

        // load clients from a file to a vector
        vector<clsBankClient> vClient = _LoadClientsDataFromFile();

        // make changes - update the obj
        for (clsBankClient& C : vClient) {

            if (C.getAccountNumber() == getAccountNumber()) {
                C = *this; // update information
                break;
            }
        }
       
        // save client data to the file (updated data)
        _SaveClientsDataToFile(vClient);
    }

    //---Add new---
    void _AddDataLineToFile(string line)
    {
        fstream myFile;

        myFile.open(fileName, ios::out | ios::app);

        if (myFile.is_open())
        {
            myFile << line << endl;
        }

        myFile.close();
    }

    void _AddNew() 
    {
        _AddDataLineToFile(_ConvertClientObjectToLine(*this));
    }

    //---Transfer record---
     string _PreparTransferRecord(clsBankClient DestanitionClient, float transferAmount, string seperator = "#//#") {

        string transferRecord = "";

        transferRecord += clsDate::getSystemDateTimeString() + seperator;
        transferRecord += getAccountNumber() + seperator;
        transferRecord += DestanitionClient.getAccountNumber() + seperator;
        transferRecord += to_string(transferAmount) + seperator;
        transferRecord += to_string(getAccountBalance()) + seperator;
        transferRecord += to_string(DestanitionClient.getAccountBalance()) + seperator;
        transferRecord += currentUser.userName;

        return transferRecord;
    }

    //---Register transfer in a log file---
     void _RegisterTransferLog(clsBankClient DestanitionClient, float transferAmount) {

        string dataLine = _PreparTransferRecord(DestanitionClient, transferAmount);

        fstream myFile;
        myFile.open("TransferRegisterFile.txt", ios::out | ios::app);

        if (myFile.is_open())
        {
            myFile << dataLine << endl;
            myFile.close();
        }
    }

public:
    clsBankClient(enMode mode, string firstName, string lastName, string email, string phone, string accountNumber, string pinCode, double accountBalance)
        : clsPerson(firstName, lastName, email, phone)
    {
        _Mode = mode;
        _AccountNumber = accountNumber;
        _PinCode = pinCode;
        _AccountBalance = accountBalance;
    }

    // Getters & Setters
    string getAccountNumber()
    {
        return _AccountNumber;
    }

    void setPinCode(string pinCode)
    {
        _PinCode = pinCode;
    }
    string getPinCode()
    {
        return _PinCode;
    }
    __declspec(property(get = getPinCode, put = setPinCode)) string pinCode;

    void setAccountBalance(float accountBalance)
    {
        _AccountBalance = accountBalance;
    }
    float getAccountBalance()
    {
        return _AccountBalance;
    }
    __declspec(property(get = getAccountBalance, put = setAccountBalance)) float accountBalance;

    //---Mode---
    bool isEmpty()
    {
        return (_Mode == enMode::emptyMode);
    }

    //---print---
    /*
    * // No UI code inside object!
    void Print()
    {
        cout << "\nClient Card:";
        cout << "\n-----------------------------------------";
        cout << "\nFirst name       :" << firstName;
        cout << "\nLast name        :" << lastName;
        cout << "\nFull name        :" << fullName();
        cout << "\nEmail            :" << email;
        cout << "\nPhone            :" << phone;
        cout << "\nAccount number   :" << _AccountNumber;
        cout << "\nPassword         :" << _PinCode;
        cout << "\nBalance          :" << _AccountBalance;
        cout << "\n-----------------------------------------\n";
    }
    */

    //---Find client---
    static clsBankClient findClient(string accountNumber)
    {
        fstream myFile;
        myFile.open(fileName, ios::in);

        if (myFile.is_open())
        {
            string line = "";
            while (getline(myFile, line))
            {
                clsBankClient client = _ConvertLineToClientObject(line);
                if (client.getAccountNumber() == accountNumber)
                {
                    myFile.close();
                    return client;
                }
            }
            myFile.close();
        }

        return _GetEmptyClientObject();
    }

    static clsBankClient findClient(string accountNumber, string pinCode)
    {

        fstream myFile;
        myFile.open(fileName, ios::in);

        if (myFile.is_open())
        {
            string line = "";
            while (getline(myFile, line))
            {
                clsBankClient client = _ConvertLineToClientObject(line);
                if (client.getAccountNumber() == accountNumber && client.getPinCode() == pinCode)
                {
                    myFile.close();
                    return client;
                }
            }
            myFile.close();
        }

        return _GetEmptyClientObject();
    }

    //---Is client exist---
    static bool isClientExist(string accountNumber)
    {
        clsBankClient client = clsBankClient::findClient(accountNumber);
        return (!client.isEmpty());
    }

    //---Save---
    enum enSaveResults{svFailedEmptyObj = 0, svSucceded = 1, svFailAccountNumberExists = 2};
    enSaveResults Save() {
        switch (_Mode)
        {
            case clsBankClient::emptyMode:
            {
                return enSaveResults::svFailedEmptyObj;
                break;
            }
            case clsBankClient::updateMode:
            {
                _Update();
                return enSaveResults::svSucceded;
                break;
            }
            case clsBankClient::addNewMode:
            {
                if (clsBankClient::isClientExist(_AccountNumber))
                {
                    return enSaveResults::svFailAccountNumberExists;
                }
                else
                {
                    _AddNew();
                    _Mode = enMode::updateMode;
                    return enSaveResults::svSucceded;
                }
            }

        }
    }

    //---Get add new client object---
    static clsBankClient GetAddNewClientObject(string accountNumber)
    {
        return clsBankClient(enMode::addNewMode, "", "", "", "", accountNumber, "", 0);
    }

    //---Delete client---
    bool Delete() {
        vector <clsBankClient> vClients = _LoadClientsDataFromFile();

        for (clsBankClient& C : vClients)
        {
            if (C.getAccountNumber() == _AccountNumber)
            {
                C._MarkForDelete = true;
                break;
            }
        }

        _SaveClientsDataToFile(vClients);

        *this = _GetEmptyClientObject();

        return true;
    }

    //---Client lists---
    static vector <clsBankClient> getClientsList() {
        return _LoadClientsDataFromFile();
    }

    //---Total balances---
    static double getTotalBalances() {

        vector <clsBankClient> vClients = clsBankClient::getClientsList();

        double totalBalances = 0;
        for (clsBankClient C : vClients)
        {
            totalBalances += C.accountBalance;
        }

        return totalBalances;
    }

    //---Deposite---
    bool Deposite(double amount) {
        
        // Handle if the input is negative
        if (amount < 0)
        {
            return false;
        }
        else
        {
            _AccountBalance += amount;
            Save();
        }
    }

    //---Withdraw---
    bool Withdraw(double amount) {

        if (amount > _AccountBalance)
        {
            return false;
        }
        else
        {
            _AccountBalance -= amount;
            Save();
        }

    }

    //---Transfet---
    bool Transfer(float amount, clsBankClient &accountTo) {

        // check amount & balance
        if (amount > accountBalance || amount < 0)
        {
            return false;
        }

        Withdraw(amount);
        accountTo.Deposite(amount);
        _RegisterTransferLog(accountTo,amount);
        return true;

    }

    //---Transfer register list---
    struct stTrnsferLogRecord
    {
        string dateTime;
        string SourceClient;
        string DestanitionClient;
        float amount =0;
        float srcBalance=0;
        float DestBalance=0;
        string username;
    };
   
    static  vector <stTrnsferLogRecord> getTransfersLogList()
    {
        vector <stTrnsferLogRecord> vTransferLogRecord;

        fstream MyFile;
        MyFile.open("TransferRegisterFile.txt", ios::in);

        if (MyFile.is_open())
        {

            string line;

            stTrnsferLogRecord transferRecord;

            while (getline(MyFile, line))
            {

                transferRecord = _ConvertTransferLogLineToRecord(line);

                vTransferLogRecord.push_back(transferRecord);

            }

            MyFile.close();

        }

        return vTransferLogRecord;

    }

   

};