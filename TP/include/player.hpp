// player.hpp
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "deck.hpp"

class player{
    private : 
        int playerId, credit, bet ; 
        deck hand ;  

    public : 
        player() ; 
        player(int i) ; 

        int getId() const ; 
        int getCredit() const ; 
        int getBet() const ; 
        int HandSum() const ; 
        int HandLenght() const ; 

        void setBet() ; 
        void resetBet() ; 
        void setCredit() ;
        void setCredit(int) ; 
        void makeDealer() ; 
        void playerInfo() ; 
        void printHand() ; 
        void actualiseCredit() ; 
        void actualiseCredit(int) ; 
        void freeHand(deck &discard) ;
        void play(deck &fromdeck,deck &discard) ; 
        void playDealer(deck &fromdeck,deck &discard) ; 
        void appendHand(deck &fromdeck, deck &discard) ; 
}; 

#endif