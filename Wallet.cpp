#include "Wallet.h"

using namespace std;

Wallet::Wallet(){                     // constructor
    money = 0;
}
Wallet::Wallet(float money){            // constructor
    this->money = money;
}
float Wallet::getMoney(){              // return money owned by a person
    return money;
}
void Wallet::addMoney(float x){        // add money to the account
    money += x;
}
void Wallet::removeMoney(float x){     // remove money from the account
    if(x > money){
        cout<<"Your money is set to zero"<<endl;
        money = 0;
    }
    else {
        money -= x;
    }
}

ofstream & operator<<(ofstream & stream,  Wallet & w){
    stream<<w.money;
    return stream;
}

ostream & operator<<(ostream & stream, Wallet & w){
    stream<<w.money;
    return stream;
}

ifstream & operator>>(ifstream & stream, Wallet & w){
    stream>>w.money;
    return stream;
}

istream & operator>>(istream & stream, Wallet & w){
    stream>>w.money;
    return stream;
}