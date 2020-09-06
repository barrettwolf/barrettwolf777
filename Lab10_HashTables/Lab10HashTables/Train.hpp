//
//  Train.hpp
//  Lab10HashTables
//
//  Created by Barrett Wolf on 11/14/19.
//  Copyright © 2019 Barrett Wolf. All rights reserved.
//

#ifndef TRAIN_H
#define TRAIN_H
#include <string>
using namespace std;

class Train
{
public: //makes the train name and train number public and creates the constructor for the train
    string trainName;
    int trainNumber;
    Train(string name_in, int number_in);
    unsigned int hash(int tablesize); //declares hash that takes in a table size
};

ostream & operator << (ostream & out, Train * t); //declaration of the << operator 

#endif

