//
// Created by jerem on 14/12/2023.
//

#ifndef GRID_H
#define GRID_H

#include "../../Utils/Difficulty.h"
#include "Cell.h"

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
    [[nodiscard]] bool isWin() const;
    [[nodiscard]] int getMineLeft() const;

    bool revele(int x, int y);
    void reveleMine() const;

    void reset();

    void markAllBomb();
    void markCell(int x, int y);
private:
    int numMine_;
    int mineLeft_;
    int width_;
    int height_;
    Cell **cells_;
    bool isInit_;
    void init(int x, int y);
    [[nodiscard]] int bombAround(int x, int y) const;
};



#endif //GRID_H
