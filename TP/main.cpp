// main.cpp 

#include "card.hpp"
#include "deck.hpp"
#include "player.hpp"
#include <limits>

const char *symbols[4] = {"♥", "♦", "♣", "♠"} ; 
string c_name[13] = {"Ace","2","3","4","5","6","7","8","9","10","Jack","Queen","King"} ;

deck initializeDiscard() {
    deck d = deck(13,4,6) ; 
    return d ; 
}

int getNbOfPlayers() {
    int n ; 
    cout << "Nombre de joueurs : "  ; 
    cin >> n ; 
    cout << endl ; 
    while(n < 1){
        cout << "Erreur. Veuillez renseigner un nombre supérieur à 0 : "; 
        cin >> n ; 
        cout << endl ;  
    }
    return n ; 
}

vector<player> initializePlayers() {
    vector<player> vp ; 
    vp.push_back(player(0)) ; 
    vp.back().makeDealer() ; 
    int nbOfPlayers = getNbOfPlayers() ; 
    for (int i = 1 ; i < nbOfPlayers+1 ; i++) {
        vp.push_back(player(i)) ; 
    }
    return vp ; 
}

void setCredit(vector<player> &v){
     for (long unsigned int i = 1; i < v.size() ; i++){
        cout << "Joueur[" << v[i].getId() << "] :" ; 
        v[i].setCredit() ; 
    }
}

void setBet(vector<player> &v){
    for (long unsigned int i = 1; i < v.size() ; i++){
        cout << "Joueur[" << v[i].getId() << "] :" ; 
        v[i].setBet() ; 
    }
}

void dealCards(vector<player> &v, deck &playingdeck, deck &discard){
    v[0].appendHand(playingdeck, discard) ; 
    for (long unsigned int i = 1 ; i < v.size() ; i++) {
        v[i].appendHand(playingdeck, discard) ; 
        v[i].appendHand(playingdeck, discard) ; 
    }
}

void printGlobalInfos(vector<player> v){
    for (long unsigned int i=0 ; i<v.size() ; i++) {
        v[i].playerInfo() ; 
    }
}

void turnPlayer(vector<player> &v, deck &playingdeck, deck &discard){
    for (long unsigned int i = 1 ; i < v.size() ; i++) {
        cout << "Début du tour pour le joueur[" << v[i].getId() << "] :" << endl << endl ; 
        v[i].printHand() ; 
        v[i].play(playingdeck, discard) ; 
        cout << "Tour terminé pour le joueur[" << v[i].getId() << "]." << endl << "__________________________________________________________\n" << endl ; 
    }
}

void turnDealer(vector<player> &v, deck &playingdeck, deck &discard){
    cout << "Le croupier joue :" << endl << endl  ;  
    v[0].playDealer(playingdeck, discard) ; 
    cout << "Le croupier a terminé." << endl << "__________________________________________________________\n" << endl ;
}

