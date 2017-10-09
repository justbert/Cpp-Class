/**********************************************************************
Filename:			ass2.cpp
Version: 			1.0
Author:				Justin Bertrand
Student No:  		040 786 592
Course Name/Number:	C++ CST8219
Lab Sect: 			301
Assignment #:		2
Assignment name:	FleaBay with Overloaded Operators
IDE:				VS 2013
Due Date:			November 08 2015
Submission Date:	November 08 2015
Professor:			Andrew Tyler
Purpose: 			A class for a mock Online Sales Management System 
					(OSMS) whicha llows for the creation, validation,
					and printing of user accounts.
*********************************************************************/

#include <iostream>
#include <string.h>
using namespace std;

#include "FleaBay.h"

/********************************************************************
Function name:	FleaBay()
Purpose:		Default Constructor
					Allows for the instantiation of a FleaBay account.
In parameters:	none
Out parameters:	FleaBay object
Version:		1.0
Author:			Justin Bertrand
**********************************************************************/
FleaBay::FleaBay()
{
	numAccounts = 0;
	accounts = nullptr;
}

/********************************************************************
Function name:	~FleaBay()
Purpose:		Destructor
				Liberates all of the accounts in the FleaBay object.
In parameters:	none
Out parameters:	none
Version:		1.0
Author:			Justin Bertrand
**********************************************************************/
FleaBay::~FleaBay()
{
	unsigned int account_index;

	/* If no accounts exist, prevent the releasing of memory */
	if (numAccounts != 0)
	{
		for (account_index = 0; account_index < numAccounts; ++account_index)
		{
			delete accounts[account_index];
		}
	}

	delete accounts;
}

/********************************************************************
Function name:	Login()
Purpose:		Allows for the creation of a new account, and 
					the access of a previously created account.
					Also allows for the addition of an Item when
					logging into an account.
In parameters:	none
Out parameters:	boolean: true for success, false for failure
Version:		1.0
Author:			Justin Bertrand
**********************************************************************/
bool FleaBay::Login()
{
	char input;
	unsigned int account_index;
	char buffer[256];
	bool account_found = false;

	if (numAccounts == 0)
	{
		cout << "**NO ACCOUNTS**" << endl;
	}

	cout << "1. Add a new Account" << endl;
	cout << "2. Open an existing Account" << endl;
	cout << "3. Return to Main Menu\n" << endl;

	cin >> input;
	switch (input)
	{
	case '1':
		return AddNewAccount();
		break;
	case '2':
		cout << "please enter your account ID: " << endl;
		cin.clear();
		cin.ignore(10000, '\n');
		cin.getline(buffer, sizeof(buffer));

		//Looks for account in array of accounts
		for (account_index = 0; account_index < numAccounts; ++account_index) {
			if (strcmp(buffer, accounts[account_index]->getID()) == 0)
			{
				account_found = true;
				break;
			}
		}

		if (account_found)
		{
			cout << "please enter your account password: ";
			cin.getline(buffer, sizeof(buffer));
			if (strcmp(buffer, accounts[account_index]->getPassWord()) == 0)
			{
				if (accounts[account_index]->getnumItems() == 0)
				{
					cout << "No items in your account" << endl;
				}

				input = 'Y';
				while (input != 'Q' && input != 'q')
				{
					cout << "Do you wish to change your password? (yes = 'P')" << endl;
					cout << "Do you wish to add another Item (yes = 'Y')" << endl;
					cout << "Want to quit this menu? (yes = 'Q')" << endl;
					cin >> input;

					switch (input) {
					case 'Y':
					case 'y':
						accounts[account_index]->AddItem();
						break;
					case 'P':
					case 'p':
						cout << "Please enter your new password: ";
						cin.clear();
						cin.ignore(256, '\n');
						cin >> buffer;
						{
							char*& pw = accounts[account_index]->getPassWord();
							delete pw;
							pw = new char[strlen(buffer) + 1];
							strcpy(pw, buffer);
						}
						break;
					case 'Q':
					case 'q':
						break;
					default:
						cout << "Unrecognized input.";
					}
				}
			}
			else
			{
				cout << endl << buffer << "s password doesn't match this ID:" << endl;
			}
		}
		else
		{
			/* Allows to add items to account */
			cout << "Account not found" << endl;

		}
		break;
	case '3':
		cout << "Returning to Main Menu." << endl;
		break;
	}

	return true;
}

/********************************************************************
Function name:	operator[]()
Purpose:		Overloaded Operator
				Allows for the accessing of an account with an 
					ID
In parameters:	Pointer to a char arrau
Out parameters:	Account object
Version:		1.0
Author:			Justin Bertrand
**********************************************************************/
Account FleaBay::operator[](char* id)
{
	for (unsigned int account_index = 0; account_index < this->numAccounts; ++account_index) {
		if (strcmp(id, accounts[account_index]->getID()) == 0)
		{
			return *accounts[account_index];
		}
	}
	
	return Account("INVALID", "");
}

/********************************************************************
Function name:	operator<<()
Purpose:		Outputs all of the accounts, and the items associated
					to them to the default output stream.
In parameters:	ostream reference and FleaBay reference
Out parameters:	ostream reference
Version:		1.0
Author:			Justin Bertrand
**********************************************************************/
ostream& operator<<(ostream& os, FleaBay& fb)
{
	if (fb.numAccounts != 0)
	{
		for (unsigned int account_index = 0; account_index < fb.numAccounts; ++account_index)
		{
			os << *fb.accounts[account_index];
		}
	}
	else
	{
		cout << "**NO ACCOUNTS TO DISPLAY**" << endl;
	}

	return os;
}

/********************************************************************
Function name:	AddNewAccount()
Purpose:		Allows the addition of a new account to the 
					FleaBay instance.
In parameters:	none
Out parameters:	boolean: true for success, false for failure
Version:		1.0
Author:			Justin Bertrand
**********************************************************************/
bool FleaBay::AddNewAccount()
{
	ppAccount temp;
	char ID_buffer[256] = { 0 };
	char PW_buffer[256] = { 0 };
	bool account_name_unique = true;
	unsigned int index = 0;

	cout << "please enter your account ID: ";
	cin.clear();
	cin.ignore(10000, '\n');
	cin.getline(ID_buffer, sizeof(ID_buffer));

	for (index = 0; index < numAccounts; ++index) {
		if (strcmp(ID_buffer, accounts[index]->getID()) == 0)
		{
			account_name_unique = false;
			break;
		}
	}

	if (account_name_unique)
	{
		temp = new pAccount[numAccounts + 1];

		/* If there are previous accounts,
		the previous block of memory must be copied
		to the new block, then freed */
		if (numAccounts != 0)
		{
			memcpy(temp, accounts, sizeof(accounts)*numAccounts);
			if (temp == nullptr)
			{
				cout << "**MEMORY ALLOCATION ERROR**";
				return false;
			}

			delete accounts;
		}
		accounts = temp;

		cout << "please enter your account password: ";
		cin.getline(PW_buffer, sizeof(PW_buffer));

		accounts[numAccounts] = new Account(ID_buffer, PW_buffer);
		++numAccounts;
		return true;
	}
	else
	{
		cout << "**ACCOUNT NAME NOT UNIQUE**"<<endl;
		return true;
	}
}