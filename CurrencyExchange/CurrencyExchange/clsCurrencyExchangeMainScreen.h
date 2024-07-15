#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRateScreen.h"

using namespace std;

class clsCurrencyExchangeMainScreen : clsScreen {

private:

	enum enOption {listCurrencies = 1, findCurrency = 2, updateRate = 3, currencyCalculator = 4, exit = 5};

	static short _ReadMainMenuOption() {
		short userOption;

		cout << setw(40) << left << "" << "Enter your option [1/5] : ";
		userOption = clsInputValidate::readShortNumberBetween(1, 5, "\t\t\t\t\tInvalid number! Please enter a valid number: ");
		return userOption;
	}

	static void _GoBackToMainScreen() {
		cout << "\n\nPress any key to go back to the main screen ...\n";

		system("pause>0");
		showMainMenu();
	}

	static void _ShowCurrencyListScreen() {
		clsCurrenciesListScreen::showCurrencyList();
	}

	static void _ShowFindCurrencyScreen() {
		clsFindCurrencyScreen::showFindCurrencyScreen();
	}

	static void _ShowUpdateRateScreen() {
		clsUpdateCurrencyRateScreen::showUpdateRateScreen();
	}

	static void _ShowCurrencyCalculatorScreen() {
		cout << "\nWork on it\n";
	}
	
	static void _PerformCurrenciesMenuOption(enOption option) {

		switch (option)
		{
			case clsCurrencyExchangeMainScreen::listCurrencies:
			{
				system("cls");
				_ShowCurrencyListScreen();
				_GoBackToMainScreen();
				break;
			}
			case clsCurrencyExchangeMainScreen::findCurrency:
			{
				system("cls");
				_ShowFindCurrencyScreen();
				_GoBackToMainScreen();
				break;
			}
			case clsCurrencyExchangeMainScreen::updateRate:
			{
				system("cls");
				_ShowUpdateRateScreen();
				_GoBackToMainScreen();
				break;
			}
			case clsCurrencyExchangeMainScreen::currencyCalculator:
			{
				system("cls");
				_ShowCurrencyCalculatorScreen();
				_GoBackToMainScreen();
				break;
			}
			case clsCurrencyExchangeMainScreen::exit:
			{
				return;
			}
		}

	}

public:

	static void showMainMenu() {

		system("cls");
		clsScreen::_DrawScreenHeader("\tCurrency exchange main screen");

		cout << setw(40) << left << "" << "============================================================\n";
		cout << setw(40) << left << "" << "\t\tCurrency exchange menu\n";
		cout << setw(40) << left << "" << "============================================================\n";

		cout << setw(40) << left << "" << "\t[1] List currencies.\n";
		cout << setw(40) << left << "" << "\t[2] Find currency.\n";
		cout << setw(40) << left << "" << "\t[3] Update rate.\n";
		cout << setw(40) << left << "" << "\t[4] Currency calculator.\n";
		cout << setw(40) << left << "" << "\t[5] Exit.\n";
		cout << setw(40) << left << "" << "============================================================\n";

		_PerformCurrenciesMenuOption(enOption(_ReadMainMenuOption()));

	}

};