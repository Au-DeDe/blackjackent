//deck.cpp

#include "deck.hpp" 

// Constructeurs
deck::deck () {
}

deck::deck(int ic, int jc, int kc){
    int i, j, k ; 
    for (k = 0 ; k < kc ; k++) { // k = 6
        for (j = 0 ; j < jc ; j ++) { // j = 4
            for (i = 0 ; i < ic ; i ++) { // i = 13
                v.push_back(card(i+1,j)) ;
            }
        }
    }
}

// Methodes. 

void deck :: shuffleDeck(deck &discard){
    if (discard.getSize() < 1){ // In case discard is empty
        cout << "Discard is empty" << endl ; 
        exit(1) ;
    }
    srand(time(nullptr)) ; 
    while(!discard.v.empty()) {
        int rdm = rand() % discard.v.size() ;  
        iter_swap(discard.v.begin()+rdm,discard.v.end()-1) ; 
        v.push_back(discard.v.back()) ; 
        discard.v.pop_back() ;         
    }
    // Now we discard 3 cards. 
    for(int i = 0; i < 3 ; i++){
        discard.v.push_back(v.back()) ; 
        v.pop_back() ; 
    }
}

void deck :: printDeck() const{
    if(v.size() < 1){
        cout << " / " ; 
    }
    for(unsigned long int i = 0; i < v.size(); i++)
    {
        v[i].printCard() ;
    }
}

void deck :: appendCard(deck &fromdeck) { // Version ou on DEFAUSSE
    v.push_back(fromdeck.v.back()) ;
    fromdeck.v.pop_back() ; 
}

void deck :: appendCard(deck &fromdeck, deck &discard) { // version où on ne veut pas PIOCHE
    if (fromdeck.v.size() == 0) {
        // On ne peux pas piocher, on remélange le deck
        fromdeck.shuffleDeck(discard) ;
        cout << "! Le croupier mélange le deck !" << endl ; 
    }
    v.push_back(fromdeck.v.back()) ;
    fromdeck.v.pop_back() ; 
}

bool deck :: isDeckEmpty() const{
    if(v.empty())
        return 1 ; 
    else 
        return 0 ; 
}

int deck :: deckLenght() const {
    return v.size() ; 
}

int deck :: getSumValue() const {
    int sum = 0 ; 
    for(unsigned long int i = 0; i < v.size(); i++)
    {   
        if(v[i].getValue() >= 10){
            sum+= 10 ; 
        }
        else{
            if(v[i].getValue() == 1){
                if ((sum + 11) <= 21){
                    sum += 11 ; 
                }
                else {
                    sum+= 1 ; 
                }        
            }
            else {
                sum += v[i].getValue() ;
            }
        }
    }
    return sum ; 
}

unsigned long int deck :: getSize() const  {
    return v.size() ; 
}




