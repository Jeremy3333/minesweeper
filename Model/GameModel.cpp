//
// Created by jerem on 14/12/2023.
//

#include "GameModel.h"

namespace Model {
    GameModel::GameModel(Controller::GameController* controller) : controller_(controller), lost_(false), win_(false), grid_(beginner){}

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

    bool GameModel::isLost() const
    {
        return lost_;
    }

    bool GameModel::isWin() const
    {
        return win_;
    }

    void GameModel::reveleCell(const int x, const int y) {
        if(lost_||win_)
            return;
        if(grid_.revele(x, y)) {
            lost_ = true;
            grid_.reveleMine();
        }
        if(grid_.isWin()) {
            win_ = true;
            grid_.markAllBomb();
        }
    }

    void GameModel::markCell(const int x, const int y) const
    {
        if(lost_||win_)
            return;
        if(!grid_.getCell(x, y).isReveled())
        {
            grid_.markCell(x, y);
        }
    }

    void GameModel::resetGrid()
    {
        lost_ = false;
        win_ = false;
        grid_.reset();
    }




} // Model