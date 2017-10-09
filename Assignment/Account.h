#include <iostream>
using namespace std;

#include "Item.h"
#ifndef ACCOUNT_H
#define ACCOUNT_H

//typedef class Account
//{
//public:
//	char* ID;
//	char* PassWord;
//	unsigned int numItems;
//	ppItem items;
//	Account();
//	~Account();
//	void AddItem();
//	void Report();
//}*pAccount, **ppAccount;

//typedef class Account
//{
//	char* ID;
//	char* PassWord;
//	unsigned int numItems;
//	ppItem items;
//public:
//	Account();
//	Account(Account&);
//	Account(char*, char*);
//	~Account();
//	char* getID(){ return ID; }
//	char*& getPassWord();
//	unsigned int getnumItems(){ return numItems; }
//	void AddItem();
//	friend ostream& operator<<(ostream&, Account&);
//}*pAccount, **ppAccount;

typedef class Account
{
	char* ID;
	char* PassWord;
	unsigned int numItems;
	ppItem items;
public:
	Account();
	Account(Account&);
	Account(char*, char*);
	~Account();
	char* getID(){ return ID; }
	char*& getPassWord();
	unsigned int getnumItems(){ return numItems; }
	void AddItem();
	friend ostream& operator<<(ostream&, Account&);
}*pAccount, **ppAccount;

#endif
