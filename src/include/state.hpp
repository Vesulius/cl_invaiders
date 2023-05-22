#pragma once

#include <set>
#include <string>
#include <vector>

#include "debug_log.hpp"
#include "graphics.hpp"

const int ENEMY_WIDTH = 3;

enum direction {
    left = -1,
    right = 1
};

struct Player {
    int x, y;
};

struct Enemy {
    int x, y;
    direction d;
};

struct Bullet {
    int x, y;
};

class State {
   public:
    bool gameOver;

    State(int height, int width) : graphics(height, width) {
        graphics = Graphics(height, width);
        gameOver = false;

        // enemies.push_back({2, 2, right});
        wave = 1;

        screenHeight = height;
        screenWidth = width;

        player.x = 10;
        player.y = 10;
        graphics.drawPlayer(player.y, player.x);
        graphics.refresh();
    }

    void processInput() {
        while (true) {
            switch (graphics.getInput()) {
                case -1:  // no input
                    return;
                case 65:  // UP
                    player.y--;
                    break;
                case 66:  // DOWN
                    player.y++;
                    break;
                case 67:  // RIGHT
                    player.x++;
                    break;
                case 68:  // LEFT
                    player.x--;
                    break;
                case 32:  // SPACE key
                    bullets.push_back({player.x + 1, player.y});
                    break;
                case 'q':
                case 'Q':
                    gameOver = true;
                    break;
                default:
                    // printw("Invalid input\n");
                    break;
            }
        }
    }

    void updateState() {
        // update bullets
        for (std::vector<Bullet>::iterator it = bullets.begin(); it != bullets.end();) {
            Bullet& b = *it;
            graphics.addAt(b.y, b.x, ' ');
            b.y--;
            if (b.y < 1) {
                it = bullets.erase(it);
            } else {
                ++it;
                graphics.addAt(b.y, b.x, '^');
            }
        }

        // update enemies
        for (std::vector<Enemy>::iterator it = enemies.begin(); it != enemies.end();) {
            Enemy& e = *it;
            graphics.maskEnemy(e.y, e.x);

            bool removeEnemy = false;

            removeEnemy = e.y >= screenHeight;

            for (Bullet& bullet : bullets) {
                if (bullet.y == e.y && (bullet.x == e.x || bullet.x == e.x + 1 || bullet.x == e.x + 2)) {
                    removeEnemy = true;
                    break;
                }
            }

            if (e.y == player.y && (player.x == e.x || player.x == e.x + 1 || player.x == e.x + 2)) {
                gameOver = true;
            }

            if (removeEnemy) {
                it = enemies.erase(it);
            } else {
                if (e.x + 2 >= screenWidth - ENEMY_WIDTH || e.x < 2) {
                    e.d = static_cast<direction>(e.d * (-1));
                    e.y++;
                }
                e.x += e.d;
                ++it;
                graphics.drawEnemy(e.y, e.x);
            }
        }

        // add next wave of enemies
        if (enemies.size() == 0) {
            wave *= 2;
            for (int i = 0; i < wave; i++) {
                enemies.push_back({2 + (i * (ENEMY_WIDTH + 2)) % (screenWidth / 2), 2 + (i * 4)  / screenHeight, right});
            }
        }

        // get user input and update player
        graphics.maskPlayer(player.y, player.x);
        processInput();
        graphics.drawPlayer(player.y, player.x);

        // UI
        graphics.printPoints(wave);
    }

    void gameOverScreen() {
        graphics.gameOverScreen();
        graphics.refresh();
    }

    void updateGraphics() {
        graphics.refresh();
    }

   private:
    Graphics graphics;
    Player player;
    int screenWidth;
    int screenHeight;
    int wave;
    std::vector<Enemy> enemies;
    std::vector<Bullet> bullets;
};
