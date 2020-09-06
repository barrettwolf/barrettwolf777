//
//  Shuffle.cpp
//  Lab8War
//
//  Created by Barrett Wolf on 11/4/19.
//  Copyright © 2019 Barrett Wolf. All rights reserved.
//

#include <iostream>
using namespace std;
#include "Shuffle.hpp"

void Shuffle(queue <Card>& q) //function takes in a queue
{
    vector <int> cardvect; //creates a new vector of ints
    int tovect=0,temp=0; //instantiating the two temps needed both to 0
    
    for(int i=0;i<26;i++) //for loop that adds the values of cards to the vector
    {
        tovect= q.front().getValue(); //sets the value of the first card to temp variable
        cardvect.push_back(tovect); //adds value of the card to the vector
        q.pop(); //removes the card from the queue
    }
    //where the actual shuffling occurs
    for(int i=0;i<26;i++) //for loop that runs through all indexes using i
    {
        for(int j=0;j<26;j++) //for loop that runs through all indexes using i
        {
            if(rand()%2==0) //if the random number is divisible by two
            {
                temp=cardvect.at(i); //setting the temp value to i
                cardvect.at(i)=cardvect.at(j); //setting i to j
                cardvect.at(j)=temp; //setting j to the temp so the original i
            }
        }
    }
    
    for(int i=0;i<26;i++) //for loop for adding the ints in the vector back to the queue of cards
    {
        Card c= Card(cardvect.at(i)); //makes a card based off the value
        q.push(c); //adds the card to the queue
    }
}
