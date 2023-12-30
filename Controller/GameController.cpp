//
// Created by jerem on 14/12/2023.
//

#include "GameController.h"
#include "../Utils/Constant.h"
#include "../Utils/CaseID.h"
#include "../Utils/ResetID.h"

#include <iostream>


namespace Controller {

    GameController::GameController() : model(this), view(this), running(true), holdLeftClickGrid(false), holdLeftClickReset(false), gridW(0), gridH(0), selX(-1), selY(-1) {}

    void GameController::getGridDim(int& x, int& y, const bool fromScreen) const
    {
        model.getGridDim(x, y);
        if(fromScreen)
            GridToScreenGrid(x, y);
    }

    int GameController::getCellID(const int x, const int y) const
    {
        const int index = model.getCellIndex(x, y);
        const bool reveled = model.isReveled(x, y);
        const bool marked = model.isMarked(x, y);
        if(isCellNumbre(x, y))
            return index - 1;



        if(reveled) {
            if(index == -2)
                return ExplodedMine;
            if(!marked) {
                if(index == 0)
                    return noMineAround;
                return Mine;
            }
            if(index != -1)
                return MarkedNoMine;
            std::cerr << "Error Impossible case" << std::endl;
            exit(1);
        }
        if(marked)
            return Marked;
        return Uncheck;
    }

    int GameController::getResetID() const
    {
        if(model.isLost())
            return Lose;
        if(model.isWin())
            return Win;
        if(holdLeftClickGrid)
            return CellSelect;
        if(holdLeftClickReset)
            return NormalSelect;
        return Normal;
    }

    int GameController::getMineLeft() const
    {
        return model.getMineLeft();
    }

    bool GameController::isCellNumbre(const int x, const int y) const
    {
        return (model.isReveled(x, y) && !model.isMarked(x, y) &&(model.getCellIndex(x, y) > 0));
    }

    bool GameController::isGridResize()
    {
        int tw, th;
        model.getGridDim(tw, th);

        if(tw == gridW && th == gridH)
            return false;

        gridW = tw;
        gridH = th;
        return true;
    }

    void GameController::getSelect(int& x, int& y) const
    {
        x = selX;
        y = selY;
    }


    void GameController::closeGame()
    {
        running = false;
    }


    void GameController::LaunchGameLoop(){

        // Main game loop
        while (running) {
            // Update user input and game state
            view.receiveInput();

            // Update the view based on the model
            view.render();
        }
    }

    void GameController::mouseLeftDown(const int mouseX, const int mouseY)
    {
        int WINW, WINH;
        view.getWindowDim(WINW, WINH);
        constexpr int gridX = GRID_X * ZOOM;
        constexpr int gridY = GRID_Y * ZOOM;
        int gridW, gridH;
        model.getGridDim(gridW, gridH);
        GridToScreenGrid(gridW, gridH);
        // if it's on the grid
        if(mouseX >= gridX && mouseY >= gridY && mouseX < gridX + gridW && mouseY < gridY + gridH)
        {
            int x = mouseX - gridX;
            int y = mouseY - gridY;
            ScreenGridToGrid(x, y);
            selectCell(x, y);
            holdLeftClickGrid = true;
            return;
        }
        // if it's on the reset button
        if(
            mouseX >= ((WINW / 2) - (RESET_HEIGHT / 2) * ZOOM) &&
            mouseX < ((WINW / 2) + (RESET_HEIGHT / 2) * ZOOM) &&
            mouseY >= (HEADER_Y + (HEADER_H / 2) - (RESET_HEIGHT / 2)) * ZOOM &&
            mouseY < (HEADER_Y + (HEADER_H / 2) + (RESET_HEIGHT / 2)) * ZOOM)
        {
            holdLeftClickReset = true;
        }
        selX = -1;
        selY = -1;
    }

    void GameController::mouseLeftHoldDown(const int mouseX, const int mouseY)
    {
        // if it's on the grid
        constexpr int gridX = GRID_X * ZOOM;
        constexpr int gridY = GRID_Y * ZOOM;
        int gridW, gridH;
        model.getGridDim(gridW, gridH);
        GridToScreenGrid(gridW, gridH);
        if(mouseX >= gridX && mouseY >= gridY && mouseX < gridX + gridW && mouseY < gridY + gridH && holdLeftClickGrid)
        {
            int x = mouseX - gridX;
            int y = mouseY - gridY;
            ScreenGridToGrid(x, y);
            selectCell(x, y);
            return;
        }
        selX = -1;
        selY = -1;
    }

    void GameController::mouseLeftUp(const int mouseX, const int mouseY)
    {
        selX = -1;
        selY = -1;
        int WINW, WINH;
        view.getWindowDim(WINW, WINH);
        constexpr int gridX = GRID_X * ZOOM;
        constexpr int gridY = GRID_Y * ZOOM;
        int gridW, gridH;
        model.getGridDim(gridW, gridH);
        GridToScreenGrid(gridW, gridH);
        // if it's on the grid
        if(mouseX >= gridX && mouseY >= gridY && mouseX < gridX + gridW && mouseY < gridY + gridH)
        {
            int x = mouseX - gridX;
            int y = mouseY - gridY;
            ScreenGridToGrid(x, y);
            model.reveleCell(x, y);
        }
        // if it's on the reset button
        else if(
            mouseX >= ((WINW / 2) - (RESET_HEIGHT / 2) * ZOOM) &&
            mouseX < ((WINW / 2) + (RESET_HEIGHT / 2) * ZOOM) &&
            mouseY >= (HEADER_Y + (HEADER_H / 2) - (RESET_HEIGHT / 2)) * ZOOM &&
            mouseY < (HEADER_Y + (HEADER_H / 2) + (RESET_HEIGHT / 2)) * ZOOM &&
            holdLeftClickReset)
        {
            model.resetGrid();
        }
        holdLeftClickGrid = false;
        holdLeftClickReset = false;
    }

    void GameController::mouseRightDown(const int mouseX, const int mouseY)
    {
        // if it's on the grid
        constexpr int gridX = GRID_X * ZOOM;
        constexpr int gridY = GRID_Y * ZOOM;
        int gridW, gridH;
        model.getGridDim(gridW, gridH);
        GridToScreenGrid(gridW, gridH);
        if(mouseX >= gridX && mouseY >= gridY && mouseX < gridX + gridW && mouseY < gridY + gridH)
        {
            int x = mouseX - gridX;
            int y = mouseY - gridY;
            ScreenGridToGrid(x, y);
            model.markCell(x, y);
        }
    }

    void GameController::selectCell(int x, int y)
    {
        if(model.getGrid()->getCell(x, y).isMarked() || model.getGrid()->getCell(x, y).isReveled() || model.isLost() || model.isWin())
        {
            selX = -1;
            selY = -1;
            return;
        }
        selX = x;
        selY = y;
    }


    void GameController::ScreenGridToGrid(int& x, int& y) {
        x /= CASE_HEIGHT * ZOOM;
        y /= CASE_HEIGHT * ZOOM;
    }

    void GameController::GridToScreenGrid(int& x, int& y)
    {
        x *= CASE_HEIGHT * ZOOM;
        y *= CASE_HEIGHT * ZOOM;
    }


} // Controller