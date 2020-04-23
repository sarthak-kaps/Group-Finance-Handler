#ifndef Person_H
#define Person_H

#include <bits/stdc++.h>
#include "Date.h"
#include "Wallet.h"
using namespace std;

class Person {              // class to handle the accounts of the people in the application
private :
    int userID;             // credentials of a person handled by the application
    string name;
    Date DOB;
    int age;
    string password;
    Wallet w;
public :
    Person();
    Person(int userID, string name, Date DOB, int age, string password);
    int getID()const;                // return id of the person
    string getName();                // return name
    void addMoney(float money);       // add money to account
    void withdrawMoney(float money);   // withdraw money from account
    Wallet getWallet();                // return wallet of the person
    Date getDOB();                     // return date of birth
    int getAge();                       // return age
    string getPassword();               // return password
    const bool operator<(const Person & p)const;
    friend ostream & operator<<(ostream & stream, Person & p);
    friend istream & operator>>(istream & stream, Person & p);
    friend ofstream & operator<<(ofstream & stream, Person & p);
    friend ifstream & operator>>(ifstream & stream, Person & p);
};

#endif