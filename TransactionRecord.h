#ifndef TransactionRecord_H
#define TransactionRecord_H

#include <bits/stdc++.h>
#include <ctime>
using namespace std;

class TransactionRecord {                     // class to maintain an instance of an active transaction between 2 persons in the group
    float balance;     // amount transacted
    time_t time;       // time of transaction
    string comment;    // comment for transaction
public :
    TransactionRecord();
    TransactionRecord(float balance, time_t time, string comment);
    float getBalance() const;
    time_t getTime() const;
    string getComment() const;
    const bool operator<(const TransactionRecord & x) const ;
    friend ostream & operator<<(ostream & stream, TransactionRecord & x);
    friend ofstream & operator<<(ofstream & stream, TransactionRecord & x);
    friend ifstream & operator>>(ifstream & stream, TransactionRecord & x);
    friend istream & operator>>(istream & stream, TransactionRecord & x);
};

#endif