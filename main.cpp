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
#include "Group.cpp"

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


class Comparator{           // comparator for sorting aggregate of pair class objects
public :
    bool operator()(const pair<int, int> & p1, const pair<int, int> & p2){
        return p1.first < p2.first;
    }
};


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

void checkDues(Person & p){
    ifstream in("Groups");
    Group<Person> g;
    int count = 0;
    while(in>>g){
        if(g.isInGroup(p)){
            if(g.checkDues(p)){
                count++;
            }
       }
    }
    if(count > 0){
        cout<<"\t\t\t\t\t\t\t\t\tNOTIFICATION - You have dues in "<<count<<" Groups, kindly see your alerts"<<endl<<endl;
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
    checkDues(p);
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
    if(tolower(choice) == 'n'){
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
        cout<<"\t\t\t\t\t\t\t\t\tWELCOME TO GROUP FINANCE HANDLING SYSTEM"<<endl<<endl;;
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