void result(vector<player>& v){
    // On va check le score de chaque joueur avec son handsum et comparer au dealer.
    int psum ; 
    int dealersum = v[0].HandSum() ; 
    if (dealersum >= 21){
        // Le dealer a perdu.
        for (long unsigned int i = 1 ; i < v.size() ; i++) {
            psum = v[i].HandSum() ;
            int pcredit = v[i].getBet() ;
            if (psum == 21 && v[i].HandLenght() == 2){// Black Jack -> x2.5
                v[i].setCredit((int)(pcredit*2.5)) ;
                v[i].resetBet() ;  
                cout << "Joueur [" << v[i].getId() << "] remporte x2.5 sa mise. Credit = " << v[i].getCredit() << endl ; 
            }
            else{
                if (psum <= 21){// -> x2
                    v[i].setCredit(pcredit*2) ;
                    v[i].resetBet() ; 
                    cout << "Joueur [" << v[i].getId() << "] remporte x2 sa mise. Credit = " << v[i].getCredit() << endl ; 
                }
                else {
                    v[i].resetBet() ; 
                    cout << "Joueur [" << v[i].getId() << "] perd sa mise. Credit = " << v[i].getCredit() << endl ; 
                }
            }
        }
    }
    else {
        // le dealer n'a pas perdu, on compare les scores. 
        for (long unsigned int i = 1 ; i < v.size() ; i++) {
            psum = v[i].HandSum() ;
            int pcredit = v[i].getBet() ;
            if (psum == 21 && v[i].HandLenght() == 2){
                // Black Jack. On determine si le Dealer à aussi Blackjack. 
                if(dealersum == 21 && v[0].HandLenght() == 2) {// Blackjack aussi réalisé par le Dealer.
                    v[i].setCredit(pcredit) ;
                    v[i].resetBet() ;  
                    cout << "Joueur [" << v[i].getId() << "] récupère sa mise. Credit = " << v[i].getCredit() << endl ; 
                }
                else{
                    v[i].setCredit((int)(pcredit*2.5)) ;
                    v[i].resetBet() ;
                    cout << "Joueur [" << v[i].getId() << "] remporte x2.5 sa mise. Credit = " << v[i].getCredit() << endl ; 
                }
            }
            else{
                if (psum <= 21){
                    if(psum == dealersum){
                        v[i].setCredit(pcredit) ;
                        v[i].resetBet() ;
                        cout << "Joueur [" << v[i].getId() << "] récupère sa mise. Credit = " << v[i].getCredit() << endl ;   
                    }
                else{
                    if(psum > dealersum){
                        v[i].setCredit((int)(pcredit*2)) ;
                        v[i].resetBet() ;
                        cout << "Joueur [" << v[i].getId() << "] remporte x2 sa mise. Credit = " << v[i].getCredit() << endl ; 
                    }
                    else{
                        v[i].resetBet() ; 
                        cout << "Joueur [" << v[i].getId() << "] perd sa mise. Credit = " << v[i].getCredit() << endl ; 
                    }
                }   
                }
                else {
                    v[i].resetBet() ; 
                    cout << "Joueur [" << v[i].getId() << "] perd sa mise. Credit = " << v[i].getCredit() << endl ; 
                }
            }
        }
    }
    cout << endl ; 
}

void freeHands(vector<player> &v, deck &discard){ 
    for (long unsigned int i = 0 ; i < v.size() ; i++) {
        v[i].freeHand(discard) ; 
    }
}

void whoStays(vector<player> &v){
    int pcredit ; 
    int choice ; 
     for (long unsigned int i = 1 ; i < v.size() ; i++) {
        pcredit = v[i].getCredit() ; 
        if (pcredit < 10){
            cout << "Le joueur[" << v[i].getId() << "] n'a plus assez de crédit. Il sort de la table" << endl ; 
            v.erase(v.begin()+i) ; 
            i-=1 ; 
        }
        else {
            cout << "Joueur[" <<  v[i].getId() << "] que voulez vous faire ?" << endl ; 
            cout << "1) : Rester à la table. " << endl ; 
            cout << "2) : Quitter la table. " << endl ; 
            cin >> choice ; 
            while ( choice != 1 && choice != 2 ) {
                cout << "Choix invalide : " ; 
                cin >> choice ; 
            }
            if (choice == 2){
                cout << "Joueur[" <<  v[i].getId() << "] quitte la table avec : "<< v[i].getCredit() << " credits." << endl ; 
                v.erase(v.begin()+i) ;  
                i-=1 ; 
            }
        }
    }
    cout << endl ; 
}

int main(void) {
    // Creation of the deck and the discard.
    deck discard = initializeDiscard() ; 
    deck playingdeck ; 
    playingdeck.shuffleDeck(discard) ; 

    vector<player> vplayer = initializePlayers() ; 
    setCredit(vplayer) ;
    // Initialisation ok
    while (vplayer.size() != 1){
        setBet(vplayer) ; 
        system("clear") ; 
        dealCards(vplayer,playingdeck, discard) ; 
        printGlobalInfos(vplayer) ; 
        turnPlayer(vplayer,playingdeck, discard) ; 
        turnDealer(vplayer,playingdeck, discard) ; 
        result(vplayer) ; 
        freeHands(vplayer,discard) ; 
        whoStays(vplayer) ; 
        cout << "Fin du tour." << endl ; 
    }
    cout << "Fin de la partie." << endl ; 
    return 0 ; 
} 