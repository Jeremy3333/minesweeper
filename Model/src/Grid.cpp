//
// Created by jerem on 14/12/2023.
//

#include "Grid.h"

#include <iostream>
#include <random>

Grid::Grid(const Difficulty difficulty) : isInit_(false){
    switch (difficulty) {
        case beginner:
            numMine_ = 10;
            width_ = 9;
            height_ = 9;
        break;
        case intermediate:
            numMine_ = 40;
            width_ = 16;
            height_ = 16;
        break;
        case expert:
            numMine_ = 99;
            width_ = 30;
            height_ = 16;
        break;
        default:
            std::cerr << "Grid difficulty is wrong" << std::endl;
            exit(1);
    }

    mineLeft_ = numMine_;
    cells_ = new Cell*[width_];

    for(int i = 0; i < width_; i++) {
        cells_[i] = new Cell[height_];
    }

    for(int i = 0; i < width_; i++) {
        for(int j = 0; j < height_; j++) {
            cells_[i][j] = Cell();
        }
    }
}

Grid::~Grid() {
    for(int i = 0; i < width_; i++) {
        delete[] cells_[i];
    }
    delete[] cells_;
}


int Grid::getWidth() const {
    return width_;
}

int Grid::getHeight() const {
    return height_;
}

Cell Grid::getCell(const int x, const int y) const{
    return cells_[x][y];
}

// NOLINTNEXTLINE
bool Grid::revele(const int x, const int y) {
    if(x < 0 || y < 0 || x >= width_ || y >= height_)
        return false;
    if(!isInit_)
        init(x, y);
    if(cells_[x][y].isReveled())
        return false;
    const bool bomb = cells_[x][y].revele();
    if(cells_[x][y].getIndex() == 0) {
        for(int i = -1; i <= 1; i++)
            for(int j = -1; j <= 1; j++)
                revele(x + i, y + j);
    }
    return bomb;
}

void Grid::reveleMine() const {
    for(int i = 0; i < width_; i++) {
        for(int j = 0; j < height_; j++) {
            if(cells_[i][j].isBomb())
                cells_[i][j].reveleMine();
        }
    }
}

bool Grid::isWin() const {
    for(int i = 0; i < width_; i++) {
        for(int j = 0; j < height_; j++) {
            if(!cells_[i][j].isBomb() && !cells_[i][j].isReveled()) {
                return false;
            }
        }
    }
    return true;
}

int Grid::getMineLeft() const
{
    return mineLeft_;
}


void Grid::reset()
{
    for(int i = 0; i < width_; i++)
    {
        for(int j = 0; j < height_; j++)
        {
            cells_[i][j].reset();
        }
    }
    mineLeft_ = numMine_;
    isInit_ = false;
}


void Grid::markAllBomb() {
    for(int i = 0; i < width_; i++) {
        for(int j = 0; j < height_; j++) {
            if(cells_[i][j].isBomb())
                cells_[i][j].mark();
        }
    }
    mineLeft_ = 0;
}

void Grid::markCell(const int x, const int y)
{
    if(cells_[x][y].changeMark())
        mineLeft_--;
    else
        mineLeft_++;
}



void Grid::init(const int x, const int y){
    std::random_device rd;
    std::mt19937 gen(rd());

    int tx, ty;

        for(int i = 0; i < numMine_; i++) {
            do {
                tx = static_cast<int>(gen() % width_);
                ty = static_cast<int>(gen() % height_);
            }while(((tx >= x - 1 && tx <= x + 1) && (ty >= y - 1 && ty <= y + 1)) || cells_[tx][ty].isBomb());
            cells_[tx][ty].setIndex(-1);
        }

        for(int i = 0; i < width_; i++) {
            for(int j = 0; j < height_; j++) {
                if(!cells_[i][j].isBomb())
                    cells_[i][j].setIndex(bombAround(i, j));
            }
        }

    isInit_ = true;
}

int Grid::bombAround(const int x, const int y) const{
    int n = 0;
    for(int i = -1; i <= 1; i++) {
        for(int j = -1; j <= 1; j++) {
            if(i + x >= 0 && j + y >= 0 && i + x < width_ && j + y < height_ && cells_[i + x][j + y].isBomb())
                n++;
        }
    }
    return n;
}

