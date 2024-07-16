#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

using namespace std;

class  clsCurrencyCalculatorScreen : protected clsScreen {

private:

	static void _PrintCuurency(clsCurrency currency, string msg = "\nCurrency card:") {

		cout << "\n\n" << msg;
		cout << "\n=================================================";
		cout << "\nCountry	: " << currency.Country();
		cout << "\nCode 	: " << currency.currencyCode();
		cout << "\nName 	: " << currency.currencyName();
		cout << "\nRate(1$) : " << currency.Rate();
		cout << "\n=================================================\n";

	}

	static clsCurrency _GetCurrency(string text = "\nPlease enter currency code : ") {
		
		string currencyCode;
		cout << text;
		currencyCode = clsInputValidate::readString();

		// check if currency exsits
		while (!clsCurrency::isCurrencyExsit(currencyCode))
		{
			cout << "Currency not found!\nPlease enter a valid currency code: ";
			currencyCode = clsInputValidate::readString();
		}

		// create an obj of currency info
		clsCurrency currency = clsCurrency::findByCode(currencyCode);

		return currency;
	}

	static float _ReadAmount() {

		float amount = 0; 
		cout << "\nEnter amount : ";
		amount = clsInputValidate::readFloatNumber();
		return amount;
	}

	static void _PrintCalculationsResults(float amount, clsCurrency currency1, clsCurrency currency2) {

		_PrintCuurency(currency1, "Convert from: ");

		// convert to USD
		float amountInUSD = currency1.converToUSD(amount);
		cout << "\n" << amount << " " << currency1.currencyCode() << " = " << amountInUSD << " USD.\n";
		if (currency2.currencyCode() == "USD")
		{
			return;
		}

		// convert from USD to other currencies
		cout << "\nConvert from USD to " << currency2.currencyCode();
		_PrintCuurency(currency2, "Convert to: ");

		float amountInOtherCurrency = currency1.converToOtherCurrency(amount, currency2);
		cout << amount << " " << currency1.currencyCode() << " = " << amountInOtherCurrency << " " << currency2.currencyCode() << ".\n";

	}

public:

	static void showCurrencyCalculatorScreen() {
		
		char answer = 'y';

		while (answer == 'y' || answer == 'Y')
		{
			// Print the main screen
			system("cls");
			_DrawScreenHeader("\tCurrency calculator screen.");

			// Get currency & amount
			clsCurrency currencyFrom = _GetCurrency("\nPlease enter currency code 1 : ");
			clsCurrency currencyTo = _GetCurrency("\nPlease enter currency code 2 : ");
			float amount = _ReadAmount();

			// Calculate and show the results
			_PrintCalculationsResults(amount, currencyFrom, currencyTo);

			// ask for other calc
			cout << "\nDo you want to perform another calculator [y/n]? ";
			cin >> answer;
		}
		
	}

};