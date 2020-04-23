# Group-Finance-Handler

## Introduction
The application is intended for use as a group finance handler.

People can form groups in the application and the software handles the various transactions taken in the group.

Any person can make payments for the group (investment, social gatherings) without caring against whom they have positive or negative balances.

The application adds the dues to the other people.

People can view their alerts any time they like.

The application requires every one to have an e-wallet to handle transactions.

The people can easily clear dues and fines are automatically handled if applicable.

## Files
The Application contains the following files (I have attached the application in 2 formats) - 

1) OOAIAProject.cpp - The main application program (All code in single file and can be run through single compilation)

2) The source code distributed in the following files -
    
    a) main.cpp - the driver of the application
    
    b) Group.cpp and Group.h - Source code and header file to implement the group class
    
    c) Person.cpp and Person.h - Source code and header file to implement the person class
    
    d) Graph.cpp and Graph.h, Edge.cpp and Edge.h - These files contains classes implementing the dynamic directed graph used       by the application
    
    e) TransactionRecord.cpp and TransactionRecord.h - Source code and header file to implement the TransactionRecord class
    
    f) Wallet.cpp and Wallet.h - Source Code and header file to implement the transcation account
    
    g) Date.cpp and Date.h - Source Code and header file to handle Dates

There are 2 additional files shown here for reference and need not be present in the Directory (The application will create one) -

1)   Groups - File containing record of all groups in the application

2) Users.txt - File containing record of all persons having an account in the application

## Run Command

Make sure all the required files are present in the same directory

1) To execute format 1 use the command -

    Compile with the command - g++ OOAIAProject.cpp -o OOAIAProject

    Note - The application runs only on linux environment and g++17 compiler

    To execute write the command - ./OOAIAProject
 
 2) To execute format 2 use the command -
    
    Use the command -$ make
    
    This will generate the executable - GFH
    
    Run the application with the command -$ ./GFH
    
    To clean all binary files use -$ make clean 
