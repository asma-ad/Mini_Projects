#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"
#include "clsString.h"

class clsUpdateCurrencyRateScreen : protected clsScreen {

private:

	static void _PrintCuurency(clsCurrency currency) {

		cout << "\n=================================================";
		cout << "\nCurrency card:";
		cout << "\n=================================================";
		cout << "\nCountry	: " << currency.Country();
		cout << "\nCode 	: " << currency.currencyCode();
		cout << "\nName 	: " << currency.currencyName();
		cout << "\nRate(1$) : " << currency.Rate();
		cout << "\n=================================================\n";

	}

	static float _ReadRate() {

		float newRate = 0;
		cout << "\Enter new rate: ";
		newRate = clsInputValidate::readFloatNumber();
		return newRate;

	}

public:


	static void showUpdateRateScreen() {
		

		// print the main header
		system("cls");
		_DrawScreenHeader("\t\tUpdate curreny screen.");

		// Read currency code 
		string code;
		cout << "\nPlease enter currency code: ";
		code = clsInputValidate::readString();

		// check if currency exsits
		while (!clsCurrency::isCurrencyExsit(code))
		{
			cout << "Currency not found!\nPlease enter a valid currency code: ";
			code = clsInputValidate::readString();
		}

		// Print currency card
		clsCurrency currency = clsCurrency::findByCode(code);
		_PrintCuurency(currency);

		// check to update
		char answer = 'N';
		cout << "\nAre you sure you want to update the rate of this currency [Y/N]?  ";
		cin >> answer;

		// update
		if (answer == 'y' || answer == 'Y')
		{
			cout << "\nUpdate rate: ";
			cout << "\n------------------------------\n";
			currency.updateRate(_ReadRate());

			cout << "\nCurrency rate updated successfully!\n";
			_PrintCuurency(currency);
		}
		else
		{
			cout << "\nOperation cancelled\n";
		}
	}
};