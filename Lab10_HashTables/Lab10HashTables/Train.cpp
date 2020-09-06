//
//  Train.cpp
//  Lab10HashTables
//
//  Created by Barrett Wolf on 11/14/19.
//  Copyright © 2019 Barrett Wolf. All rights reserved.
//

#include "Train.hpp"
#include <iostream>
using namespace std;

Train::Train(string name_in, int number_in) //train constructor that takes in a name and number
{
    trainNumber = number_in;
    trainName = name_in;
}
unsigned int Train::hash(int tablesize) //hash function for the trains
{
    unsigned int value = trainNumber;
    for (int i = 0; i<trainName.size(); i++) //for loop that hashes the train into the list
    {
        value += (trainNumber + 11) * value + trainName[i];
    }
    return value % tablesize;
}
ostream &operator << (ostream & out, Train* t) //defines the << operator
{
    out << t->trainName << " " << t->trainNumber;
    return out;
}
