//
// Created by jerem on 14/12/2023.
//

#include "GameModel.h"

#include <iostream>

namespace Model {
    GameModel::GameModel() : running(true), lost(false), grid_(beginner){}

    bool GameModel::isGameRunning() const{
        return running;
    }

    void GameModel::closeGame() {
        running = false;
    }

    Grid *GameModel::getGrid() {
        return &grid_;
    }

    void GameModel::selectCase(int x, int y) {
        grid_.selectCase(x, y);
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