all : GFH

GFH : Date.o Wallet.o TransactionRecord.o Edge.o Graph.o Person.o Group.o main.o
	g++ main.o Group.o Person.o Graph.o Edge.o TransactionRecord.o Wallet.o Date.o -o GFH

main.o : main.cpp
	g++ -c main.cpp

Group.o : Group.cpp
	g++ -c Group.cpp

Person.o : Person.cpp
	g++ -c Person.cpp

Graph.o : Graph.cpp
	g++ -c Graph.cpp

Edge.o : Edge.cpp	
	g++ -c Edge.cpp

TransactionRecord.o : TransactionRecord.cpp	
	g++ -c TransactionRecord.cpp

Wallet.o : Wallet.cpp
	g++ -c Wallet.cpp

Date.o : Date.cpp
	g++ -c Date.cpp

clean :
	rm -rf *o GFH