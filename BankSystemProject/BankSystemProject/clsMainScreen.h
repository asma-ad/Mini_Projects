#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsClientListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUsersScreen.h"
#include "clsLoginRegisterScreen.h"
#include "Global.h"
#include "clsCurrencyExchangeMainScreen.h"

using namespace std;

class clsMainScrenn : protected clsScreen {

private:

	enum enMainScreenOptions {
		enShowClientsList = 1,
		enAddNewClient = 2,
		enDeleteClient = 3,
		enUpdateClientInfo = 4,
		enFindClient = 5,
		enTrnsactions = 6,
		enManageUsers = 7,
		enLoginRegister = 8,
		enCurrencyExchange = 9,
		enLogOut = 10
	};

	static short _ReadMainMenuOption() {

		short userOption;

		cout << setw(40) << left << "" << "Enter your option [1/10] : ";
		userOption = clsInputValidate::readShortNumberBetween(1, 10, "\t\t\t\t\tInvalid number! Please enter a valid number: ");
		return userOption;
	}

	static void _GoBackToMainScreen(){
		cout << "\n\nPress any key to go back to the main screen ...\n";

		system("pause>0");
		showMainMenu();
	}

	static void _ShowAllClientsScreen() {
		clsClientListScreen::showClientsList();
	}

	static void _ShowAddNewClientScreen() {

		clsAddNewClientScreen::showAddNewClientScreen();
	}

	static void _ShowDeleteClientScreen() {
		clsDeleteClientScreen::showDeleteClientScreen();
	}

	static void _ShowUpdateClientScreen() {
		clsUpdateClientScreen::showUpdateClientScreen();
	}

	static void _ShowFindClientScreen() {
		clsFindClientScreen::showFindClientScreen();
	}

	static void _ShowTransactionsScreen() {
		clsTransactionsScreen::showTransactionsScreen();
	}
	
	static void _ShowMangeUserScreen() {
		clsManageUsersScreen::showMangeUserScreen();
	}

	static void _ShowLoginRegisterScreen() {
		clsLoginRegisterScreen::showLoginRegisterScreen();
	}

	static void _ShowCurrencyExchangeMainScreen() {
		clsCurrencyExchangeMainScreen::showMainMenu();
	}

	static void _Logout() {
		
		// Just return an empty obj
		currentUser = clsUser::Find("", "");
		
		/*
			To show Login screen after Logoing out
			I can't call clsLoginScreen::showLoginScreen()
			because that'll cause "circular reference" ...
			So instead, I can use while loop in the mail file.
		*/
		
	}

	static void _PerformMainMenuOption(enMainScreenOptions options) {

		switch (options)
		{
		case clsMainScrenn::enShowClientsList:
		{
			system("cls");
			_ShowAllClientsScreen();
			_GoBackToMainScreen();
			break;
		}
		case clsMainScrenn::enAddNewClient:
		{
			system("cls");
			_ShowAddNewClientScreen();
			_GoBackToMainScreen();
			break;
		}
		case clsMainScrenn::enDeleteClient:
		{
			system("cls");
			_ShowDeleteClientScreen();
			_GoBackToMainScreen();
			break;
		}
		case clsMainScrenn::enUpdateClientInfo:
		{
			system("cls");
			_ShowUpdateClientScreen();
			_GoBackToMainScreen();
			break;
		}
		case clsMainScrenn::enFindClient:
		{
			system("cls");
			_ShowFindClientScreen();
			_GoBackToMainScreen();
			break;
		}
		case clsMainScrenn::enTrnsactions:
		{
			system("cls");
			_ShowTransactionsScreen();
			_GoBackToMainScreen();
			break;
		}
		case clsMainScrenn::enManageUsers:
		{
			system("cls");
			_ShowMangeUserScreen();
			_GoBackToMainScreen();
			break;
		}
		case clsMainScrenn::enLoginRegister:
		{
			system("cls");
			_ShowLoginRegisterScreen();
			_GoBackToMainScreen();
			break;
		}
		case clsMainScrenn::enCurrencyExchange:
		{
			system("cls");
			_ShowCurrencyExchangeMainScreen();
			_GoBackToMainScreen();
			break;
		}
		case clsMainScrenn::enLogOut:
		{
			system("cls");
			_Logout();
			break;
		}
		default:
			break;
		}
	}

public:

	static void showMainMenu() {

		system("cls");
		clsScreen::_DrawScreenHeader("\t\tMain screen");

		// the empty string is used to ensure that the specified width and justification are applied correctly before printing the rest of the message.
		cout << setw(40) << left << "" << "============================================================\n";
		cout << setw(40) << left << "" << "\t\t\tMain menu\n";
		cout << setw(40) << left << "" << "============================================================\n";

		cout << setw(40) << left << "" << "\t[1] Show clients list.\n";
		cout << setw(40) << left << "" << "\t[2] Add new client.\n";
		cout << setw(40) << left << "" << "\t[3] Delete client.\n";
		cout << setw(40) << left << "" << "\t[4] Update client info.\n";
		cout << setw(40) << left << "" << "\t[5] Find client.\n";
		cout << setw(40) << left << "" << "\t[6] Transactions.\n";
		cout << setw(40) << left << "" << "\t[7] Manage users.\n";
		cout << setw(40) << left << "" << "\t[8] Login register.\n";
		cout << setw(40) << left << "" << "\t[9] Currency exchange.\n";
		cout << setw(40) << left << "" << "\t[10] Log out.\n";
		cout << setw(40) << left << "" << "============================================================\n";
	
		_PerformMainMenuOption(enMainScreenOptions(_ReadMainMenuOption()));

	}
};