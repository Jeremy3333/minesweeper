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

    void reveleCell(int x, int y);

private:
    Controller::GameController *controller_;
    bool lost;
    Grid grid_;
};

} // Model

#endif //GAMEMODEL_H
