#include <vector>
#include <string>
using namespace std;

using Plateau = vector<vector<int>>;

struct Partie{
    Plateau grille;
    int score;
};

// Vous pouvez ajouter des fonctions à ce fichier si besoin est

/** génère aléatoirement un 2 ou un 4 avec des probabilités respectives de 9/10 et 1/10
 *  @return 2 ou 4
 **/
int tireDeuxOuQuatre();

/** génère un plateau de dimensions 4*4 ne contenant que des 0
 *  @return un plateau vide
 **/
Plateau plateauVide();

/** génère deux nombres sur des cases aléatoires d'un plateau vide
 *  @return un plateau en début de jeu
 **/
Plateau plateauInitial();

/** déplace les tuiles d'un plateau vers la gauche et les combine si possible
 *  @param plateau le plateau
 *  @return le plateau une fois déplacé vers la gauche
 **/
Partie deplacementGauche(Partie p);

/** déplace les tuiles d'un plateau vers la droite et les combine si possible
 *  @param plateau le plateau
 *  @return le plateau une fois déplacé vers la droite
 **/
Partie deplacementDroite(Partie p);

/** déplace les tuiles d'un plateau vers le haut et les combine si possible
 *  @param p le plateau
 *  @return le plateau une fois déplacé vers le haut
 **/
Partie deplacementHaut(Partie p);

/** déplace les tuiles d'un plateau vers le bas et les combine si possible
 *  @param plateau le plateau
 *  @return le plateau une fois déplacé vers le bas
 **/
Partie deplacementBas(Partie p);

/** déplace les tuiles d'un plateau dans la direction donnée et génère une nouvelle tuile si le déplacement est valide
 *  @param plateau le plateau
 *  @param direction la direction
 *  @return le plateau déplacé dans la direction
 **/
Partie deplacement(Partie plateau, string direction);

/** affiche un plateau
 * @param p le plateau
 **/
string dessine(Plateau p);

/** permet de savoir si une partie est terminée
 *  @param plateau un plateau
 *  @return true si le plateau est vide, false sinon
 **/
bool estTerminé(Plateau plateau);

/** permet de savoir si une partie est gagnée
 * @param plateau un plateau
 * @return true si le plateau contient un 2048, false sinon
 **/
bool estGagnant(Plateau plateau);

/** permet de savoir si la grille est pleine
 * @param p le plateau
 * @return un booleen
 **/
bool fullGrid(Plateau p);

/** permet de recuperer la tuile avec le numero le plus grand
  * @param p le plateau
  * @return une chaine de caractere
**/

string plusGrandeCase(Plateau p);


/** fonction qui reinitialise un plateau a 0
  * @return un plateau 4x4 nul
**/

Plateau reinitialisePlateau();

/** fonction qui donne aleatoirement la valeur 2 ou 4 a une tuile vide du plateau
  * @param plateau p
  * @return un plateau
**/

Plateau genereTuile(Plateau p);

/** fonction qui verifie si deux tuiles peuvent etre combinees
  * @param p le Plateau
  * @return un booleen
**/

bool canMerge(vector<int> ligne);

/** fonction qui verifie si une tuile peut se deplacer vers la droite
  * @param tab un tableau d'entiers
  * @param index un entier
  * @return un booleen
**/

bool canMove(vector<int> tab, int index);

/** fonction qui tourne a 90 degres le plateau
  * @param plateau Le plateau
  * @return un plateau
**/ 

Plateau rotateMatrix(Plateau p);
/** fonction inverse a la fonction rotateMatrix (remet le plateau a sa place)
  * @param plateau Le plateau
  * @return un plateau
**/ 

Plateau unrotateMatrix(Plateau p);


