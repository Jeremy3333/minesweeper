//
// Created by jerem on 14/12/2023.
//

#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
#include "../Model/GameModel.h"
#include "../View/GameView.h"

#include <SDL.h>

namespace Controller {

class GameController {
public:
    /**
     * \brief Create a GameController Object
     * \param p_model A pointer to the minesweeper model
     * \param p_view A point to the minesweeper view
     */
    GameController(Model::GameModel *p_model, View::GameView *p_view);

    /**
     * \brief Lauche the game loop that end when the game end.
     */
    void LaunchGameLoop();
private:
    Model::GameModel *model;
    View::GameView *view;
    bool mouseLeft;
    [[nodiscard]] bool isGameRunning() const;
    void handleInput();
    static void ScreenToGrif(int &x, int &y) ;
};

} // Controller

#endif //GAMECONTROLLER_H
