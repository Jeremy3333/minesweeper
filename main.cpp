#include <iostream>

#include "Controller/GameController.h"
#include "Model/GameModel.h"
#include "View/GameView.h"

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0){
        // Handle initialization error
        std::cerr << "SDL initialization error: " << SDL_GetError() << std::endl;
        return 1;
    }
    if (TTF_Init() == -1) {
        // Handle initialization error
        std::cerr << "SDL TTF initialization error: " << SDL_GetError() << std::endl;
        return 1;
    }
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        // Handle SDL_image initialization error
        std::cerr << "SDL IMAGE initialization error: " << SDL_GetError() << std::endl;
        return 1;
    }
    // Create instances of the Model, View, and Controller
    Model::GameModel gameModel;
    View::GameView gameView;
    Controller::GameController gameController(&gameModel, &gameView);

    gameController.LaunchGameLoop();

    SDL_Quit();
    return 0;
}
