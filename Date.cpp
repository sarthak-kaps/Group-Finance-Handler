#include "Date.h"

using namespace std;

Date::Date(){
        
}
Date::Date(int day, int month, int year){       // constructor
    this->day = day;
    this->month = month;
    this->year = year;
}
ofstream & operator<<(ofstream & stream, Date & d){
    stream<<d.day<<" "<<d.month<<" "<<d.year;
    return stream;
}

ifstream & operator>>(ifstream & stream, Date & d){
    stream>>d.day>>d.month>>d.year;
    return stream;
}

ostream & operator<<(ostream & stream, Date & d){
    stream<<d.day<<" "<<d.month<<" "<<d.year;
    return stream;
}

istream & operator>>(istream & stream, Date & d){
    return stream>>d.day>>d.month>>d.year;
}
