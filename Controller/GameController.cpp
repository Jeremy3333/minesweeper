//
// Created by jerem on 14/12/2023.
//

#include "GameController.h"

#include <iostream>

#include "../Utils/Constant.h"


namespace Controller {

    GameController::GameController(Model::GameModel *p_model,View::GameView *p_view) : model(p_model), view(p_view), mouseLeft(false) {}

    bool GameController::isGameRunning() const {
        return model->isGameRunning();
    }

    void GameController::LaunchGameLoop(){

        // Main game loop
        while (isGameRunning()) {
            // Update user input and game state
            handleInput();

            // Update the view based on the model
            view->render(model);
        }
    }


    void GameController::handleInput() {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT){
                model->closeGame();
            }
            else if (event.type == SDL_KEYDOWN) {
                switch(event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        model->closeGame();
                    break;
                    default:
                        break;
                }
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    int mouseX = event.button.x;
                    int mouseY = event.button.y;
                    ScreenToGrif(mouseX, mouseY);
                    model->selectCase(mouseX, mouseY);
                    mouseLeft = true;
                }
            }
            else if (event.type == SDL_MOUSEBUTTONUP) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    int mouseX = event.button.x;
                    int mouseY = event.button.y;
                    ScreenToGrif(mouseX, mouseY);
                    model->selectCase(-1, -1);
                    model->reveleCell(mouseX, mouseY);
                    mouseLeft = false;
                }
            }
            else if (event.type == SDL_MOUSEMOTION && mouseLeft) {
                int mouseX = event.button.x;
                int mouseY = event.button.y;
                ScreenToGrif(mouseX, mouseY);
                model->selectCase(mouseX, mouseY);
            }
        }
    }

    void GameController::ScreenToGrif(int& x, int& y) {
        x = (x - (10 * ZOOM)) / (CASE_HEIGHT * ZOOM);
        y = (y - (59 * ZOOM)) / (CASE_HEIGHT * ZOOM);
    }

} // Controller