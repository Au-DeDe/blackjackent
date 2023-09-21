// card.cpp

#include "card.hpp"

// constructeurs

card::card(int i, int c) {
    value = i ;
    color = c ;
}

card::card() {
    value = -1 ; 
    color = -1 ; 
}

// Methodes

int card::getValue() const{
    return value ; 
}

int card::getColor() const{
    return color ; 
}

void card::printCard() const{
    std::cout << c_name[value-1] << "[" << symbols[color] << "] " ; 
}