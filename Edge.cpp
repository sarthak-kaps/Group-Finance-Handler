#include "Edge.h"

Edge::Edge(){                 // constructor
    records.clear();
}
void Edge::addRecord(TransactionRecord & x){    // add new transaction
    records.insert(x);
}
set<TransactionRecord> Edge::returnRecords(){       // get record
    return records;
}

ostream & operator<<(ostream & stream, Edge & e){
    for(auto elem : e.records){
        stream<<elem<<" ";
    }
    auto x = TransactionRecord(-1, 0, "None");       // delimiter to help while reading record
    stream<<x; 
    return stream;
}

istream & operator>>(istream & stream, Edge & e){
   set<TransactionRecord> s;
   TransactionRecord x;
    while(stream>>x){
        if(x.getBalance() + 1 == 0){
            e.records = s;
            return stream;
        }
        s.insert(x);
    }
    return stream;
}

ofstream & operator<<(ofstream & stream, Edge & e){
    for(auto elem : e.records){
        stream<<elem<<" ";
    }
    auto x = TransactionRecord(-1.0, 0, "None");
    stream<<x; 
    return stream;
}

ifstream & operator>>(ifstream & stream, Edge & e){
    set<TransactionRecord> s;
    TransactionRecord x;
    while(stream>>x){
        if(x.getBalance() + 1 == 0){
            e.records = s;
            return stream;
        }
        s.insert(x);
    }
    return stream;
}
