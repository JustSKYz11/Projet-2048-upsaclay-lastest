#include<iostream>
#include<vector>
#include<ncurses.h>
#include "modele.hpp"

using namespace std;
using Plateau = vector<vector<int>>;

int main(){
    initscr();
    Partie partie = {plateauInitial(), 0};
    int move;
    bool runtime = true;
    string direction = "";
    keypad(stdscr, true); // recognize function keys and arrow keys in regular screen
    if(!has_colors()) cout << "Le terminal ne prend pas en charge les couleurs" << endl;
    start_color();
    init_pair(1, COLOR_MAGENTA, COLOR_BLACK);
    attron(COLOR_PAIR(1));
    while(!estTerminé(partie.grille)){

        printw("%s \nScore: %d\n", dessine(partie.grille).c_str(), partie.score);
        if(estGagnant(partie.grille)) printw("YOU WIN");
        move = getch();
        switch(move){
            case KEY_UP:
                direction = "w";
                break;
            case KEY_DOWN:
                direction = "s";
                break;
            case KEY_LEFT:
                direction = "a";
                break;
            case KEY_RIGHT:
                direction = "d";
                break;
            default:
                break;
        }
        partie = deplacement(partie , direction);

        clear();

    }
    attroff(COLOR_PAIR(1));
    clear();
    printw("%s \nScore: %d\n", dessine(partie.grille).c_str(), partie.score);
    printw("FIN DU PROGRAMME");
    getch();
    endwin();
    

    return 0;
}