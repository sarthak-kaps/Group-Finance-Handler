#ifndef Wallet_H
#define Wallet_H

#include <bits/stdc++.h>
using namespace std;

class Wallet {           // class to handle money owned by a person within the application
private :
    float money;
public :
    Wallet();
    Wallet(float money);
    float getMoney();
    void addMoney(float x);
    void removeMoney(float x);
    friend ostream & operator<<(ostream & stream, Wallet & w);
    friend ofstream & operator<<(ofstream & stream, Wallet & w);
    friend istream & operator>>(istream & stream, Wallet & w);
    friend ifstream & operator>>(ifstream & stream, Wallet & w);
};
#endif