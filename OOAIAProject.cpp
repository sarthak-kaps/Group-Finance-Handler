/****************************************
********* GROUP HANDLING SYSTEM *********
******** AUTHOR : SARTHAK KAPOOR ********   
* INDIAN INSTITUTE OF TECHNOLOGY MADRAS *   
****** DATE CREATED : 6 MARCH 2020 ******
***** LAST MODIFIED : 19 APRIL 2020 *****
*****************************************/

#include <bits/stdc++.h>
#include <termios.h>
#include <unistd.h>
#include <ctime>

using namespace std;
 
int getch() {           // modified getch to print * while taking input
    int ch;
    struct termios t_old, t_new;

    tcgetattr(STDIN_FILENO, &t_old);
    t_new = t_old;
    t_new.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &t_new);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &t_old);
    return ch;
}

string getPassword(bool show_asterisk=true) {          //  read password and print * for each character read
    const char BACKSPACE=127;
    const char RETURN=10;

    unsigned char ch=0;
    string password;
    while((ch=getch())!=RETURN) {
        if(ch==BACKSPACE) {
            if(password.length()!=0) {
                if(show_asterisk)
                cout <<"\b \b";
                password.resize(password.length()-1);
            }
        }
        else {
            password+=ch;
            if(show_asterisk)
            cout <<'*';
        }
    }
    cout <<endl;
    return password;
}



class Date{      // handle DATES 
public:
    int day;
    int month;
    int year;
    Date(){
        
    }
    Date(int day, int month, int year){       // constructor
        this->day = day;
        this->month = month;
        this->year = year;
    }
    friend ostream & operator<<(ostream & stream, Date & d);
};

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

class Wallet {           // class to handle money owned by a person within the application
private :
    float money;
public :
    Wallet(){                     // constructor
        money = 0;
    }
    Wallet(float money){            // constructor
        this->money = money;
    }
    float getMoney(){              // return money owned by a person
        return money;
    }
    void addMoney(float x){        // add money to the account
        money += x;
    }
    void removeMoney(float x){     // remove money from the account
        if(x > money){
            cout<<"Your money is set to zero"<<endl;
            money = 0;
        }
        else {
            money -= x;
        }
    }
    friend ostream & operator<<(ostream & stream, Wallet & w);
    friend ofstream & operator<<(ofstream & stream, Wallet & w);
    friend istream & operator>>(istream & stream, Wallet & w);
    friend ifstream & operator>>(ifstream & stream, Wallet & w);
};

