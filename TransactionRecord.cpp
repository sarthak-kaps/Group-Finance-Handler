#include "TransactionRecord.h"

TransactionRecord::TransactionRecord(){      // constructor

}
TransactionRecord::TransactionRecord(float balance, time_t time, string comment){       // constructor
    this->balance = balance;
    this->time = time;
    this->comment = comment;
}
float TransactionRecord::getBalance() const{             // get amount transacted
    return balance;
}
time_t TransactionRecord::getTime() const{              // get time of transaction - Note that the current application uses the system clock
    return time;
}
string TransactionRecord::getComment() const{           // get transaction comment
    return comment;
}
const bool TransactionRecord::operator<(const TransactionRecord & x) const {
    return time > x.getTime();
}

ostream & operator<<(ostream & stream, TransactionRecord & x){
    stream<<x.balance<<" "<<x.time<<" "<<x.comment;
    return stream;
}

ofstream & operator<<(ofstream & stream, TransactionRecord & x){
    stream<<x.balance<<" "<<x.time<<" "<<x.comment;
    return stream;
}

istream & operator>>(istream & stream, TransactionRecord & x){
    stream>>x.balance>>x.time>>x.comment;
    return stream;
}

ifstream & operator>>(ifstream & stream, TransactionRecord & x){
    stream>>x.balance>>x.time>>x.comment;
    return stream;
}
