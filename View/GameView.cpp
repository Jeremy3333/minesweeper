//
// Created by jerem on 14/12/2023.
//

#include "GameView.h"
#include "../Utils/Constant.h"

#include <iostream>

namespace View {
    GameView::GameView() {
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

    void GameView::render(Model::GameModel *model) const{
        const int WINW = ((CASE_HEIGHT * (model->getGrid()->getWidth())) + 20) * ZOOM;
        const int WINH = (((CASE_HEIGHT * (model->getGrid()->getWidth())) + 20) + 49) * ZOOM;
        SDL_SetWindowSize(window_, WINW, WINH);
        drawBackground(WINW, WINH);
        drawGrid(*model->getGrid());
        SDL_RenderPresent(renderer_);
    }

    void GameView::drawBackground(const int width, const int height) const{
        SDL_SetRenderDrawColor(renderer_,181, 181, 181, 255);
        SDL_RenderClear(renderer_);
        drawBump(0, 0, width, height, true);
        drawBump(8 * ZOOM, 57 * ZOOM, width - 16 * ZOOM, height - 16 * ZOOM, false);
        drawBump(8 * ZOOM, 8 * ZOOM, width - 16 * ZOOM, 41 * ZOOM, false);
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


    void GameView::drawGrid(const Grid& grid) const{
        SDL_SetRenderDrawColor(renderer_,0, 0, 0, 255);
        for(int i = 0; i < grid.getWidth(); i++) {
            for(int j = 0; j < grid.getHeight(); j++) {
                drawCase(i,j, grid.getCell(i, j));
            }
        }
        int x, y;
        grid.getSelect(x, y);
        drawSelect(x, y);
    }

    void GameView::drawCase(const int x, const int y, const Cell cell) const{
        drawTexture((x * CASE_HEIGHT + 10) * ZOOM, (y * CASE_HEIGHT + 59) * ZOOM, CASE_HEIGHT * ZOOM, CASE_HEIGHT * ZOOM, cell.getCaseID() * 17, 51 + (static_cast<int>(cell.isCaseNumbre()) * 17), 16, 16, sprite_, false);
    }

    void GameView::drawSelect(const int x, const int y) const {
        if(x == -1)
            return;
        drawTexture((x * CASE_HEIGHT + 10) * ZOOM, (y * CASE_HEIGHT + 59) * ZOOM, CASE_HEIGHT * ZOOM, CASE_HEIGHT * ZOOM, 17, 51, 16, 16, sprite_, false);
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