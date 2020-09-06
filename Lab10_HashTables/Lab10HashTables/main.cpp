//
//  main.cpp
//  Lab10HashTables
//
//  Created by Barrett Wolf on 11/14/19.
//  Copyright © 2019 Barrett Wolf. All rights reserved.
//

#include <iostream>
#include "Train.hpp"
#include "HashTable.hpp"
using namespace std;

int main()
{
    Train* train1= new Train("4-4-2",343); //creation of the three initial trains
    Train* train2= new Train("2-8-0",344);
    Train* train3= new Train("4-0-4",345);

    HashTable ht= HashTable(); //instantiates a new hash table
    ht.print(); //prints the hash table with no trains
    cout << "\n";
    
    ht.insert(train1); //inserting the created trains into the hash table
    ht.insert(train2);
    ht.insert(train3);
    
    cout << "original print:" << "\n";
    ht.print(); //prints the table with the three trains
    cout << "\n";
    
    ht.insert(train1); //inserts trains again
    ht.insert(train2);
    ht.insert(train3);
    cout << "print after adding same three again:" << "\n";
    ht.print(); //prints the table after trying to add the same three trains
    cout << "\n";
    
    Train* train4= new Train("2-8-0",1); //creating a ton of new trains
    Train* train5= new Train("2-8-0",2);
    Train* train6= new Train("2-8-0",3);
    Train* train7= new Train("12-0-0",42);
    Train* train8= new Train("12-0-12",84);
    Train* train9= new Train("2-2",2);
    Train* train10= new Train("4-4",4);
    
    ht.insert(train4); //inserting the created trains to the hash table
    ht.insert(train5);
    ht.insert(train6);
    ht.insert(train7);
    ht.insert(train8);
    ht.insert(train9);
    ht.insert(train10);
    cout << "print after adding more trains: \n";
    ht.print(); //printing after adding more trains
    cout << "\n";
    
    cout << "print after deleting the trains: \n";
    ht.remove(train1); //removing the first three trains
    ht.remove(train2);
    ht.remove(train3);
    ht.print(); //prints after removing
    
}