ofstream & operator<<(ofstream & stream, Wallet & w){
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

class Person {              // class to handle the accounts of the people in the application
private :
    int userID;             // credentials of a person handled by the application
    string name;
    Date DOB;
    int age;
    string password;
    Wallet w;
public :
    Person();
    Person(int userID, string name, Date DOB, int age, string password);
    int getID()const;                // return id of the person
    string getName();                // return name
    void addMoney(float money);       // add money to account
    void withdrawMoney(float money);   // withdraw money from account
    Wallet getWallet();                // return wallet of the person
    Date getDOB();                     // return date of birth
    int getAge();                       // return age
    string getPassword();               // return password
    const bool operator<(const Person & p)const{
        return userID < p.getID();
    }
    friend ostream & operator<<(ostream & stream, Person & p);
    friend istream & operator>>(istream & stream, Person & p);
    friend ofstream & operator<<(ofstream & stream, Person & p);
    friend ifstream & operator>>(ifstream & stream, Person & p);
};

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


class TransactionRecord {                     // class to maintain an instance of an active transaction between 2 persons in the group
    float balance;     // amount transacted
    time_t time;       // time of transaction
    string comment;    // comment for transaction
public :
    TransactionRecord(){      // constructor

    }
    TransactionRecord(float balance, time_t time, string comment){       // constructor
        this->balance = balance;
        this->time = time;
        this->comment = comment;
    }
    float getBalance() const{             // get amount transacted
        return balance;
    }
    time_t getTime() const{              // get time of transaction - Note that the current application uses the system clock
        return time;
    }
    string getComment() const{           // get transaction comment
        return comment;
    }
    const bool operator<(const TransactionRecord & x) const {
        return time > x.getTime();
    }
    friend ostream & operator<<(ostream & stream, TransactionRecord & x);
    friend ofstream & operator<<(ofstream & stream, TransactionRecord & x);
    friend ifstream & operator>>(ifstream & stream, TransactionRecord & x);
    friend istream & operator>>(istream & stream, TransactionRecord & x);
};

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

class Edge {              // class representing edge of the Graph used to implement transaction relations
    set<TransactionRecord> records;   // Active transaction history stored as set sorted according to the time of transaction in ascending order
public :
    Edge(){                 // constructor
        records.clear();
    }
    void addRecord(TransactionRecord & x){    // add new transaction
        records.insert(x);
    }
    set<TransactionRecord> returnRecords(){       // get record
        return records;
    }
    friend ofstream & operator<<(ofstream & stream, Edge & e);
    friend ostream & operator<<(ostream & stream, Edge & e);
    friend istream & operator>>(istream & stream, Edge & e);
    friend ifstream & operator>>(ifstream & stream, Edge & e);
};

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

class Comparator{           // comparator for sorting aggregate of pair class objects
public :
    bool operator()(const pair<int, int> & p1, const pair<int, int> & p2){
        return p1.first < p2.first;
    }
};

class Graph {           // Implementation of a Dynamic Directed Graph Class with efficient support of vertex delete and addition
private :
    map<int, map<int, Edge>> g;     // adjacency list representation
public :
    Graph(){     // constructor

    }
    void addVertex(int v){      // add a new vertex
        g[v].clear();
    }
    void addEdge(int u, int v, TransactionRecord & x){    // add a new edge
        if(g.find(v) == g.end()){
            g[v].clear();
        }
        g[u][v].addRecord(x);
    }
    void assignEdge(int u, int v, Edge & e){       // assign a new edge between 2 vertices
        g[u][v] = e;
    }
    void reset(int u, int v){             // clear the edge between 2 vertices
        g[u][v] = Edge(); 
    }
    map<int, Edge> & operator[](int v){      // a reference is returned
        return g[v];
    }
    Edge getWeight(int u, int v){      // return edge corresponding to 2 vertices
        if(g.find(u) != g.end() and g[u].find(v) != g[u].end()){
            return g[u][v];
        }
        return Edge();
    }
    void deleteVertex(int u){      // remove vertex from the graph
        for(auto it = g.begin(); it != g.end(); it++){
            it->second.erase(u);
        }
        g.erase(u);
    }
    vector<int> getVertices(){       // return all vertices
        vector<int> v;
        for(auto it : g){
            v.push_back(it.first);
        }
        return v;
    }
    friend ostream & operator<<(ostream & stream, Graph & g);
    friend ofstream & operator<<(ofstream & stream, Graph & g);
    friend istream & operator>>(istream & stream, Graph & g);
    friend ifstream & operator>>(ifstream & stream, Graph & g);
};

ostream & operator<<(ostream & stream, Graph & g){    
    for(auto it : g.g){
        stream<<it.first<<" ";
        for(auto e : it.second){
            stream<<e.first<<" "<<g[it.first][e.first]<<" ";
        }
        stream<<"-1 ";
    }
    stream<<"-2"<<endl;
    return stream;
}

ofstream & operator<<(ofstream & stream, Graph & g){    // operator to write graph into the file
    for(auto it : g.g){
        stream<<it.first<<" ";
        for(auto e : it.second){
            stream<<e.first<<" "<<g[it.first][e.first]<<" ";
        }
        stream<<"-1 ";
    }
    stream<<"-2"<<endl;
    return stream;
}

istream & operator>>(istream & stream, Graph & g){
    int c;
    while(stream>>c){
        if(c == -2){
            return stream;
        }
        g.addVertex(c);
        int d;
        while(stream>>d){
            if(d == -1){
                break;
            }
            Edge w;
            stream>>w;
            g.assignEdge(c, d, w);
        }
    }
}

ifstream & operator>>(ifstream & stream, Graph & g){
    int c;
    while(stream>>c){
        if(c == -2){
            return stream;
        }
        g.addVertex(c);
        int d;
        while(stream>>d){
            if(d == -1){
                break;
            }
            Edge w;
            stream>>w;
            g.assignEdge(c, d, w);
        }
    }
}

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
    Group(){         // constructor

    }
    Group(string name, int days, float finePercent){     // constructor
        this->name = name;
        this->days = days;
        this->finePercent = finePercent;
    }
    string getName(){                 // return group name
        return name;
    }
    int getDays(){              
        return days;
    }
    float getFinePercent(){
        return finePercent;
    }
    void add(T & p){                     // add person to group, check if person is already present or not
        if(ids.find(p) != ids.end()){
            cout<<"You are already part of this group"<<endl;
            return;
        }
        ids[p] = p.getID();
        rel[p.getID()] = p;
        group.addVertex(p.getID());
    }
    void seeDues(T & p){                // display dues of a person in the group
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
    void seeTransactions(T & p){       // view active payments done by the person in the group that is those that have not been paid back
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
    void removePerson(T & p){        // remove person from the group, check if the person has dues or other people have dues
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
    bool isInGroup(T & p){             // check membership in group
        return ids.find(p) != ids.end();
    }
    void getMembers(){               // show members of the group
        for(auto it : rel){
            cout<<it.first<<" "<<it.second.getName()<<endl;
        }
    }
    void pay(Person & p, float money){       // pay money for the group and add equal due for every person in the group
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
    void clearDuesAgainst(Person & p, int id){             //  clear due against a person against given id with given fine, cancel request if wallet does not have enough money
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
    float getDuesAgainst(Person & p, int id, bool print = true){      // return dues against person with added fine if applicable
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
    void clearDues(Person & p){    // clear dues against everyone in the group, cancel request if wallet does not have enough money
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
    int getSize(){     // return group size
        return ids.size();
    }
    void sortLeastDues(){         // sort group members according to increasing dues
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
    void sortMaxDues(){              // sort group members according to decreasing dues
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

Person findPerson(int id){
    ifstream in("Users.txt");
    Person p;
    while(in>>p){
        if(p.getID() == id){
            return p;
        }
    }
    in.close();
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
        p = findPerson(elem);
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
        p = findPerson(elem);
        g.ids[p] = p.getID();
        g.rel[p.getID()] = p;
    }
    return stream;
}

bool viewOrChangeBioData(Person & p){            // function to allow a person to change bio-data
    cout<<"We have the following data "<<endl;
    cout<<"\t\t\t\t\t\t\t\t\tName : "<<p.getName()<<endl;
    cout<<"\t\t\t\t\t\t\t\t\tAge : "<<p.getAge()<<endl;
    cout<<"\t\t\t\t\t\t\t\t\tDate Of Birth : "<<p.getDOB().day<<"/"<<p.getDOB().month<<"/"<<p.getDOB().year<<endl;
    cout<<"Do you want to modify your data ? (Y/N)"<<endl;
    char ch;
    cin>>ch;
    if(tolower(ch) == 'n'){
        return false;
    }
    ifstream in("Users.txt");
    ofstream out("Temp1");
    Person newP;
    while(in>>newP){
        if(newP.getID() == p.getID()){
            cout<<"ENTER YOUR DETAILS"<<endl;
            string name;
            Date DOB;
            int age;
            cout<<"Enter your name"<<endl;
            cin>>name;
            cout<<"Enter Date Of Birth (dd/mm/yyyy)"<<endl;
            int day, month, year;
            char ch1, ch2;
            cin>>day>>ch1>>month>>ch2>>year;
            DOB = Date(day, month, year);
            cout<<"Enter your age"<<endl;
            cin>>age;
            auto x = Person(p.getID(), name, DOB, age, p.getPassword());
            x.addMoney(p.getWallet().getMoney());
            newP = x;
        }
        out<<newP;
    }
    remove("Users.txt");
    rename("Temp1", "Users.txt");
    return true;
}

bool seeOrChangeWallet(Person & p){     // function to allow person to add and remove money from the wallet
    cout<<"Your Wallet contains "<<p.getWallet().getMoney()<<" money "<<endl;
    cout<<"Do you want to add or remove money ?(Y/N)"<<endl;
    char ch;
    cin>>ch;
    if(tolower(ch) == 'n'){
        return false;
    }
    cout<<"Enter 0 to add money"<<endl;
    cout<<"Enter 1 to remove money"<<endl;
    int choice;
    cin>>choice;
    cout<<"Enter the amount"<<endl;
    float amt;
    cin>>amt;
    while(amt < 0){
        cout<<"Enter a non negative amount"<<endl;
        cin>>amt;
    }
    if(choice == 0){
        p.addMoney(amt);
    }
    else {
        p.withdrawMoney(amt);
    }
    Person newP;
    ifstream in("Users.txt");
    ofstream out("Temp1");
    while(in>>newP){
        if(newP.getID() == p.getID()){
            newP = p;
        }
        out<<newP;
    }
    remove("Users.txt");
    rename("Temp1", "Users.txt");
    return true;

}

bool seeInfo(Person & p){    // function to allow person see personal information
    cout<<"Enter 0 to see or change Bio-Data"<<endl;
    cout<<"Enter 1 to see or change wallet"<<endl;
    cout<<"Enter 2 to exit"<<endl;
    int choice;
    cin>>choice;
    switch(choice){
        case 0 : return viewOrChangeBioData(p);
            break;
        case 1 : return seeOrChangeWallet(p);
            break;
        case 2 : return false;
    }
}

void newGroup(Person & p){   // function to create a new group, group name must be unique, add details for the group
    string name;
    bool check = false;
    do {
        check = false;
        cout<<"Enter the name of the group"<<endl;
        cin>>name;
        ifstream in("Groups");
        Group<Person> g;
        while(in>>g){
            if(g.getName() == name){
                cout<<"The group name is not available, please try again"<<endl;
                check = true;
                break;
            }
        }
        if(check == false){
            break;
        }
    }while(check);
    int days;
    float finePercent;
    cout<<"Enter the number of days after which you want to impose fine"<<endl;
    cin>>days;
    cout<<"Enter the percentage of fine to be imposed after "<<days<<" days"<<endl;
    cin>>finePercent;
    Group<Person> g(name, days, finePercent);
    g.add(p);
    ofstream out("Groups", ios::app);
    out<<g;
    out.close();
    cout<<"The group has succesfully formed and you have been added !!"<<endl;    

}

void enterGroup(Person & p){       // function to let person join group, all groups are public
    cout<<"Enter the name of the group you would want to enter"<<endl;
    string name;
    cin>>name;
    ifstream in("Groups");
    Group<Person> g;
    bool flag = false;
    while(in>>g){
        if(g.getName() == name){
            flag = true;
        }
    }
    in.close();
    if(flag == false){
        cout<<"Given Group Does Not Exist, Try Again"<<endl;
        return;
    }
    in.open("Groups");
    ofstream o("Temp");
    while(in>>g){
        if(g.getName() != name){
            o<<g;
        }
        else {
            g.add(p);
            o<<g;
        }
    }
    cout<<"You have been added successfully"<<endl;
    remove("Groups");
    rename("Temp", "Groups");
}

void leaveGroup(Person & p){     // function to let person leave group
    ifstream in("Groups");
    Group<Person> g;
    int count = 0;
    cout<<"You are part of the following groups"<<endl;
    while(in>>g){
        if(g.isInGroup(p)){
            cout<<g.getName()<<endl;
            count++;
        }
    }
    in.close();
    if(count == 0){
        cout<<"You are not part of any group"<<endl;
        return;
    }
    cout<<"Which group would you want to leave"<<endl; // put this in a do while loop
    string name;
    cin>>name;
    in.open("Groups");
    ofstream o("Temp");
    count = 0;
    while(in>>g){
        if(g.getName() == name){
            g.removePerson(p);
            count++;
        }
        o<<g;
    }
    if(count == 0){
        cout<<"Such A Group Does Not Exist"<<endl;
    }
    remove("Groups");
    rename("Temp","Groups");
}

void viewAlerts(Person & p){    // function to let person view alerts
   ifstream in("Groups");
   Group<Person> g;
   while(in>>g){
       if(g.isInGroup(p)){
           cout<<"In Group "<<g.getName()<<endl;
           g.seeDues(p);
       }
   }
}

void seePaymentHistory(Person & p){     // function to let person see active payment history
    ifstream in("Groups");
    Group<Person> g;
    while(in>>g){
        if(g.isInGroup(p)){
            cout<<"In Group "<<g.getName()<<endl;
            g.seeTransactions(p);
        }
    }
}

void viewGroups(){     // function to show all groups
    ifstream in("Groups");
    Group<Person> g;
    while(in>>g){
        cout<<g.getName()<<" "<<g.getSize()<<endl;
        g.getMembers();
    }
}

void makePayment(Person & p){    // function to allow person pay for a group
    ifstream in("Groups");
    cout<<"You are the member of the following groups"<<endl;
    int count = 0;
    Group<Person> g;
    while(in>>g){
        if(g.isInGroup(p)){
            cout<<g.getName()<<endl;
            count++;
        }
    }
    if(count == 0){
        cout<<"You are not part of any group"<<endl;
        return;
    }
    cout<<"Enter the name of the group in which you want to make payment"<<endl;
    string name;
    cin>>name;
    cout<<"Enter the amount of money you want to pay"<<endl;
    float money;
    cin>>money;
    if(money > p.getWallet().getMoney()){
        cout<<"You do not have enough money, add money to your wallet"<<endl;
        return;
    }
    else {
        p.withdrawMoney(money);
    }
    in.close();
    in.open("Groups");
    count = 0;
    ofstream o("Temp");
    while(in>>g){
        if(g.getName() == name){
            g.pay(p, money);
            count++;
        }
        o<<g;
    }
    remove("Groups");
    rename("Temp", "Groups");
    if(count == 0){
        cout<<"Such a group does not exist"<<endl;
        return;
    }
    ifstream In("Users.txt");
    ofstream out("Temp1");
    Person newP;
    while(In>>newP){
        if(newP.getID() == p.getID()){
            newP = p;
        }
        out<<newP;
    }
    remove("Users.txt");
    rename("Temp1", "Users.txt");
    cout<<"Payed Successfully"<<endl;
}

void payDues(Person & p){      // function to let person clear dues in a group
    ifstream in("Groups");
    Group<Person> g;
    int count = 0;
    cout<<"You are a part of the following groups"<<endl;
    while(in>>g){
        if(g.isInGroup(p)){
            cout<<g.getName()<<endl;
            count++;
        }
    }
    if(count == 0){
        cout<<"You are not part of any group"<<endl;
        return;
    }
    cout<<"Enter the name of the Group in which you want to clear your dues"<<endl;
    string name;
    cin>>name;
    in.close();
    in.open("Groups");
    count = 0;
    ofstream o("Temp");
    while(in>>g){
        if(g.getName() == name){
            g.getMembers();
            cout<<"Enter the id against whom you want to clear you dues, enter -1 to clear dues against everyone"<<endl;
            int id;
            cin>>id;
            if(id == -1){
                g.clearDues(p);
            }
            else {
                g.clearDuesAgainst(p, id);
            }
            count++;
        }
        o<<g;
    }
    if(count == 0){
        cout<<"Such a group does not exist"<<endl;
    }
    remove("Groups");
    rename("Temp", "Groups");
}

void getStats(Group<Person> & g){     // shows statistics of a particular group
    cout<<"Number of members in the group "<<g.getSize()<<endl;
    cout<<"The members are "<<endl;
    g.getMembers();
    cout<<"Number of days after which fine is applicable "<<g.getDays()<<endl;
    cout<<"Fine Percentage per day of the amount paid is "<<g.getFinePercent()<<"%"<<endl;
    cout<<"Enter 1 to see list in ascending order of dues"<<endl;
    cout<<"Enter 2 to see list in descending order of dues"<<endl;
    int choice;
    cin>>choice;
    switch(choice){
        case 1 : g.sortLeastDues();
                break;
        case 2 : g.sortMaxDues();
                break;
    }
}

void seeStatistics(Person & p){    // allows person to see statistcs of a particular group
    ifstream in("Groups");
    Group<Person> g;
    int count = 0;
    while(in>>g){
        if(g.isInGroup(p)){
            cout<<g.getName()<<endl;
            count++;
        }
    }
    if(count == 0){
        cout<<"You are not part of any group"<<endl;
        return;
    }
    cout<<"Enter the name of the group to see its statistics"<<endl;
    string name;
    cin>>name;
    in.close();
    in.open("Groups");
    count = 0;
    while(in>>g){
        if(g.getName() == name){
            getStats(g);
            count++;
        }
    }
    if(count == 0){
        cout<<"Such a group does not exist"<<endl;
    }
}



void run(Person & p){      // menu to let person run application
    while(true){
        cout<<"\t\t\t\t\t\t\t\t\tEnter 0 to view personal information "<<endl;
        cout<<"\t\t\t\t\t\t\t\t\tEnter 1 to make a new group"<<endl;
        cout<<"\t\t\t\t\t\t\t\t\tEnter 2 to enter a group"<<endl;
        cout<<"\t\t\t\t\t\t\t\t\tEnter 3 to leave a group"<<endl;
        cout<<"\t\t\t\t\t\t\t\t\tEnter 4 to see alerts"<<endl;
        cout<<"\t\t\t\t\t\t\t\t\tEnter 5 to view groups"<<endl;
        cout<<"\t\t\t\t\t\t\t\t\tEnter 6 to make payment"<<endl;
        cout<<"\t\t\t\t\t\t\t\t\tEnter 7 to pay dues"<<endl;
        cout<<"\t\t\t\t\t\t\t\t\tEnter 8 to view group statistics"<<endl;
        cout<<"\t\t\t\t\t\t\t\t\tEnter 9 to see your active payment history"<<endl;
        cout<<"\t\t\t\t\t\t\t\t\tEnter 10 to exit"<<endl;
        int choice;
        cin>>choice;
        switch(choice){
            case 0 : if(seeInfo(p)){
                        cout<<"We have commited the changes for security reasons please login again"<<endl;
                        return;
                    }
                    break;
            case 1 : newGroup(p);
                    break;
            case 2 : enterGroup(p);
                    break;
            case 3 : leaveGroup(p);
                    break;
            case 4 : viewAlerts(p);
                    break;
            case 5 : viewGroups();
                    break;
            case 6 : makePayment(p);
                    break;
            case 7 : payDues(p);
                    break;
            case 8 : seeStatistics(p);
                    break;
            case 9 : seePaymentHistory(p);
                    break;
            case 10 : return;
        }
    }
}

void login(){      // safe login into account with password
    int id;
    cout<<"Enter your user id"<<endl;
    cin>>id;
    string password = "";
    bool check = false;
    Person p;
    getPassword();
    do{ 
        int count = 0;
        ifstream in("Users.txt");
        while(in>>p){
            if(p.getID() == id){
                password = "";
                cout<<"Enter your password"<<endl;
                password = getPassword();
                count = 1;
                if(p.getPassword() == password){
                    check = true;
                    break;
                }
                else {
                    cout<<"Invalid Password, try again"<<endl;
                    break;
                }
            }
        }
        in.close();
        if(count == 0){
            cout<<"Your account does not exist, please create an account"<<endl;
            return;
        }
    }while(check == false);
    cout<<"\t\t\t\t\t\t\t\t\tWELCOME "<<p.getName()<<endl<<endl<<endl;
    run(p);
}

bool disclaimer(){    // display rules for using application
    cout<<"\t\t\t\t\t\t\t\t\tPlease Read The below Rules"<<endl;
    cout<<"\t\t\t\t\t\t\t\t\tYou will be given a unique ID, remember it and you can set the password only once"<<endl;
    cout<<"\t\t\t\t\t\t\t\t\tYou can change rest of the Bio-Data anytime you like"<<endl;
    cout<<"\t\t\t\t\t\t\t\t\tAll transactions in the application will take through an e-wallet handled by us, you can add and remove money at your will"<<endl;
    cout<<"\t\t\t\t\t\t\t\t\tIf you form a group, you are supposed to enter the number of days after which fine is imposed and the rate as well "<<endl;
    cout<<"\t\t\t\t\t\t\t\t\tyou cannot change this later"<<endl;
    cout<<"\t\t\t\t\t\t\t\t\tOnce a group is formed you cannot rename it again and the group name cannot be used again"<<endl;
    cout<<"\t\t\t\t\t\t\t\t\tWe will keep track of active payments of all the users, that is those that have not been payed back by others in the group"<<endl;
    cout<<"\t\t\t\t\t\t\t\t\tother payments that have been resolved will be removed from our database"<<endl;
    cout<<"Are you ready make an account ?(y/n)"<<endl;
    char choice;
    cin>>choice;
    if(tolower(choice) == '\n'){
        return false;
    }
    return true;
}

void createNew(){       // create a nre account of a person and add it into the file record
    if(!disclaimer()){
        return;
    }
    ifstream in("Users.txt");
    cout<<"ENTER YOUR DETAILS"<<endl;
    string name;
    Date DOB;
    int age;
    cout<<"Enter your name"<<endl;
    cin>>name;
    cout<<"Enter Date Of Birth (dd/mm/yyyy)"<<endl;
    int day, month, year;
    char ch1, ch2;
    cin>>day>>ch1>>month>>ch2>>year;
    DOB = Date(day, month, year);
    cout<<"Enter your age"<<endl;
    cin>>age;
    Person p;
    int mxId = 0;
    while(in>>p){   
        mxId = max(mxId, p.getID());
    }
    in.close();
    mxId++;
    cout<<"Your id is "<<mxId<<endl;
    string password = "";
    getPassword();
    do {
        password = "";
        cout<<"Enter password (minimum 4 characters):"<<endl;
        password = getPassword();
    }while(password.length() < 4);
    Person newP(mxId, name, DOB, age, password);
    ofstream out("Users.txt", ios::app);
    out<<newP;
    out.close();
    cout<<"Account created successfully !!!"<<endl;
}

int main(void){
    while(true){
        cout<<"\t\t\t\t\t\t\t\t\tWELCOME TO GROUP HANDLING SYSTEM"<<endl<<endl;;
        cout<<"\t\t\t\t\t\t\t\t\tEnter 0 to login"<<endl;
        cout<<"\t\t\t\t\t\t\t\t\tNew here ?"<<endl;
        cout<<"\t\t\t\t\t\t\t\t\tEnter 1 to make a new Account"<<endl;
        int op;
        cin>>op;
        switch(op){
            case 0 : login();
                      break;
            case 1 : createNew();
                      break;
        }
    }
    return 0;
}