//
//  HashTable.hpp
//  Lab10HashTables
//
//  Created by Barrett Wolf on 11/14/19.
//  Copyright © 2019 Barrett Wolf. All rights reserved.
//

#ifndef HashTable_hpp
#define HashTable_hpp

#include <iostream>
#include "Train.hpp"
#include <vector>
using namespace std;

class HashTable
{
public: // declares all of the needed constructors and methods
    HashTable();
    bool insert(Train* t);
    void print();
    bool find(Train* t);
    void remove(Train* t);
    void rehash();
private: //declares all of the needed variables 
    int numofentries;
    int sizeoftable;
    vector<vector<Train*>> trainvector;
};

ostream & operator << (ostream & out, vector<vector<Train*>> tv);

#endif /* HashTable_hpp */
