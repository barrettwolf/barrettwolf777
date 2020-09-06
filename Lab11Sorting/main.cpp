//
//  main.cpp
//  Lab11Sorting
//
//  Created by Barrett Wolf on 12/4/19.
//  Copyright © 2019 Barrett Wolf. All rights reserved.
//

#include <iostream>
#include <vector>
#include "sort.hpp"
using namespace std;

vector<int> vecReturn(int size_in,int seed_in) //function that returns a created int vector
{
    vector<int> intvector; //creation of the int vector
    
    for(int i=0;i<size_in;i++) //for loop that runs as many times as the vectors size
    {
        intvector.push_back(i); //adds the same value as the index to the vector
    }
    
    srand(seed_in); //setting srand to the seed entered
    int q; //instantiation of q
    int tempint=0; //initializing the temporary int
    
    for(int i=0;i<size_in;i++) //for loop that will shuffle the vector
    {
        q=rand()%size_in; //making q a random number
        tempint= intvector.at(i); //setting vector index at i to a temp int
        intvector.at(i)= intvector.at(q); //setting index at i to index at q
        intvector.at(q)= tempint; //index at q is set to the temp int
    }
    
    return intvector; //returns the int vector
}

int getInv(vector<int> intvector_in, int vecsize) //function that returns the number of inversions
{
    int invcount = 0; //setting count to 0
    for (int i=0;i<vecsize-1;i++) //
    {
        for (int j=i+1;j<vecsize;j++)
        {
            if (intvector_in.at(i) > intvector_in[j]) //if the index at i is greater than at j
            {
                invcount++; //increase the inversion count
            }
        }
    }
  
    return invcount; //returns the inversion count
}

int main()
{
    int size=0,seed=0; //creating the size and seed ints
    cout << "How large of a list would you like to create? :"; //asking the user for size and seed inputs
    cin >> size;
    cout << "What random seed would you like to use? :";
    cin >> seed;
    
    vector<int> intvector = vecReturn(size,seed); //setting a vector to the vecReturn function
    cout << "\nTotal inversions in the original list :" << getInv(intvector,size); //total inversions
    long long before= getTime(); //making a before time before sort function is called
    insertionSort(intvector); //calls the sort function on the vector
    long long after= getTime(); //making an time for after the sort function is called
    long long time= after-before; //setting time to the time elapsed between the two
    cout << "\nInsertion sort time :" << time; //prints the total time that it took
    cout << "\nTotal inversions after insertion sort :" << getInv(intvector,size); //prints total inversions after sorting is done
    
    
}
