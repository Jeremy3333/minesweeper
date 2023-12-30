//
// Created by jerem on 14/12/2023.
//

#ifndef GAMEMODEL_H
#define GAMEMODEL_H
#include "src/Grid.h"

namespace Controller
{
 class GameController;
}

namespace Model {

class GameModel {
public:
    /**
     * \brief Create a GameModel object
     */
    explicit GameModel(Controller::GameController* controller);

    /**
     * \return the Game grid
     */
    [[nodiscard]] Grid *getGrid();

    void getGridDim(int &x, int &y) const;
    [[nodiscard]] int getCellIndex(int x, int y) const;
    [[nodiscard]] int getMineLeft() const;
    [[nodiscard]] bool isReveled(int x, int y) const;
    [[nodiscard]] bool isMarked(int x, int y) const;
    [[nodiscard]] bool isLost() const;
    [[nodiscard]] bool isWin() const;

    void reveleCell(int x, int y);
    void markCell(int x, int y);
    void resetGrid();

private:
    Controller::GameController *controller_;
    bool lost_, win_;
    Grid grid_;
};

} // Model

#endif //GAMEMODEL_H
