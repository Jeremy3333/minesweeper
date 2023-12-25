//
// Created by jerem on 14/12/2023.
//

#include "GameModel.h"

#include <iostream>

namespace Model {
    GameModel::GameModel(Controller::GameController* controller) : controller_(controller), lost(false), grid_(beginner){}

    Grid *GameModel::getGrid() {
        return &grid_;
    }

    void GameModel::getGridDim(int& x, int& y) const
    {
        x = grid_.getWidth();
        y = grid_.getHeight();
    }


    void GameModel::reveleCell(const int x, const int y) {
        if(grid_.revele(x, y)) {
            lost = true;
            grid_.reveleMine();
        }
        if(grid_.isFinished()) {
            grid_.markAllBomb();
        }
    }


} // Model