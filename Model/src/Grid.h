//
// Created by jerem on 14/12/2023.
//

#ifndef GRID_H
#define GRID_H

#include "../../Utils/Difficulty.h"
#include "Cell.h"

#include <random>

class Grid {
public:
    /**
     * \brief Create a Grid object
     * \param difficulty The difficulty wanted
     */
    explicit Grid(Difficulty difficulty);

    ~Grid();

    /**
     * \return How many Cells there is in width
     */
    [[nodiscard]] int getWidth() const;

    /**
     * \return How many Cells there is in height
     */
    [[nodiscard]] int getHeight() const;

    [[nodiscard]] Cell getCell(int x, int y) const;

    void getSelect(int &x, int &y) const;

    void selectCase(int x, int y);

    bool revele(int x, int y);

    void reveleMine() const;

    [[nodiscard]] bool isFinished() const;

    void markAllBomb() const;
private:
    int numMine_;
    int mineLeft_;
    int width_;
    int height_;
    int selX_, selY_;
    Cell **cells_;
    bool isInit_;
    void init(int x, int y);
    int bombAround(int x, int y) const;
};



#endif //GRID_H
