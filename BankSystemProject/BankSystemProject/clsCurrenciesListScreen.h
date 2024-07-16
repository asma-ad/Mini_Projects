#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"

using namespace std;

class clsCurrenciesListScreen : protected clsScreen {

private:

	static void _PrintCuurency(clsCurrency currency) {

		cout << setw(15) << left << ""
		  	 << " | " << left << setw(35) << currency.Country();
		cout << " | " << left << setw(20) << currency.currencyCode();
		cout << " | " << left << setw(40) << currency.currencyName();
		cout << " | " << left << setw(20) << currency.Rate();
	}

public:

	static void showCurrencyList() {

		// get currenies
		vector <clsCurrency> vCurrency = clsCurrency::getCurrenciesList();

		// Print the main header
		string title = "\t\tCurrencies list screen.";
		string sub = "\t  (" + to_string(vCurrency.size()) + ") currencis.";
		_DrawScreenHeader(title, sub);

		// print header        
		cout << setw(15) << left << "" << "-------------------------------------------------------------------------------------------------------------------\n\n";

		cout << setw(15) << left << ""
			<< " | " << left << setw(35) << "Country";
		cout << " | " << left << setw(20) << "Code";
		cout << " | " << left << setw(40) << "Name";
		cout << " | " << left << setw(20) << "Rate";
		cout << "\n\n";
		cout << setw(15) << left << "" << "-------------------------------------------------------------------------------------------------------------------\n\n";

		// check if there no currenies
		if (vCurrency.size() == 0)
		{
			cout << "\n\n\t\t\t\t\t\tNo currenies available in the system!\n";
			cout << "\n----------------------------------------------------------------------------------------------------------------------------------------\n";

		}

		// print body
		else
		{
			for (clsCurrency C : vCurrency)
			{
				_PrintCuurency(C);
				cout << endl;
			}
			cout << setw(15) << left << "" << "-------------------------------------------------------------------------------------------------------------------\n\n";

		}

	}

};