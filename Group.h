#ifndef Group_H
#define Group_H

#include <bits/stdc++.h>
#include "Graph.h"
#include "Person.h"
using namespace std;

template <class T>
class Group;
template <class T>
ostream & operator<<(ostream & stream, Group<T> & g);
template <class T>
ofstream & operator<<(ofstream & stream, Group<T> & g);
template <class T>
istream & operator>>(istream & stream, Group<T> & g);
template <class T>
ifstream & operator>>(ifstream & stream, Group<T> & g);

template<class T>
class Group {                    // Implementation of a group in the applicatio
private :
    string name;                // Must be unique
    int days;                   // Number of days after which fine is imposed
    float finePercent;          // fine rate to be applied
    Graph group;                 // Graph representing transactions between 2 nodes correspoding to persons
    map<T, int> ids;            // map between person and id
    map<int, T> rel;            // map between id and person
public :
    Group();
    Group(string name, int days, float finePercent);
    string getName();
    int getDays();
    float getFinePercent();
    void add(T & p);
    void seeDues(T & p);
    void seeTransactions(T & p);
    void removePerson(T & p);
    bool isInGroup(T & p);
    void getMembers();
    void pay(Person & p, float money);
    void clearDuesAgainst(Person & p, int id);
    float getDuesAgainst(Person & p, int id, bool print = true);
    void clearDues(Person & p);
    int getSize();
    void sortLeastDues();
    void sortMaxDues();
    friend ostream & operator<< <>(ostream & stream, Group<T> & g);
    friend ofstream & operator<< <>(ofstream & stream, Group<T> & g);
    friend istream & operator>> <>(istream & stream, Group<T> & g);
    friend ifstream & operator>> <>(ifstream & stream, Group<T> & g);
};


template <class T>
ostream & operator<<(ostream & stream, Group<T> & g){    
    stream<<g.name<<" "<<g.days<<" "<<g.finePercent<<" "<<g.group;
    return stream;
}

template <class T>
istream & operator>>(istream & stream, Group<T> & g){
    string name;
    int days;
    float finePercent;
    Graph h;
    stream>>name;
    stream>>days;
    stream>>finePercent;
    stream>>h;
    g.name = name;
    g.group = h;
    g.days = days;
    g.finePercent = finePercent;
    Person p;
    for(auto elem : h.getVertices()){
        ifstream in("Users.txt");
        Person p;
        while(in>>p){
            if(p.getID() == elem){
                break;
            }
        }
        in.close();
        g.ids[p] = p.getID();
        g.rel[p.getID()] = p;
    }
    return stream;
}

template <class T>
ofstream & operator<<(ofstream & stream, Group<T> & g){    // operator to write into the file
    stream<<g.name<<" "<<g.days<<" "<<g.finePercent<<" "<<g.group;
    return stream;
}


template <class T>
ifstream & operator>>(ifstream & stream, Group<T> & g){     // operator to read from the file
    string name;
    Graph h;
    int days;
    float finePercent;
    stream>>name>>days>>finePercent>>h;
    g = Group<Person>(name, days, finePercent);
    g.group = h;
    Person p;
    for(auto elem : h.getVertices()){
        ifstream in("Users.txt");
        Person p;
        while(in>>p){
            if(p.getID() == elem){
                break;
            }
        }
        g.ids[p] = p.getID();
        g.rel[p.getID()] = p;
    }
    return stream;
}

#endif