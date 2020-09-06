//
//  Card.hpp
//  Lab8War
//
//  Created by Barrett Wolf on 10/31/19.
//  Copyright © 2019 Barrett Wolf. All rights reserved.
//

#ifndef Card_hpp
#define Card_hpp
#include <iostream>
#include <list>
#include <queue>
#include <deque>
using namespace std;

class Card
{
public:
    Card(int value_in); //constructor that takes in a value
    int getValue(); //function that returns a value
private:
    int value; //making the value a private var so it cannot be changed
};

#endif
