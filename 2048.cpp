#include<iostream>
#include<vector>
#include "modele.hpp"

using namespace std;
using Plateau = vector<vector<int>>;

int main(){


    Partie partie = {plateauInitial(), 0};
    string move;
    cout << dessine(partie.grille) << endl;
    bool runtime = true;
    while (runtime){
        cout << "Entrer une commande: ";
        cin >> move;
        cout << endl;
        if (move=="q") runtime = false;
        else partie = deplacement(partie, move);
        cout << dessine(partie.grille) << endl;
        if (estGagnant(partie.grille)) cout << "YOU WON";
        if (estTerminé(partie.grille)){ 
            cout << dessine(partie.grille) << endl << "GAME OVER" << endl;
            runtime = false;    
        }

    }

    
    return 0;
}