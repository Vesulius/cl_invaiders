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
        drawFrame();
        wrefresh(window);
        nodelay(window, TRUE);
    }

    void drawFrame() {
        box(window, 0, 0);  // add border
        mvwprintw(window, 0, width / 2 - 9, " A S T E R O I D S ");
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

    void printPoints(int points, int bullets, int maxAmmo) {
        mvwprintw(window, height - 1, 4, " P O I N T S: %d - A M M O: %d/%d ", points, bullets, maxAmmo);
    }

    void gameOverScreen(int points) {
        wclear(window);
        drawFrame();
        mvwprintw(window, 5, 7, "   ___   _   __  __ ___ ");
        mvwprintw(window, 6, 7, "  / __| /_\\ |  \\/  | __|");
        mvwprintw(window, 7, 7, " | (_ |/ _ \\| |\\/| | _|");
        mvwprintw(window, 8, 7, "  \\___/_/ \\_\\_|  |_|___|");
        mvwprintw(window, 9, 7, "   _____   _____ ___");
        mvwprintw(window, 10, 7, "  / _ \\ \\ / / __| _ \\");
        mvwprintw(window, 11, 7, " | (_) \\ V /| _||   /");
        mvwprintw(window, 12, 7, "  \\___/ \\_/ |___|_|_\\");
        mvwprintw(window, height - 1, width / 2 - 7, " P O I N T S: %d ", points);
    }

   private:
    WINDOW* window;
    int height, width;
};
