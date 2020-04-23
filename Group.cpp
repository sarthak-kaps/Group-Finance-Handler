#include "Group.h"


class leastDues {       // comparator to sort aggregate of pair class object according to a condition
public :
    const bool operator()(const pair<int, float> & p1, const pair<int, float> & p2) const{
        return p1.second < p2.second;
    }
};

class MaxDues {         // comparator to sort aggregate of pair class object according to a condition
public :
    const bool operator()(const pair<int, float> & p1, const pair<int, float> & p2) const {
        return p1.second > p2.second;
    }
};


template<class T>
Group<T>::Group(){         // constructor

}
template<class T>
Group<T>::Group(string name, int days, float finePercent){     // constructor
    this->name = name;
    this->days = days;
    this->finePercent = finePercent;
}
template<class T>
string Group<T>::getName(){                 // return group name
    return name;
}
template<class T>
int Group<T>::getDays(){              
    return days;
}
template<class T>
float Group<T>::getFinePercent(){
    return finePercent;
}
template<class T>
void Group<T>::add(T & p){                     // add person to group, check if person is already present or not
    if(ids.find(p) != ids.end()){
        cout<<"You are already part of this group"<<endl;
        return;
    }
    ids[p] = p.getID();
    rel[p.getID()] = p;
    group.addVertex(p.getID());
}
template<class T>
void Group<T>::seeDues(T & p){                // display dues of a person in the group
    if(!isInGroup(p)){
        cout<<"You are not part of this group"<<endl;
        return;
    }
    time_t curr = time(NULL);
    int count = 0;
    for(auto it : rel){
        if(group.getWeight(it.first, p.getID()).returnRecords().size() > 0){
            auto e = group.getWeight(it.first, p.getID());
            for(auto elem : e.returnRecords()){
                auto time = elem.getTime();
                auto date = ctime(&time);
                cout<<"Your dues against "<<it.second.getName()<<" are "<<elem.getBalance()<<" dated "<<date<<" Transaction id "<<time<<endl;
                long long int diff = 86400 * days;
                if(curr - time > diff){
                    cout<<"You have been fined for not paying dues within "<<days<<" days"<<endl;
                    int d = (curr - time)/86400;
                    float fine = finePercent * d * elem.getBalance() / 100;
                    cout<<"The amount you have to pay as fine is "<<fine<<endl;;
                }
            }
            cout<<endl;
            count++;
        }
    }
    if(count == 0){
        cout<<"You have no dues"<<endl;
    }
}
template<class T>
void Group<T>::seeTransactions(T & p){       // view active payments done by the person in the group that is those that have not been paid back
    if(!isInGroup(p)){
        cout<<"You are not part of this group"<<endl;
        return;
    }
    for(auto it : rel){
        if(group.getWeight(p.getID(), it.first).returnRecords().size() > 0){
            auto e = group.getWeight(p.getID(), it.first);
            for(auto elem : e.returnRecords()){
                auto time = elem.getTime();
                auto date = ctime(&time);
                cout<<"You payed "<<elem.getBalance()<<" to "<<it.second.getName()<<" on "<<date<<" Transaction id "<<time<<endl;
            }
            cout<<endl;
        }
    }
}
template<class T>
void Group<T>::removePerson(T & p){        // remove person from the group, check if the person has dues or other people have dues
    if(!isInGroup(p)){
        cout<<"You are not part of this group"<<endl;
        return;
    }
    for(auto it : ids){
        if(group.getWeight(it.second, p.getID()).returnRecords().size() > 0){
            cout<<"You have remaining dues, hence you cannot leave the group"<<endl;
            return;
        }
    }
    auto neighbours = group[p.getID()];
    for(auto it : neighbours){
        if(it.second.returnRecords().size() > 0){
            cout<<"Warning !, Some People have dues against you, Do you still want to leave ? (Yes/ No)"<<endl;
            string response;
            cin>>response;
            if(response == "No"){
                cout<<"Cancelling Request"<<endl;
                return;
            }
        }
    }
    cout<<"You have been successfully removed"<<endl;
    group.deleteVertex(p.getID());
    ids.erase(p);
    rel.erase(p.getID());
}
template<class T>
bool Group<T>::isInGroup(T & p){             // check membership in group
    return ids.find(p) != ids.end();
}
template<class T>
void Group<T>::getMembers(){               // show members of the group
    for(auto it : rel){
        cout<<it.first<<" "<<it.second.getName()<<endl;
    }
}
template<class T>
void Group<T>::pay(Person & p, float money){       // pay money for the group and add equal due for every person in the group
    if(!isInGroup(p)){
        cout<<"You are not part of this group"<<endl;
        return;
    }
    cout<<"Enter comment for the corresponding payment (One line Only)"<<endl;
    // cin.get();
    string buffer;
    // getline(cin, buffer);
    cin>>buffer;
    if(money == 0){
        return;
    }
    money = money / ids.size();
    for(auto elem : rel){
        if(elem.first == p.getID()){
            continue;
        }
        time_t now = time(NULL);
        auto x = TransactionRecord(money, now, buffer);
        group.addEdge(p.getID(), elem.first, x);
    }
}
template<class T>
void Group<T>::clearDuesAgainst(Person & p, int id){             //  clear due against a person against given id with given fine, cancel request if wallet does not have enough money
    if(!isInGroup(p)){
        cout<<"You are not part of this group"<<endl;
    }
    if(rel.find(id) == rel.end()){
        cout<<"ID does not exist"<<endl;
        return;
    }
    auto cost = getDuesAgainst(p, id);
    cout<<"Total payable amount is "<<cost<<endl;
    if(cost < p.getWallet().getMoney()){
        cout<<"Are you sure you want to pay ?(Y/N)"<<endl;
        char ch;
        cin>>ch;
        if(tolower(ch) == 'n'){
            cout<<"Request Cancelled"<<endl;
        }
        else {
            group.reset(id, p.getID());
            p.withdrawMoney(cost);
            rel[id].addMoney(cost);
            cout<<"Transaction Successful"<<endl;
        }
    }
    else {
        cout<<"Your Wallet does not contain enough money, kindly add money"<<endl;
    }
    ifstream in("Users.txt");
    ofstream out("Temp1");
    Person newP;
    while(in>>newP){
        if(rel.find(newP.getID()) != rel.end()){
            newP = rel[newP.getID()];
        }
        out<<newP;
    }
    remove("Users.txt");
    rename("Temp1", "Users.txt");
}
template<class T>
float Group<T>::getDuesAgainst(Person & p, int id, bool print){      // return dues against person with added fine if applicable
    auto e = group.getWeight(id, p.getID());
    float cost = 0;
    time_t curr = time(NULL);
    for(auto elem : e.returnRecords()){
        auto time = elem.getTime();
        auto date = ctime(&time);
        if(print){
            cout<<"Your dues against "<<rel[id].getName()<<" are "<<elem.getBalance()<<" dated "<<date<<endl;
        }
        long long int diff = 86400 * days;
        float fine = 0;
        if(curr - time > diff){
            if(print){
                cout<<"You have been fined for not paying dues within "<<days<<" days"<<endl;
            }
            int d = (curr - time)/86400;
            fine = finePercent * d * elem.getBalance() / 100;
            if(print){
                cout<<"The amount you have to pay as fine is "<<fine<<endl;
            }
        }
        cost += (elem.getBalance() + fine);
    }
    return cost;
}
template<class T>
void Group<T>::clearDues(Person & p){    // clear dues against everyone in the group, cancel request if wallet does not have enough money
    if(!isInGroup(p)){
        cout<<"You are not part of this group"<<endl;
    }
    float cost = 0;
    unordered_map<int, float> x;
    for(auto it : rel){
        if(it.first != p.getID()){
            auto currCost =  getDuesAgainst(p, it.first);
            cost += currCost;
            x[it.first] = currCost;
        }
    }
    cout<<"Total payable amount is "<<cost<<endl;
    if(cost <= p.getWallet().getMoney()){
        cout<<"Are you sure you want to pay ?(Y/N)"<<endl;
        char ch;
        cin>>ch;
        if(tolower(ch) == 'n'){
            cout<<"Request Cancelled"<<endl;
        }
        else {
            for(auto it : rel){
                if(it.first != p.getID()){
                    rel[it.first].addMoney(x[it.first]);
                    group.reset(it.first, p.getID());
                }
            }
            p.withdrawMoney(cost);
            cout<<"Transaction Successful"<<endl;
        }
    }
    else {
        cout<<"Your Wallet does not contain enough money, kindly add money"<<endl;
    }
    ifstream in("Users.txt");
    ofstream out("Temp1");
    Person newP;
    while(in>>newP){
        if(rel.find(newP.getID()) != rel.end()){
            newP = rel[newP.getID()];
        }
        out<<newP;
    }
    remove("Users.txt");
    rename("Temp1", "Users.txt");
}
template<class T>
int Group<T>::getSize(){     // return group size
    return ids.size();
}
template<class T>
void Group<T>::sortLeastDues(){         // sort group members according to increasing dues
    vector<pair<int, float>> v;
    for(auto i : rel){
        float total = 0;
        for(auto j : rel){
            if(i.first != j.first){
                total += getDuesAgainst(i.second, j.first, false);
            }
        }
        v.push_back(make_pair(i.first, total));
    }
    sort(v.begin(), v.end(), leastDues());
    for(auto it : v){
        cout<<rel[it.first].getName()<<" "<<it.second<<endl;
    }
}
template<class T>
void Group<T>::sortMaxDues(){              // sort group members according to decreasing dues
    vector<pair<int, float>> v;
    for(auto i : rel){
        float total = 0;
        for(auto j : rel){
            if(i.first != j.first){
                total += getDuesAgainst(i.second, j.first, false);
            }
        }
        v.push_back(make_pair(i.first, total));
    }
    sort(v.begin(), v.end(), MaxDues());
    for(auto it : v){
        cout<<rel[it.first].getName()<<" "<<it.second<<endl;
    }
}



