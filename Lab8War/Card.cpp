//
//  Card.cpp
//  Lab8War
//
//  Created by Barrett Wolf on 10/31/19.
//  Copyright © 2019 Barrett Wolf. All rights reserved.
//

#include "Card.hpp"
#include <iostream>
#include <list>
#include <queue>
#include <deque>
using namespace std;

Card::Card(int value_in) //constructor that takes in a value
{
    value=value_in;
}

int Card::getValue() //function that returns the value of the card
{
    return value; //returns value
}


