// deck.hpp
#ifndef DECK_HPP
#define DECK_HPP

#include "card.hpp"

class deck{
    private : 
        vector<card> v ; 

    public : 
        deck() ; 
        deck(int i, int j, int k) ; 
        
        void shuffleDeck(deck &discard) ; // Mélange un deck vide avec une défausse. 
        void printDeck() const ; // Affiche la main d'un joueur. 
        void appendCard(deck &fromdeck) ; // Cas où on vide les cartes dans la défausse. 
        void appendCard(deck &fromdeck, deck &discard) ; // Cas où on prends dans la pile de cartes
        bool isDeckEmpty() const ; 
        int deckLenght() const ; 
        int getSumValue() const ; 
        unsigned long int getSize() const ; 
        
}; 

#endif 