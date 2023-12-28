//
// Created by jerem on 14/12/2023.
//

#ifndef GAMEVIEW_H
#define GAMEVIEW_H
#include "../Model/GameModel.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>


namespace Controller
{
    class GameController;
}

namespace View {

class GameView {
public:
    /**
     * \brief Create a GameView object
     */
    explicit GameView(Controller::GameController *controller);

    /**
     * \brief Destruct the object
     */
    ~GameView();

    void receiveInput();

    /**
     * \brief Render a fram of the game
     * \param model A pointer to the model that has to be display
     */
    void render();

    void getWindowDim(int &w, int &h) const;
private:
    SDL_Window* window_;
    SDL_Renderer* renderer_;
    int WINW, WINH;
    Controller::GameController *controller_;
    bool mouseLeft;
    TTF_Font* font_;
    SDL_Texture *sprite_;
    void drawBackground(int width, int height) const;
    void drawBump(int x, int y, int w, int h, bool up) const;
    void drawGrid() const;
    void drawCase(int x, int y) const;
    void drawSelect(int x, int y) const;
    void drawReset() const;
    void drawText(int x, int y,const char* text,const SDL_Color* textColor,bool centeredCoord) const;
    void drawSurface(int x, int y, SDL_Surface *surface,bool centeredCoord) const;
    void drawTexture(int pos_x, int pos_y, int w, int h, int ori_x, int ori_y, int ori_w, int ori_h, SDL_Texture *texture,bool centeredCoord) const;
};

} // View

#endif //GAMEVIEW_H
