//player.cpp

#include "player.hpp"

// Constructeurs

player::player(){}

player::player(int i){
    playerId = i ; 
    credit = 0 ; 
    bet = 0 ; 
}

// Methodes const

int player::getId() const {
    return playerId ; 
}

int player::getCredit() const {
    return credit ; 
}

int player::getBet() const{ 
    return bet ; 
}

int player :: HandSum() const {
    int sum = hand.getSumValue() ; 
    return sum ; 
}

int player :: HandLenght() const{
    return hand.deckLenght() ; 
}

// Méthodes autres

void player::setBet(){
    int b ; 
    cout << "Mise de départ (>=10) : " ; 
    cin >> b ; 
    while ( b < 10 || credit < b ) {
        cout << "Mise invalide : mise < 10 ou mise > credit ! : " ; 
        cin >> b ; 
    }
    bet = b ; 
    actualiseCredit() ;
}

void player::resetBet() {
    bet = 0 ;
}

void player::setCredit() {
    int c ; 
    cout << "Credit de départ (>= 10) : " ; 
    cin >> c ; 
    while (c < 10) {
        cout << "Erreur. Le credit doit être supérieur à 10 : " ; 
        cin >> c ; 
        cout << endl ; 
    }    
    credit = c ; 
}

void player :: setCredit(int c) {
    credit += c ; 
}

void player::makeDealer() {
    credit = -1 ;
    bet = -1 ; 
}

void player::playerInfo() {
    if (playerId == 0){
    cout << "Croupier : \nHand : " ; 
    hand.printDeck() ; 
    int sum = HandSum() ; 
    if (sum > 0){
        cout << "-> " << sum << " pts." ; 
    }
    cout << endl << endl ;
    }
    else{
    cout << "Joueur[" << playerId << "] : credit = " << credit << " et mise = " << bet << ".\nHand : " ; 
    hand.printDeck() ; 
    int sum = HandSum() ; 
    if (sum > 0){
        cout << "-> " << sum << " pts." ; 
    }
    cout << endl << endl  ;
    }
     
} 

void player::printHand() {
    cout << "Hand : " ;
    hand.printDeck() ; 
    cout << "-> " << HandSum() << " pts." ; 
    cout << endl << endl ; 
} 

void player::actualiseCredit() {
    credit = credit-bet ; 
}

void player::actualiseCredit(int b) {
    credit = credit - b  ; 
}

void player::freeHand(deck &discard){
    while (!hand.isDeckEmpty()){
        discard.appendCard(hand) ; 
    }
}

void player::play(deck &fromdeck, deck &discard) {
    int sum = HandSum() ; 
    int cond = 0 ; 
    if (sum == 0) {
        appendHand(fromdeck,discard) ; 
        appendHand(fromdeck,discard) ; 
        sum = HandSum() ; 
    }
    if(sum == 21){
        cout << "->! Blackjack !<- " << endl ; 
        cond = 1 ; 
    }
    while (sum < 21 && cond == 0){
        if(credit == 0 || credit-(bet*2) < 0)
        {
            int choice ; 
            // Case 1 : Pick or lay
            cout << "1) : Piocher une carte." << endl << "2) : Stop." << endl ; 
            cin >> choice ; 
            while (choice != 1 && choice != 2){
                cout << "Erreur de choix : " ;
                cin >> choice ; 
            }
            if (choice == 1){
                appendHand(fromdeck, discard) ; 
                sum = HandSum() ; 
                printHand() ; 
                if (sum > 21){
                    cond = 1 ;
                }
            }
            else {
                cond = 1 ;
            }
        }
        else {
            int choice ; 
            // Case 1 : Pick or lay
            cout << "1) : Piocher une carte." << endl << "2) : Stop." << endl << "3) : Doubler la mise." << endl  ; 
            cin >> choice ; 
            while (choice != 1 && choice != 2 && choice != 3){
                cout << "Erreur de choix : " ;
                cin >> choice ; 
            }
            if (choice == 1){
                appendHand(fromdeck, discard) ; 
                sum = HandSum() ; 
                printHand() ; 
                if (sum > 21){
                    cond = 1 ;
                }
            }
            else {
                if(choice == 2){
                    cond = 1 ; 
                }
                else{
                    bet *= 2 ; 
                    actualiseCredit(bet/2) ; 
                    appendHand(fromdeck, discard) ; 
                    sum = HandSum() ;
                    cond = 1 ; 
                    printHand() ; 
                }
            }
        }
    }
}

void player :: playDealer(deck &fromdeck,deck &discard){
    int sum = HandSum() ; 
    while (sum <= 16){
        appendHand(fromdeck, discard) ; 
        sum = HandSum() ; 
    }
    printHand() ; 
}

void player::appendHand(deck &fromdeck, deck &discard){
    hand.appendCard(fromdeck,discard) ; 
}
