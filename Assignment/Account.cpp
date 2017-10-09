/**********************************************************************
Filename:			Account.cpp
Version: 			1.5
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
Purpose: 			A class for an Account which store an ID, a 
					a PassWord, and a list of items for sale.						
*********************************************************************/

#include <iostream>
using namespace std;

#include "Account.h"

/********************************************************************
Function name:	Account()
Purpose:		Default Constructor
				Allows for the instantiation of an Account
In parameters:	none
Out parameters:	Account object
Version:		1.0
Author:			Justin Bertrand
**********************************************************************/
Account::Account() 
{
	ID = nullptr;
	PassWord = nullptr;
	numItems = 0;
	items = nullptr;
}

/********************************************************************
Function name:	Account()
Purpose:		Copy Constructor
				Allows for a copy to be created when passing by 
				reference.
In parameters:	Reference to an account
Out parameters:	Account object
Version:		1.0
Author:			Justin Bertrand
**********************************************************************/
Account::Account(Account& account)
{
	this->ID = new char[strlen(account.ID) + 1];
	strcpy(this->ID, account.ID);

	this->PassWord = new char[strlen(account.PassWord) + 1];
	strcpy(this->PassWord, account.PassWord);

	this->numItems = account.numItems;

	this->items = new pItem[numItems];

	for (unsigned int index = 0; index < this->numItems; ++index)
	{
		this->items[index] = account.items[index];
	}
}

/********************************************************************
Function name:	Account()
Purpose:		Constructor
				Allows for the instantiation of an Account object
				with the specified ID and Password.
In parameters:	Two pointers to char arrays, one for the ID and 
				one for the PassWord.
Out parameters:	Account object
Version:		1.0
Author:			Justin Bertrand
**********************************************************************/
Account::Account(char* id, char* PW)
{
	this->ID = new char[strlen(id) + 1];
	strcpy(this->ID, id);

	this->PassWord = new char[strlen(PW) + 1];
	strcpy(this->PassWord, PW);

	numItems = 0;

	items = nullptr;
}

/********************************************************************
Function name:	~Account()
Purpose:		Destructor
				Releases the memory for the ID, the PassWord, and
					all of the Items associated to the account.
In parameters:	none
Out parameters:	none
Version:		1.0
Author:			Justin Bertrand
**********************************************************************/
Account::~Account() 
{
	delete ID;
	delete PassWord;

	for (unsigned int index = 0; index < numItems; ++index)
	{
		delete items[index];
	}

	delete items;
}

/********************************************************************
Function name:	getPassword()
Purpose:		Retrieve a reference to the Password.
In parameters:	none
Out parameters:	reference to a pointer to a character
Version:		1.0
Author:			Justin Bertrand
**********************************************************************/
char*& Account::getPassWord()
{
	return PassWord;
}

/********************************************************************
Function name:	AddItem()
Purpose:		Adds a new Item to the accounts item list asking for
					input from the default input stream.
In parameters:	none
Out parameters:	none
Version:		1.5
Author:			Justin Bertrand
**********************************************************************/
void Account::AddItem()
{
	char choice;
	char buffer[256] = { 0 };
	double price;
	pItem temp_item;
	ppItem temp_item_array;

	/* Retrieve description from user */
	cout << "Enter the new Item Description: " << endl;
	cin.clear();
	cin.ignore(256, '\n');
	cin.getline(buffer, sizeof(buffer));

	cout << "Please enter the item price: ";
	cin >> price;

	cout << "What category of item is it?" << endl;
	cout << "('F' = FoodAndBeverages,  'T' = ToysAndHobbies, 'D' = Deals): ";

	cin >> choice;
	cin.clear();
	cin.ignore(256, '\n');

	switch (choice)
	{
	case 'F':
	case 'f':
	{
		Date date;
		cout << "Please enter the expiry date as: day month year ";
		cin >> date.day;
		cin >> date.month;
		cin >> date.year;

		temp_item = new FoodAndBeverages(date, buffer, price);
	}
		break;
	case 'T':
	case 't':
		int age;

		cout << "Please enter the appropriate age group ( e.g. 6): ";
		cin >> age;

		temp_item = new ToysAndHobbies(age, buffer, price);
		break;
	case 'd':
	case 'D':
	{
		Date date;
		cout << "Please enter the date the deal expires as: day month year ";
		cin >> date.day;
		cin >> date.month;
		cin >> date.year;

		temp_item = new Deals(date, buffer, price);
	}
		break;
	default:
		cout << "Unrecognized input. Returning to previous menu." << endl;
	}


	if (choice == 'F' || choice == 'f' || choice == 'T' || choice == 't' || choice == 'd' || choice == 'D')
	{
		temp_item_array = new pItem[numItems + 1];
		memcpy(temp_item_array, items, sizeof(pItem)*numItems);
		delete items;
		items = temp_item_array;
		items[numItems] = temp_item;
		++numItems;
	}
}

/********************************************************************
Function name:	operator<<
Purpose:		Prints out the Account ID as well as all Items 
					associated to the Account
In parameters:	Reference to an ostream object and a reference
					to an account object.
Out parameters:	none
Version:		1.0
Author:			Justin Bertrand
**********************************************************************/
ostream& operator<<(ostream& os, Account& acc)
{
	cout << "Account ID: " << acc.getID() << endl;

	for (unsigned short index = 0; index < acc.getnumItems(); ++index)
	{
		cout << "Item " << index << ": ";
		acc.items[index]->Report();
		cout << endl;
	}
	cout << endl;

	return os;
}
