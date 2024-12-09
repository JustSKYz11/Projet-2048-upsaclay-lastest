
#include <SDL.h>
#include <SDL_ttf.h>
#include "modele.hpp"
using namespace std;

const int width = 600;
const int height = 800;

void SDL_ERROR_EXIT(const char *message) {
    SDL_Log("%s > %s", message, SDL_GetError());
    TTF_Quit();
    SDL_Quit();
    exit(EXIT_FAILURE);
}

void TTF_ERROR_EXIT(const char *message) {
    SDL_Log("%s > %s", message, TTF_GetError());
    TTF_Quit();
    SDL_Quit();
    exit(EXIT_FAILURE);
}

int main(int argc, char* argv[]) {
    SDL_bool runtime = SDL_TRUE;
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        SDL_ERROR_EXIT("Erreur a l'initialisation de SDL");

    if (TTF_Init() != 0)
        TTF_ERROR_EXIT("Erreur a l'initialisation de TTF");

    // Create window
    window = SDL_CreateWindow("2048 Game by Samih", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (window == NULL)
        SDL_ERROR_EXIT("Erreur a la creation de la fenetre");

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL)
        SDL_ERROR_EXIT("Erreur a la creation du rendu");

    TTF_Font* font = TTF_OpenFont("OpenSans-Bold.ttf", 24);
    if (!font)
        TTF_ERROR_EXIT("Erreur au chargement de la police d'ecriture");

    SDL_Color White = {255, 255, 255};
    Partie partie = {plateauInitial(), 0};

    SDL_SetRenderDrawColor(renderer, 84, 178, 189, 255);
    SDL_RenderClear(renderer);

    while (runtime) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                runtime = SDL_FALSE;
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                      partie = deplacement(partie, "w");
                      break;
                    case SDLK_DOWN:
                      partie = deplacement(partie, "s");
                      break;
                    case SDLK_LEFT: 
                      partie = deplacement(partie, "a");
                      break;
                    case SDLK_RIGHT:
                      partie = deplacement(partie, "d");
                      break;
                    default:
                      break;
                }
            }
        }
        
        SDL_SetRenderDrawColor(renderer, 143, 150, 151, 255);
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                SDL_Rect tile = {(j+1)*12 + j*135, (i+1)*12 + i*135, 135, 135};
                SDL_RenderFillRect(renderer, &tile);

                if (partie.grille[i][j] != 0) {
                    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, to_string(partie.grille[i][j]).c_str(), White);
                    if (!surfaceMessage)
                        TTF_ERROR_EXIT("Erreur au rendu du texte");

                    SDL_Texture* messageTexture = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
                    SDL_FreeSurface(surfaceMessage);
                    if (!messageTexture)
                        SDL_ERROR_EXIT("Erreur a la creation de la texture");

                    SDL_Rect textRect = {tile.x + 45, tile.y + 45, 45, 45}; // Adjust text size & position
                    SDL_RenderCopy(renderer, messageTexture, NULL, &textRect);
                    SDL_DestroyTexture(messageTexture);
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 199, 166, 57, 255);
        SDL_Rect rect_score = {12, 600 ,576, 188};
        SDL_RenderFillRect(renderer, &rect_score);

        string scoremsg = "Score: " + to_string(partie.score);

        SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, scoremsg.c_str() , White);
        if (!surfaceMessage)
          TTF_ERROR_EXIT("Erreur au rendu du texte");

        SDL_Texture* messageTexture = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
        SDL_FreeSurface(surfaceMessage);
        if (!messageTexture)
        SDL_ERROR_EXIT("Erreur a la creation de la texture");

         // Adjust text size & position
        SDL_RenderCopy(renderer, messageTexture, NULL, &rect_score);
        SDL_DestroyTexture(messageTexture);

        SDL_RenderPresent(renderer); // Show everything

        if(estTerminé(partie.grille)){
          SDL_Delay(10000);
          break;
        } 
        
    }

    

    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
