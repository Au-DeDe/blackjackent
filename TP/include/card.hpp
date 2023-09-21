// card.hpp
#ifndef CARD_HPP
#define CARD_HPP

#include <iostream>
#include <string>
#include <vector>
#include <algorithm> 
#include <ctime> 

using namespace std ; 

extern const char *symbols[4]; 
extern string c_name[13] ;

class card{
    private : 
        int value, color ; 

    public : 
        card(int i, int c) ; 
        card() ; 

        int getValue() const; 
        int getColor() const ;
        void printCard() const;
} ;


#endif