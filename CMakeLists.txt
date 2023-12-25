cmake_minimum_required(VERSION 3.27)
project(minesweeper)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_modules)

set(SDL2_PATH
        "C:/SDL2-w64"
        /usr/include/
)

find_package(SDL2 REQUIRED)
find_package(SDL2TTF REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

add_executable(minesweeper main.cpp
        Model/GameModel.cpp
        Model/GameModel.h
        View/GameView.cpp
        View/GameView.h
        Controller/GameController.cpp
        Controller/GameController.h
        main.cpp
        Controller/GameController.h
        Controller/GameController.h
        Controller/GameController.h
        Model/src/Grid.cpp
        Model/src/Grid.h
        Utils/Difficulty.h
        Utils/Constant.h
        Model/src/Cell.cpp
        Model/src/Cell.h
        Utils/CaseID.h
        View/GameView.cpp
        Model/src/Grid.cpp
        View/GameView.cpp
)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY})
target_link_libraries(${PROJECT_NAME} ${SDL2TTF_LIBRARY})
target_link_libraries(${PROJECT_NAME} ${SDL2_IMAGE_LIBRARY})