#include "Person.h"
#include "Date.h"
#include "Wallet.h"

using namespace std;

Person::Person(){
    
}
Person::Person(int userID, string name, Date DOB, int age, string password){
    this->userID = userID;
    this->name = name;
    this->DOB = DOB;
    this->age = age;
    this->password = password;
    w = Wallet();
}
int Person::getID()const{
    return userID;
}
string Person::getName(){
    return name;
}
Date Person::getDOB(){
    return DOB;
}
int Person::getAge(){
    return age;
}
string Person::getPassword(){
    return password;
}
Wallet Person::getWallet(){
    return w;
}
void Person::addMoney(float money){
    w.addMoney(money);
}
void Person::withdrawMoney(float money){
    w.removeMoney(money);
}
const bool Person::operator<(const Person & p)const{
        return userID < p.getID();
}
ostream & operator<<(ostream & stream, string & s){
    for(int i = 0; i < s.length(); i++){
        stream<<s[i];
    }
    return stream;
}

ofstream & operator<<(ofstream & stream, Person & p){
    stream<<p.userID<<" "<<p.name<<" "<<p.DOB<<" "<<p.age<<" "<<p.password<<" "<<p.w<<endl;
    return stream;
}

ifstream & operator>>(ifstream & stream, Person & p){
    stream>>p.userID>>p.name>>p.DOB>>p.age>>p.password>>p.w;
    return stream;
}

istream & operator>>(istream & stream, Person & p){
    stream>>p.userID>>p.name>>p.DOB>>p.age>>p.password>>p.w;
    return stream;
}

ostream & operator<<(ostream & stream, Person & p){
    stream<<p.userID<<" "<<p.name<<" "<<p.DOB<<" "<<p.age<<" "<<p.password<<" "<<p.w<<endl;
    return stream;
}
