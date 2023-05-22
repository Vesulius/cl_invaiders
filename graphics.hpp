#pragma once
#include <ncurses.h>

class Graphics {
   public:
    Graphics(int height, int width) {
        this->width = width;
        this->height = height;

        int maxX, maxY;
        getmaxyx(stdscr, maxY, maxX);

        window = newwin(height, width, (maxY / 2) - (height / 2), (maxY / 2) - (width / 2));

        // init graphics
        wclear(window);
        box(window, 0, 0);  // add border
        wrefresh(window);
        nodelay(window, TRUE);
    }

    int getInput() {
        return wgetch(window);
    }

    void refresh() {
        wrefresh(window);
    }

    void addAt(int y, int x, char c) {
        mvwaddch(window, y, x, c);
    }

    void maskEnemy(int y, int x) {
        mvwaddch(window, y, x, ' ');
        mvwaddch(window, y, x + 1, ' ');
        mvwaddch(window, y, x + 2, ' ');
    }

    void drawEnemy(int y, int x) {
        mvwaddch(window, y, x, '\\');
        mvwaddch(window, y, x + 1, 'V');
        mvwaddch(window, y, x + 2, '/');
    }

    void drawPlayer(int y, int x) {
        mvwaddch(window, y, x, '/');
        mvwaddch(window, y, x + 1, '^');
        mvwaddch(window, y, x + 2, '\\');
    }

    void maskPlayer(int y, int x) {
        mvwaddch(window, y, x, ' ');
        mvwaddch(window, y, x + 1, ' ');
        mvwaddch(window, y, x + 2, ' ');
    }

    void gameOverScreen() {
        wclear(window);
        box(window, 0, 0);  // add border
        mvwprintw(window, 5, 6, "   ___   _   __  __ ___ ");
        mvwprintw(window, 6, 6, "  / __| /_\\ |  \\/  | __|");
        mvwprintw(window, 7, 6, " | (_ |/ _ \\| |\\/| | _|");
        mvwprintw(window, 8, 6, "  \\___/_/ \\_\\_|  |_|___|");
        mvwprintw(window, 9, 6, "   _____   _____ ___");
        mvwprintw(window, 10, 6, "  / _ \\ \\ / / __| _ \\");
        mvwprintw(window, 11, 6, " | (_) \\ V /| _||   /");
        mvwprintw(window, 12, 6, "  \\___/ \\_/ |___|_|_\\");
    }

   private:
    WINDOW* window;
    int height, width;
};
