/**********************************************************************
Filename:			Item.cpp
Version: 			3.0
Author:				Justin Bertrand
Student No:  		040 786 592
Course Name/Number:	C++ CST8219
Lab Sect: 			301
Assignment #:		3
Assignment name:	FleaBay with Polymorphic Inheritance
IDE:				VS 2013
Due Date:			December 05 2015
Submission Date:	December 05 2015
Professor:			Andrew Tyler
Purpose: 			A class for an Item which has a description and
						a price.
*********************************************************************/
#include <iostream>
#include <iomanip>
using namespace std;

#include "Item.h"

/********************************************************************
Function name:	Item()
Purpose:		Default Constructor
				Allows for the instantiation of an Item
In parameters:	none
Out parameters:	Item object
Version:		1.0
Author:			Justin Bertrand
**********************************************************************/
Item::Item()
{
	description = nullptr;
	price = 0.0;
}

/********************************************************************
Function name:	Item()
Purpose:		Copy Constructor
				Allows for the instantiation of an Item with the 
					reference of another.
In parameters:	Reference to an Item
Out parameters:	Item object
Version:		1.0
Author:			Justin Bertrand
**********************************************************************/
Item::Item(Item& item) 
{
	
	this->description = new char[strlen(item.description) + 1];
	strcpy(this->description, item.description);

	this->price = item.price;
}

/********************************************************************
Function name:	Item()
Purpose:		Constructor
				Allows for the instantiation of an Item with a
					specified description and price.
In parameters:	none
Out parameters:	Item object
Version:		1.0
Author:			Justin Bertrand
**********************************************************************/
Item::Item(char* desc, double price)
{
	this->description = new char[strlen(desc) + 1];
	strcpy(this->description, desc);

	this->price = price;
}

/********************************************************************
Function name:	~Item()
Purpose:		Destructor
				Frees the memory allocated for the description.
In parameters:	none
Out parameters:	none
Version:		1.0
Author:			Justin Bertrand
**********************************************************************/
Item::~Item()
{
	if (description)
		delete description;
}

/********************************************************************
Function name:	operator<<()
Purpose:		Overloaded operator
				Allows for the printing of an Item to a ostream.
In parameters:	ostream reference and an Item reference
Out parameters:	ostream reference
Version:		1.0
Author:			Justin Bertrand
**********************************************************************/
ostream& operator<<(ostream& os, Item& item)
{
	os << setiosflags(ios::fixed);
	os << item.description << ", cost = $" << setprecision(2) << item.price << endl;
	return os;
}

/********************************************************************
Function name:	FoodAndBeverages(Date, char*, double)
Purpose:		Constructor
				Allows for the construction of a FoodAndBeverage Item
In parameters:	Date: The expiry date of the food or beverage
				desc: a description of the food or beverage
				price: The price of the food or beverage
Out parameters: None
Version:		1.0
Author:			Justin Bertrand
**********************************************************************/
FoodAndBeverages::FoodAndBeverages(Date date, char* desc, double price) :Item(desc, price)
{
	expiryDate.year = date.year;
	expiryDate.month = date.month;
	expiryDate.day = date.day;
}

/********************************************************************
Function name:	FoodAndBeverages(FoodAndBeverages&)
Purpose:		Copy Constructor
				Allows for the copy of an Item
In parameters:	A FoodAndBeverage object.
Out parameters: None
Version:		1.0
Author:			Justin Bertrand
**********************************************************************/
FoodAndBeverages::FoodAndBeverages(FoodAndBeverages& FaB) :Item(FaB)
{
	expiryDate.year = FaB.expiryDate.year;
	expiryDate.month = FaB.expiryDate.month;
	expiryDate.day = FaB.expiryDate.day;
}

/********************************************************************
Function name:	Report()
Purpose:		Prints out the objects properties to the console.
In parameters:	None
Out parameters: None
Version:		1.0
Author:			Justin Bertrand
**********************************************************************/
void FoodAndBeverages::Report()
{
	cout << "Food and Beverages Report" << endl;
	cout << "Expiry Date: " << expiryDate.day << " ";
	cout << expiryDate.month << " " << expiryDate.year << endl;
	cout << *this;
}

/********************************************************************
Function name:	ToysAndHobbies(int, char*, double)
Purpose:		Constructor
				Allows for the construction of a ToysAndHobbies Item
In parameters:	int: The suitable age of the toy or hobby
				desc: a description of the toy or hobby
				price: The price of the toy or hobby
Out parameters: None
Version:		1.0
Author:			Justin Bertrand
**********************************************************************/
ToysAndHobbies::ToysAndHobbies(int suitAge, char* desc, double price) : Item(desc, price)
{
	suitableAge = suitAge;
}

/********************************************************************
Function name:	ToysAndHobbies(ToysAndHobbies&)
Purpose:		Copy Constructor
				Allows for the copy of an Item
In parameters:	A ToysAndBeverages object.
Out parameters: None
Version:		1.0
Author:			Justin Bertrand
**********************************************************************/
ToysAndHobbies::ToysAndHobbies(ToysAndHobbies& TaH) : Item(TaH), suitableAge(TaH.suitableAge) {}

/********************************************************************
Function name:	Report()
Purpose:		Prints out the objects properties to the console.
In parameters:	None
Out parameters: None
Version:		1.0
Author:			Justin Bertrand
**********************************************************************/
void ToysAndHobbies::Report()
{
	cout << "Toys and Hobbies Report" << endl;
	cout << "Suitable Age: " << suitableAge << " years" << endl;
	cout << *this;
}

/********************************************************************
Function name:	Deals(Date, char*, double)
Purpose:		Constructor
				Allows for the construction of a Deals item
In parameters:	Date: The closing date of the deal
				desc: a description of the deal
				price: The price of the deal
Out parameters: None
Version:		1.0
Author:			Justin Bertrand
**********************************************************************/
Deals::Deals(Date closing, char* desc, double price) : Item(desc, price)
{
	closingDate.year = closing.year;
	closingDate.month = closing.month;
	closingDate.day = closing.day;
}

/********************************************************************
Function name:	Deals(Deals&)
Purpose:		Copy Constructor
				Allows for the copy of an Item
In parameters:	A Deals object.
Out parameters: None
Version:		1.0
Author:			Justin Bertrand
**********************************************************************/
Deals::Deals(Deals& deal) :Item(deal)
{
	closingDate.year = deal.closingDate.year;
	closingDate.month = deal.closingDate.month;
	closingDate.day = deal.closingDate.day;
}

/********************************************************************
Function name:	Report()
Purpose:		Prints out the objects properties to the console.
In parameters:	None
Out parameters: None
Version:		1.0
Author:			Justin Bertrand
**********************************************************************/
void Deals::Report()
{
	cout << "Deals Report" << endl;
	cout << "Closing Date: " << closingDate.day << " ";
	cout << closingDate.month << " " << closingDate.year << endl;
	cout << *this;
}
