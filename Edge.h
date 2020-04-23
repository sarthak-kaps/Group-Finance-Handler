#ifndef Edge_H
#define Edge_H

#include <bits/stdc++.h>
#include "TransactionRecord.h"
using namespace std;

class Edge {              // class representing edge of the Graph used to implement transaction relations
    set<TransactionRecord> records;   // Active transaction history stored as set sorted according to the time of transaction in ascending order
public :
    Edge();
    void addRecord(TransactionRecord & x);
    set<TransactionRecord> returnRecords();
    friend ofstream & operator<<(ofstream & stream, Edge & e);
    friend ostream & operator<<(ostream & stream, Edge & e);
    friend istream & operator>>(istream & stream, Edge & e);
    friend ifstream & operator>>(ifstream & stream, Edge & e);
};

#endif