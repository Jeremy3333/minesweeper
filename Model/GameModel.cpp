//
// Created by jerem on 14/12/2023.
//

#include "GameModel.h"

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

    int GameModel::getCellIndex(const int x, const int y) const
    {
        return grid_.getCell(x, y).getIndex();
    }

    bool GameModel::isReveled(const int x, const int y) const
    {
        return grid_.getCell(x, y).isReveled();
    }

    bool GameModel::isMarked(const int x, const int y) const
    {
        return grid_.getCell(x, y).isMarked();
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

    void GameModel::markCell(const int x, const int y) const
    {
        if(!grid_.getCell(x, y).isReveled())
        {
            grid_.markCell(x, y);
        }
    }



} // Model