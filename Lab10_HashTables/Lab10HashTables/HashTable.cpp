//
//  HashTable.cpp
//  Lab10HashTables
//
//  Created by Barrett Wolf on 11/14/19.
//  Copyright © 2019 Barrett Wolf. All rights reserved.
//

#include "HashTable.hpp"
#include <iostream>
#include <vector>
using namespace std;

HashTable::HashTable() //constructor for hash table that sets the number of entries=0 and tablesize=2
{
    numofentries = 0;
    sizeoftable = 2;
    
    trainvector.resize(sizeoftable); //resizes the vector as the size of the table
}

bool HashTable::insert(Train* t) //method for inserting a tree into the table
{
    int index= t->hash(sizeoftable); //making the index the size of the table
    
    bool inlist= false; //creates a bool for if the train is in the table
    bool addedtrain= false; //creates a bool for if the train is added
    
    for(int i=0;i< trainvector.at(index).size(); i++) //for loop that runs through the list and each vector
    {
        if(trainvector.at(index).at(i)->trainName == t->trainName && trainvector.at(index).at(i)->trainNumber == t->trainNumber) //checking if the train is already in the lists
        {
            inlist= true; //setting the inlist boolean to true
        }
    }
    
    if(inlist==false) //if the train is not in a list
    {
        vector<Train*>::iterator it; //creates an iterator
        it= trainvector.at(index).begin(); //iterator that is set to the beginning of the list
        trainvector.at(index).insert(it,t); //inserting the train at the beginning of the list
        numofentries++; //increases the number of entries
        addedtrain=true; //setting the added train bool to true
    }
    
    if(numofentries > sizeoftable*2) //if the number of entries is greater than 2* the size of table
    {
        cout << "rehashing yo table" << "\n";
        rehash(); //rehashes the table
    }
    return addedtrain; //returns the boolean
}

void HashTable::print() //print method
{
    cout << trainvector; //prints the entire list
}

ostream & operator << (ostream & out, vector<vector<Train*>> tv) //overriding of the << operator
{
    for(int i=0; i<tv.size();i++) //for loop that runs through the list
    {
        out << i << ": "; //prints i:
        for(int j=0; j<tv.at(i).size();j++) //prints the trains through the entire list
        {
            out << tv.at(i).at(j) << "   "; //prints the train information followed by some spaces
        }
        out << "\n"; //next line for the new hash level
    }
    return out; //returns the string
}

bool HashTable::find(Train* t) //method for finding a train in a list
{
    int index= t->hash(sizeoftable); //setting the index to the size of the table
    bool trainfound= false; //setting the bool for finding the train to false
    
    for(int i=0;i< trainvector.at(index).size(); i++) //looping through every train
    {
        if(trainvector.at(index).at(i)->trainName == t->trainName && trainvector.at(index).at(i)->trainNumber == t->trainNumber) //if the train is in the list
        {
            trainfound= true; //sets the boolean of finding the train to true
        }
    }
    return trainfound; //returns the bool
}

void HashTable::remove(Train* t) //removing a train from the hash table
{
    int index= t->hash(sizeoftable); //setting the index to the size of the table
    if(find(t) ==true) //if find(t) is true
    {
        for(int i=0;i< trainvector.at(index).size(); i++) //for loop that runs through the entire list
        {
            if(trainvector.at(index).at(i)->trainName == t->trainName &&  trainvector.at(index).at(i)->trainNumber == t->trainNumber) //checking which index the train is at
            {
                vector<Train*>::iterator it; //making an iterator
                it= trainvector.at(index).begin(); //setting the iterator to the beginning of the list
                trainvector.at(index).erase(it + i); //erasing the train at the index
            }
        }
    }
}

void HashTable::rehash() //method for rehashing the table
{
    vector<Train*> tempvect; //creating the tempvect
    
    for(int i=0; i<trainvector.size();i++) //running through every index of the list
    {
        for(int j=0; j<trainvector.at(i).size();j++)
        {
            tempvect.push_back(trainvector.at(i).at(j)); //adds each train to the temp vector
        }
    }
    
    trainvector.clear(); //clears the vector
    sizeoftable= sizeoftable*2; //sets the size of the table to the sizeoftable*2
    trainvector.resize(sizeoftable); //resizing the hash table
    numofentries=0; //setting the num of entries to 0
    
    for(int i=0;i<tempvect.size();i++) //for loop that runs through the entire tempvect
    {
        insert(tempvect.at(i)); //inserting the trains from tempvect to the original hash table
    }
    
    
}
