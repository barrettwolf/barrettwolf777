//
//  main.cpp
//  Lab8War
//
//  Created by Barrett Wolf on 10/31/19.
//  Copyright © 2019 Barrett Wolf. All rights reserved.
//

#include "Card.hpp"
#include "Shuffle.hpp"
#include <iostream>
#include <queue>

using namespace std;
int main()
{
    queue <Card> deck1; //instantiating the first deck queue
    queue <Card> deck2; //instantiating the second deck queue
    int seed; //instantiaing seed and setting both counts to 0
    bool player1war=false,player2war=false; //booleans for winning the war and setting them to false
    vector<Card> tempcardvect; //making the card vector
    
    for(int i=0;i<13;i++) //for loop for all 13 value needed for the deck (0-12)
    {
        for(int j=0;j<2;j++) //for loop that will make two cards of each value
        {
            Card c= Card(i); //making a card with the value i
            deck1.push(c); //adding each card to deck1
        }
    }
    
    for(int i=0;i<13;i++) //for loop for all 13 value needed for the deck (0-12)
    {
        for(int j=0;j<2;j++) //for loop that will make two cards of each value
        {
            Card c= Card(i); //making a card with the value i
            deck2.push(c); //adding each card to deck2
        }
    }
    
    cout << "What seed would you like?: "; //asking the user for a seed input
    cin >> seed; //runs in the seed
    srand(seed); //sets srand to the seed input
    
    Shuffle(deck1); //shuffles deck1
    Shuffle(deck2); //shuffles deck2
    
    while(deck1.empty() != true && deck2.empty() != true) //while both decks are not empty
    {
        //prints deck1 front vs deck2 front
        cout << deck1.front().getValue() << " vs " << deck2.front().getValue() << "\n"; //prints versus
        if(deck1.size()>1 && deck2.size()>1)
        {
            if(deck1.front().getValue()>deck2.front().getValue()) //when deck1 front > deck2 front
            {
                Card vs1= Card(deck1.front().getValue()); //makes a card of the deck1 battle
                Card vs2= Card(deck2.front().getValue()); //makes a card of the deck2 battle
                deck1.pop(); //removes the front of deck1
                deck2.pop(); //removes the front of deck2
                deck1.push(vs1); //adds first card to deck1
                deck1.push(vs2); //adds second card to deck1
            }
            
            else if(deck2.front().getValue()>deck1.front().getValue()) //when deck2 front > deck1 front
            {
                Card vs1= Card(deck1.front().getValue()); //makes a card of deck1 battle
                Card vs2= Card(deck2.front().getValue()); //makes a card of deck2 battle
                deck1.pop(); //removes the front of deck1
                deck2.pop(); //removes front of deck2
                deck2.push(vs1); //adds first card to deck2
                deck2.push(vs2); //adds the second card to deck2
            }
            
            else if(deck1.front().getValue()==deck2.front().getValue()) //if the fronts of the deck are equal
            {
                cout << "WAR!!!" << "\n"; //prints WAR!!!
                
                while(deck1.front().getValue()==deck2.front().getValue()) //if the values at the front are still the same
                {
                    Card tiewinner= Card(-1); //instantiates the cards with values as -1
                    Card tieloser= Card(-1);
                    Card deck1card1= Card(-1);
                    Card deck1card2= Card(-1);
                    Card deck2card1= Card(-1);
                    Card deck2card2= Card(-1);
                    player1war=false; //setting the booleans to false every time the while loops
                    player2war=false;
                    
                    Card tie1= Card(deck1.front().getValue()); //sets deck1 card that tied to a card
                    Card tie2= Card(deck2.front().getValue()); //sets deck2 card that tied to a card
                    deck1.pop(); //removes the tied card from deck1
                    deck2.pop(); //removes the tied card from deck2
                    tempcardvect.push_back(tie1); //push the cards to the vector
                    tempcardvect.push_back(tie2);
                    
                    if(deck1.size()>=2) //when there are enough cards to go through war in deck1
                    {
                        cout << "facedown player1: " << deck1.front().getValue() << "\n"; //prints the first facedown card from deck1
                        deck1card1= Card(deck1.front().getValue()); //makes the facedown player the front of the deck
                        deck1.pop(); //removes the front of deck1
                        tempcardvect.push_back(deck1card1); //push deck1card1 to the vector
                    }
                    
                    if(deck1.size()>=2) //making sure that theres still enough cards for war in deck1
                    {
                        cout << "facedown player1: " << deck1.front().getValue() << "\n"; //prints the  second facedown player for deck1
                        deck1card2= Card(deck1.front().getValue()); //makes the facedown card the front of the deck
                        deck1.pop(); //removes the front of deck1
                        tempcardvect.push_back(deck1card2); //push deck1card2 to the vector
                    }
                    
                    if(deck2.size()>=2) //making sure that there is enough cards for war in deck2
                    {
                        cout << "facedown player2: " << deck2.front().getValue() << "\n"; //prints first facedown card from deck2
                        deck2card1= Card(deck2.front().getValue()); //makes the first facedown card the front of the deck
                        deck2.pop(); //removes the front of deck2
                        tempcardvect.push_back(deck2card1); //push deck2card1 to the vector
                    }
                    if(deck2.size()>=2) //making sure that there is still enough cards for war in deck2
                    {
                        cout << "facedown player2: " << deck2.front().getValue() << "\n"; //prints the second facedown card from deck2
                        deck2card2= Card(deck2.front().getValue()); //makes the second facedown card the front of the deck
                        deck2.pop(); //removes the front of deck2
                        tempcardvect.push_back(deck2card2); //push deck2card2 to the vector
                    }
                    tiewinner= Card(deck1.front().getValue()); //makes tiewinner the front of deck1
                    deck1.pop(); //removes front of deck1
                    tieloser= Card(deck2.front().getValue()); //makes tiewinner the front of deck2
                    deck2.pop(); //removes deck2 front and decreases count2
                    tempcardvect.push_back(tiewinner); //pushes the final vs to the vector
                    tempcardvect.push_back(tieloser);
                    cout << "--" << deck1.front().getValue() << " vs " << deck2.front().getValue() << "--" << "\n";
                    if(deck1.front().getValue()>deck2.front().getValue()) //if the front of deck1 > front of deck2
                    {
                        player1war=true; //set player1war to true
                    }
                    
                    if(deck2.front().getValue()>deck1.front().getValue()) //if the front of deck2 is greater that deck1
                    {
                        player2war=true; //set player2war to true
                    }
                }
                if(player1war==true) //if player1war is true after the while loop
                {
                    for(int i=0; i<tempcardvect.size();i++) //empties the vector and puts it in deck1
                    {
                        deck1.push(tempcardvect.at(i));
                    }
                }
                if(player2war==true) //if player2war is true after the while loop
                {
                    for(int i=0; i<tempcardvect.size();i++) //empties the vector and puts it in deck2
                    {
                        deck2.push(tempcardvect.at(i));
                    }
                }
            }
            tempcardvect.clear();
        }
        else if(deck1.size()==1) //else for if deck1 size equals 1 when it goes into war
        {
            Card deck1nowar = Card(deck1.front().getValue());
            deck1.pop(); //removes the last card in deck1
            deck2.push(deck1nowar); //taking the card from deck1 and putting it into deck2
            
        }
        else if(deck2.size()==1) //else for if deck2 size equals 1 when it goes into war
        {
            Card deck2nowar = Card(deck2.front().getValue());
            deck2.pop(); //removes last card in deck2
            deck1.push(deck2nowar); //taking card from deck2 and putting it into deck1
        }
        if(deck1.empty()==true) //if deck 1 is empty
        {
            cout << "Player 2 wins!!"; //player two wins
            break; //breaks the while loop
        }
        
        if(deck2.empty()==true) //if deck2 is empty
        {
            cout << "Player 1 wins!!"; //player one wins
            break; //breaks the while loop
        }
    }
}
