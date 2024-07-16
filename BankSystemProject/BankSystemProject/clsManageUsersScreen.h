#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsListUserScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"

class clsManageUsersScreen : protected clsScreen {

private:

	enum enOptions {
		listUser = 1,
		addNewUser = 2,
		deleteUser = 3,
		updateUser = 4,
		findUser = 5,
		mainMenu = 6
	};

	//---Read user option---
	static short _ReadManageUsersMenuOption() {

		short userOption;

		cout << setw(40) << left << "" << "Enter your option [1/6] : ";
		userOption = clsInputValidate::readShortNumberBetween(1, 6, "\t\t\t\t\tInvalid number! Please enter a valid number: ");
		return userOption;
	}

	//---Go back to manage user screen---
	static void _GoBackToManageUserScreen() {
		cout << "\n\nPress any key to go back to the manage user screen ...\n";
		system("pause>0");
		showMangeUserScreen();
	}

	//---List users screen---
	static void _ShowListUsersScreen() {
		clsListUserScreen::showListUsers();
	}

	//---Add new users screen---
	static void _ShowAddNewUsersScreen() {
		clsAddNewUserScreen::showAddNewUsersScreen();
	}

	//---Delete users screen---
	static void _ShowDeleteUsersScreen() {
		clsDeleteUserScreen::showDeleteUsersScreen();
	}

	//---Update users screen---
	static void _ShowUpdateUsersScreen() {
		clsUpdateUserScreen::showUpdateUsersScreen();
	}

	//---Find users screen---
	static void _ShowFindUsersScreen() {
		clsFindUserScree::showFindUsersScreen();
	}

	//---Perform transactions menu options---
	static void _PerformManageUserMenuOption(enOptions userOption) {

		switch (userOption)
		{
			case clsManageUsersScreen::listUser:
			{
				system("cls");
				_ShowListUsersScreen();
				_GoBackToManageUserScreen();
				break;
			}
			case clsManageUsersScreen::addNewUser:
			{
				system("cls");
				_ShowAddNewUsersScreen();
				_GoBackToManageUserScreen();
				break;
			}
			case clsManageUsersScreen::deleteUser:
			{
				system("cls");
				_ShowDeleteUsersScreen();
				_GoBackToManageUserScreen();
				break;
			}
			case clsManageUsersScreen::updateUser:
			{
				system("cls");
				_ShowUpdateUsersScreen();
				_GoBackToManageUserScreen();
				break;
			}
			case clsManageUsersScreen::findUser:
			{
				system("cls");
				_ShowFindUsersScreen();
				_GoBackToManageUserScreen();
				break;
			}
			case clsManageUsersScreen::mainMenu:
			{
				// nothing
			}
		}
	}


public:

	static void showMangeUserScreen() {
		
		// Check permissions 
		if (!checkAccessRights(clsUser::enPermissions::pManageUsers))
		{
			// if the user hasn't access, exit!
			return;
		}

		// print the main header
		system("cls");
		_DrawScreenHeader("\t\tManage user screen.");

		// Prit the header
		cout << setw(40) << left << "" << "============================================================\n";
		cout << setw(40) << left << "" << "\t\t\tManage user screen.\n";
		cout << setw(40) << left << "" << "============================================================\n";

		// Print the body
		cout << setw(40) << left << "" << "\t[1] List users.\n";
		cout << setw(40) << left << "" << "\t[2] Add new user.\n";
		cout << setw(40) << left << "" << "\t[3] Delete user.\n";
		cout << setw(40) << left << "" << "\t[4] Update user.\n";
		cout << setw(40) << left << "" << "\t[5] Find user.\n";
		cout << setw(40) << left << "" << "\t[6] Main menu.\n";
		cout << setw(40) << left << "" << "============================================================\n";

		_PerformManageUserMenuOption((enOptions)_ReadManageUsersMenuOption());

	}

};