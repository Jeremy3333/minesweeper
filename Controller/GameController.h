//
// Created by jerem on 14/12/2023.
//

#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
#include "../Model/GameModel.h"
#include "../View/GameView.h"

namespace Controller {

class GameController {
public:
    /**
     * \brief Create a GameController Object
     */
    GameController();

    /**
     * \brief Lauche the game loop that end when the game end.
     */
    void LaunchGameLoop();
    void closeGame();

    void getGridDim(int &x, int &y, bool fromScreen) const;
    [[nodiscard]] int getCellID(int x, int y) const;
    [[nodiscard]] bool isCellNumbre(int x, int y) const;
    void getSelect(int &x, int &y) const;

    void mouseLeftDown(int mouseX, int mouseY);
    void mouseLeftHoldDown(int mouseX, int mouseY);
    void mouseLeftUp(int mouseX, int mouseY);

    void mouseRightDown(int mouseX, int mouseY);

    static void ScreenGridToGrid(int &x, int &y);
    static void GridToScreenGrid(int &x, int &y);
private:
    Model::GameModel model;
    View::GameView view;
    bool running;
    int selX, selY;
    void selectCell(int x, int y);
};

} // Controller

#endif //GAMECONTROLLER_H
