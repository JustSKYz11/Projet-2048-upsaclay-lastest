#include<iostream>
#include<vector>
#include<iomanip>
#include<random>
#include<ctime>
#include<sstream>
#include "modele.hpp"

using namespace std;
using Plateau = vector<vector<int>>;

int tireDeuxOuQuatre(){
    srand(time(0));
    int a = 1 + rand() %10;
    if (a == 10) return 4;
    else return 2;
    
}



Plateau plateauVide(){
    Plateau tab(4); //declaration du plateau et allocation (taille 4)
    
    for (int i=0 ; i<tab.size() ; i++){
        tab[i] = vector<int>(4); //allocation des sous-tableaux
        
    }

    return tab;
    
}



Plateau reinitialisePlateau(){
    return(plateauVide());
}




Plateau plateauInitial(){
   
    Plateau game = plateauVide();
    
    srand(time(0));

    int m1,m2,n1,n2; // valeurs random qui vont designer une tuile au hasard pour lui allouer une valeur (2 ou 4)
    
    do{
        game = reinitialisePlateau();
        m1 = 0+rand()%3;
        n1 = 0+rand()%3;
        m2 = 0+rand()%3;
        n2 = 0+rand()%3;
        game[m1][n1] = tireDeuxOuQuatre(); // tirage aleatoire des tuiles auxquelles les valeurs 2 ou 4 seront donnees pas dans la meme case
        game[m2][n2] = tireDeuxOuQuatre(); // tirage aleatoire des tuiles auxquelles les valeurs 2 ou 4 seront donnees pas dans la meme case
        
    } while(m1 == m2 and n1 == n2);
    
    return game;
}


Plateau rotateMatrix(Plateau p){

    Plateau plateau = plateauVide();
    for(int i=0 ; i< plateau.size(); i++){
        for(int j=0 ; j<plateau[i].size(); j++){
            plateau[i][j] = p[plateau[i].size()-1-j][i];

        }        
    }
    
    return plateau;
    
}



Plateau unrotateMatrix(Plateau p){

    Plateau plateau = plateauVide();
    for(int i=0 ; i< plateau.size(); i++){
        for(int j=0 ; j<plateau[i].size(); j++){
            plateau[i][j] = p[j][plateau.size()-1-i];
            
        }
    }

    return plateau;
}



string plusGrandeCase(Plateau p){
    int plusGrand = 2; // la plus grande valeur de tuile dans la partie (minimum 2)
    for (auto ligne:p){
        for (auto tuile:ligne){
            if( tuile > plusGrand) plusGrand = tuile; // parcourt tous les elements du tableau pour trouver le plus grand
        }
    }
    
    return to_string(plusGrand); // fonction qui convertit le plus grand numero en chaine de caractere
}



string dessine(Plateau p){;

    ostringstream flux;

    string largest_number = plusGrandeCase(p); // la plus grande tuile dans le plateau
    
    int longueur_bordure = 4*(largest_number.size()+2) + 5;
                      
    for(int i=0; i<longueur_bordure ; i++) flux << "*";

    flux << "\n";
                          
    for(auto ligne:p){
        for(auto tuile:ligne){
            if (tuile != 0){
                flux << "*" << setw(largest_number.size()+1) << tuile << " " ; 
            }
            else{
                flux << "*" << setw(largest_number.size()+2) << setfill(' ') << " ";  // ici on a mis des espaces en considerant le nombre de caracteres de la   plus grande tuile plus deux espaces (un a gauche et un a droite)
            }
        }
        
        flux << "*\n";
        for(int i=0; i<longueur_bordure ; i++) flux << "*";
        flux << "\n";
    }

    return flux.str();

}

Plateau genereTuile(Plateau p){

    if(fullGrid(p)) return p;

    Plateau plateau = p;
    

    srand(time(0));

    int m,n;

    do{
        m = 0+rand()%4;
        n = 0+rand()%4;
        if(p[m][n] == 0) break;
            
        } while(p[m][n] != 0);

    plateau[m][n] = tireDeuxOuQuatre();   
    
    return plateau;
        
}

