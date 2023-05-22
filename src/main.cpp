#include <ncurses.h>

#include <chrono>
#include <thread>
#include <vector>

#include "state.hpp"

const int WINDOW_HEIGHT = 20;
const int WINDOW_WIDTH = WINDOW_HEIGHT * 2;
const int FRAME_RATE = 20;

int main() {
    // Init ncurses
    initscr();
    refresh();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, true);

    std::chrono::milliseconds frameTime(1000 / FRAME_RATE);

    State state(WINDOW_HEIGHT, WINDOW_WIDTH);

    while (!state.gameOver) {
        auto startTime = std::chrono::steady_clock::now();
        state.updateState();
        state.updateGraphics();
        auto endTime = std::chrono::steady_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
        std::this_thread::sleep_for(frameTime - elapsedTime);
    }
    state.gameOverScreen();
    getch();  // just a delay before quitting the game
    endwin();
    return 0;
}
