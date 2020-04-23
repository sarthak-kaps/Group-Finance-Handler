#ifndef Date_H
#define Date_H

#include <bits/stdc++.h>
using namespace std;

class Date{      // handle DATES 
public:
    int day;
    int month;
    int year;
    Date();
    Date(int day, int month, int year); // constructor
    friend ostream & operator<<(ostream & stream, Date & d);
    friend istream & operator>>(istream & stream, Date & d);
    friend ofstream & operator<<(ofstream & stream, Date & d);
    friend ifstream & operator>>(ifstream & stream, Date & d);
};

#endif