bool fullGrid(Plateau p){

    for(int i=0 ; i<p.size() ; i++){
        for(int j=0 ; j<p[i].size() ; j++){
            if(p[i][j] == 0) return false;
        }
    }

    return true;
}

bool canMerge(vector<int> ligne){
    
    for(int i=0 ; i<ligne.size() ; i++){
        if(ligne[i]!=0 && ligne[i+1] == ligne[i]) return true;
        for(int k=2 ; k< ligne.size()-i ; k++){
            for(int n=1; n<k ; n++)
                if (ligne[i] != 0 && ligne[i+k] == ligne[i] && ligne[i+k-n] == 0) return true;
        }
    }
    
    return false;
}



bool canMove(vector<int> tab, int index){

    if (tab[index+1] == 0 && tab[index] !=0 && index < tab.size()-1) return true;

    return false;
}



bool estTerminé(Plateau plateau){

    if(!fullGrid(plateau)) return false;
    else{
        Plateau rotaMatrix = rotateMatrix(plateau);
        for(int i=0 ; i<plateau.size(); i++){
            for(int j=plateau[i].size()-1 ; j>=0; j--){
                if(canMerge(plateau[i]) || canMerge(rotaMatrix[i])) return false;
                
            }
        }
        return true;
    }
    
    
}


bool estGagnant(Plateau plateau){
    
    for(auto ligne: plateau){
        for(auto tuile:ligne){
            if(tuile == 2048) return true;
            
        }
        
    }
    
    return false;
}



Partie deplacementDroite(Partie p){
    
    Plateau plateau = p.grille;
    int score_p = p.score;
    int k;

    if(!estTerminé(plateau)){
        for(int i=0 ; i<plateau.size() ; i++){
            for(int j=plateau[i].size()-1 ; j>=0 ; j--){
                if(plateau[i][j] != 0){
                k=j;
                
                while(canMove(plateau[i], k)){ // tuile va a droite tant qu'elle le peut
                    
                    
                    plateau[i][k+1] = plateau[i][k]; 
                    plateau[i][k] = 0;
                    k++;
                        
                    }

                if(plateau[i][k+1] == plateau[i][k]){
                    plateau[i][k] = 0;
                    plateau[i][k+1] *= 2;
                    score_p += plateau[i][k+1];

                    }
                }
            }
        }
        plateau = genereTuile(plateau);
    }
    
    
            
    return {plateau, score_p};
    
}



Partie deplacementHaut(Partie p){

    Partie plateau = p;
    plateau.grille = rotateMatrix(plateau.grille); //c'est comme ci on avait fait tourner la matrice et applique le mouvement a droite
    plateau = deplacementDroite(plateau);
    plateau.grille = unrotateMatrix(plateau.grille);
    return plateau;
    
}


Partie deplacementGauche(Partie p){
    
    Partie plateau = p;
    plateau.grille = rotateMatrix(plateau.grille);
    plateau.grille = rotateMatrix(plateau.grille);
    plateau = deplacementDroite(plateau);
    plateau.grille = unrotateMatrix(plateau.grille);
    plateau.grille = unrotateMatrix(plateau.grille);

    return plateau;
}


Partie deplacementBas(Partie p){

    Partie plateau = p;
    plateau.grille = unrotateMatrix(plateau.grille);
    plateau = deplacementDroite(plateau);
    plateau.grille = rotateMatrix(plateau.grille);
    
    return plateau;
    
}


Partie deplacement(Partie plateau, string direction){
        if (direction == "d" || direction == "d") return deplacementDroite(plateau);
        else if(direction == "h" || direction == "w" || direction == "z") return deplacementHaut(plateau);
        else if(direction == "b" || direction == "s") return deplacementBas(plateau);
        else if(direction == "g" || direction == "a") return deplacementGauche(plateau);
        else return plateau;
        
}
