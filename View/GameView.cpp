//
// Created by jerem on 14/12/2023.
//

#include "GameView.h"
#include "../Utils/Constant.h"
#include "../Controller/GameController.h"

#include <iostream>

namespace View {
    GameView::GameView(Controller::GameController *controller) :WINH(0), WINW(0), controller_(controller), mouseLeft(false){
        window_ = SDL_CreateWindow("Minesweeper", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
        if(!window_) {
            std::cerr << "SDL window creation error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            exit(1);
        }
        renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (!renderer_) {
            // Handle renderer creation error
            std::cerr << "SDL renderer creation error: " << SDL_GetError() << std::endl;
            SDL_DestroyWindow(window_);
            SDL_Quit();
            exit(1);
        }
        font_ = TTF_OpenFont("../Media/TTF/mine-sweeper.ttf", 20);
        if(!font_) {
            std::cerr << "SDL font creation error: " << SDL_GetError() << std::endl;
            exit(1);
        }
        SDL_Surface *spriteSurface = IMG_Load("../Media/Sprite/minesweeperSprites.png");
        if(!spriteSurface) {
            std::cerr << "SDL sprite surface creation error: " << SDL_GetError() << std::endl;
            exit(1);
        }
        sprite_ = SDL_CreateTextureFromSurface(renderer_, spriteSurface);
        if(!sprite_) {
            std::cerr << "SDL sprite texture creation error: " << SDL_GetError() << std::endl;
            exit(1);
        }
    }

    GameView::~GameView() {
        SDL_DestroyRenderer(renderer_);
        SDL_DestroyWindow(window_);
    }

    void GameView::receiveInput() {
        int gridX, gridY;
        controller_->getGridDim(gridX, gridY, true);
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT){
                controller_->closeGame();
            }
            else if (event.type == SDL_KEYDOWN) {
                switch(event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    controller_->closeGame();
                    break;
                default:
                    break;
                }
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    const int mouseX = event.button.x;
                    const int mouseY = event.button.y;
                    controller_->mouseLeftDown(mouseX, mouseY);
                    mouseLeft = true;
                }
                else if (event.button.button == SDL_BUTTON_RIGHT)
                {
                    const int mouseX = event.button.x;
                    const int mouseY = event.button.y;
                    controller_->mouseRightDown(mouseX, mouseY);
                }
            }
            else if (event.type == SDL_MOUSEBUTTONUP) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    const int mouseX = event.button.x;
                    const int mouseY = event.button.y;
                    controller_->mouseLeftUp(mouseX, mouseY);
                    mouseLeft = false;
                }
            }
            else if (event.type == SDL_MOUSEMOTION && mouseLeft) {
                const int mouseX = event.button.x;
                const int mouseY = event.button.y;
                controller_->mouseLeftHoldDown(mouseX, mouseY);
            }
        }
    }

    void GameView::render() {
        int gridW, gridH;
        controller_->getGridDim(gridW, gridH, true);
        if(controller_->isGridResize())
        {
            WINW = gridW + (20 * ZOOM);
            WINH = gridW + (20 + 49) * ZOOM;
            SDL_SetWindowSize(window_, WINW, WINH);
        }
        drawBackground(WINW, WINH);
        drawHeader(WINW);
        drawGrid();
        SDL_RenderPresent(renderer_);
    }

    void GameView::getWindowDim(int& w, int& h) const
    {
        w = WINW;
        h = WINH;
    }


    void GameView::drawBackground(const int width, const int height) const{
        SDL_SetRenderDrawColor(renderer_,181, 181, 181, 255);
        SDL_RenderClear(renderer_);
        drawBump(0, 0, width, height, true);
    }

    void GameView::drawGrid() const{
        int gridW, gridH;
        controller_->getGridDim(gridW, gridH, false);
        drawBump((GRID_X - 2) * ZOOM, (GRID_Y - 2) * ZOOM, ((gridW * CASE_HEIGHT + 4) * ZOOM), ((gridH * CASE_HEIGHT + 4) * ZOOM), false);
        SDL_SetRenderDrawColor(renderer_,0, 0, 0, 255);
        for(int i = 0; i < gridW; i++) {
            for(int j = 0; j < gridH; j++) {
                drawCase(i,j);
            }
        }
        int x, y;
        controller_->getSelect(x, y);
        drawSelect(x, y);
    }

    void GameView::drawBump(const int x, const int y, const int w, const int h, const bool up) const{
        if(up)
            SDL_SetRenderDrawColor(renderer_,255, 255, 255, 255);
        else
            SDL_SetRenderDrawColor(renderer_,123, 123, 123, 255);
        SDL_Rect rect= {x, y, w - ZOOM, 2 * ZOOM};
        SDL_RenderFillRect(renderer_, &rect);
        rect.w = 2 * ZOOM;
        rect.h = h - ZOOM;
        SDL_RenderFillRect(renderer_, &rect);
        if(up)
            SDL_SetRenderDrawColor(renderer_,123, 123, 123, 255);
        else
            SDL_SetRenderDrawColor(renderer_,255, 255, 255, 255);
        rect.x = x + w - 2 * ZOOM;
        rect.y = y + ZOOM;
        SDL_RenderFillRect(renderer_, &rect);
        rect.x = x + ZOOM;
        rect.y = y + h - 2 * ZOOM;
        rect.w = w - ZOOM;
        rect.h = 2 * ZOOM;
        SDL_RenderFillRect(renderer_, &rect);
        SDL_SetRenderDrawColor(renderer_,181, 181, 181, 255);
        rect.w = ZOOM;
        rect.h = ZOOM;
        SDL_RenderFillRect(renderer_, &rect);
        rect.x = x + w - 2 * ZOOM;
        rect.y = y + ZOOM;
        SDL_RenderFillRect(renderer_, &rect);
    }

    void GameView::drawCase(const int x, const int y) const{
        drawTexture((x * CASE_HEIGHT + GRID_X) * ZOOM, (y * CASE_HEIGHT + GRID_Y) * ZOOM, CASE_HEIGHT * ZOOM, CASE_HEIGHT * ZOOM, controller_->getCellID(x, y) * (CASE_HEIGHT + 1), SPRITE_CASE_Y + (static_cast<int>(controller_->isCellNumbre(x, y)) * (CASE_HEIGHT + 1)), CASE_HEIGHT, CASE_HEIGHT                                   , sprite_, false);
    }

    void GameView::drawSelect(const int x, const int y) const {
        if(x == -1)
            return;
        drawTexture((x * CASE_HEIGHT + GRID_X) * ZOOM, (y * CASE_HEIGHT + GRID_Y) * ZOOM, CASE_HEIGHT * ZOOM, CASE_HEIGHT * ZOOM, 17, 51, 16, 16, sprite_, false);
    }

    void GameView::drawHeader(const int width) const
    {
        drawBump((HEADER_X - BORDER_LARGEUR) * ZOOM, (HEADER_Y - BORDER_LARGEUR) * ZOOM, width - 16 * ZOOM, (HEADER_H + BORDER_LARGEUR) * ZOOM, false);
        drawNumbre(((HEADER_X) + 7) * ZOOM, ((HEADER_Y - 1 + (HEADER_H - NUMBRE_H) / 2)) * ZOOM, controller_->getMineLeft());
        drawReset();
    }


    void GameView::drawReset() const
    {
        drawTexture(WINW / 2, (HEADER_Y + (HEADER_H / 2)) * ZOOM, RESET_HEIGHT * ZOOM, RESET_HEIGHT * ZOOM, controller_->getResetID() * (RESET_HEIGHT + 1), SPRITE_RESET_Y, RESET_HEIGHT, RESET_HEIGHT, sprite_, true);
    }

    // NOLINTNEXTLINE
    void GameView::drawNumbre(const int x, const int y, int n) const
    {
        if(n > 999)
            drawNumbre(x, y, 999);
        for(int i = 2; i >= 0; i--)
        {
            const int c = n % 10;
            n /= 10;
            drawTexture(x + (i * NUMBRE_W * ZOOM), y, NUMBRE_W * ZOOM, NUMBRE_H * ZOOM, (NUMBRE_W + 1) * c, NUMBRE_Y, NUMBRE_W, NUMBRE_H, sprite_, false);
        }
        drawBump(x - (BORDER_LARGEUR * ZOOM), y - (BORDER_LARGEUR * ZOOM), (3 * NUMBRE_W + 2 * BORDER_LARGEUR) * ZOOM, (NUMBRE_H + 2 * BORDER_LARGEUR)* ZOOM, false);
    }

    void GameView::drawText(const int x, const int y, const char* text, const SDL_Color* textColor, const bool centeredCoord) const {
        SDL_Surface* textSurface = TTF_RenderText_Solid(font_, text, *textColor);
        if(!textSurface) {
            std::cerr << "SDL surface creation error: " << SDL_GetError() << std::endl;
            exit(1);
        }
        drawSurface(x, y, textSurface, centeredCoord),
        SDL_FreeSurface(textSurface);
    }

    void GameView::drawSurface(const int x, const int y, SDL_Surface *surface, const bool centeredCoord) const {

        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_, surface);
        if(!texture) {
            std::cerr << "SDL texture creation error: " << SDL_GetError() << std::endl;
            exit(1);
        }
        drawTexture(x, y, surface->w, surface->h, 0, 0, surface->w, surface->h, texture, centeredCoord);
        SDL_DestroyTexture(texture);
    }

    void GameView::drawTexture(int pos_x, int pos_y, const int w, const int h, const int ori_x, const int ori_y, const int ori_w, const int ori_h, SDL_Texture* texture, const bool centeredCoord) const {

        if(centeredCoord) {
            pos_x -= w / 2;
            pos_y -= h / 2;
        }
        const SDL_Rect renderQuad = {pos_x, pos_y, w, h};
        const SDL_Rect originRect = {ori_x, ori_y, ori_w, ori_h};
        if(SDL_RenderCopy(renderer_, texture, &originRect, &renderQuad)) {
            std::cerr << "SDL Render Copy text error: " << SDL_GetError() << std::endl;
            exit(1);
        }
    }


} // View