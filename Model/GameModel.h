//
// Created by jerem on 14/12/2023.
//

#ifndef GAMEMODEL_H
#define GAMEMODEL_H
#include "src/Grid.h"

namespace Model {

class GameModel {
public:
    /**
     * \brief Create a GameModel object
     */
    GameModel();

    /**
     * \return true if the game is running false otherwise
     */
    [[nodiscard]] bool isGameRunning() const;

    /**
     * \brief stop the game from running
     */
    void closeGame();

    /**
     * \return the Game grid
     */
    [[nodiscard]] Grid *getGrid();

    void selectCase(int x, int y);

    void reveleCell(int x, int y);

private:
    bool running;
    bool lost;
    Grid grid_;
};

} // Model

#endif //GAMEMODEL_H
