#pragma once

#include <chrono>
#include <string>
#include <thread>
#include <vector>

#include "debug_log.hpp"
#include "graphics.hpp"

const int ENEMY_WIDTH = 3;
const int MAX_BULLETS = 3;

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

        wave = 1;
        spawnEnemies = 0;
        points = 0;

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
                    if (player.y > 1) {
                        graphics.maskPlayer(player.y, player.x);
                        player.y--;
                    }
                    break;
                case 66:  // DOWN
                    if (player.y < screenHeight - 2) {
                        graphics.maskPlayer(player.y, player.x);
                        player.y++;
                    }
                    break;
                case 67:  // RIGHT
                    if (player.x < screenWidth - 4) {
                        graphics.maskPlayer(player.y, player.x);
                        player.x++;
                    }
                    break;
                case 68:  // LEFT
                    if (player.x > 1) {
                        graphics.maskPlayer(player.y, player.x);
                        player.x--;
                    }
                    break;
                case 32:  // SPACE key
                    if (bullets.size() < MAX_BULLETS) {
                        bullets.push_back({player.x + 1, player.y});
                    }
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
        // new wave
        if (enemies.size() == 0) {
            wave++;
            spawnEnemies = 2 ^ wave;
        }

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

            removeEnemy = e.y >= screenHeight - 1;

            for (Bullet& bullet : bullets) {
                if (bullet.y == e.y && (bullet.x == e.x || bullet.x == e.x + 1 || bullet.x == e.x + 2)) {
                    removeEnemy = true;
                    bullet.y = -1;
                    points++;
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

        // spawn enemies
        if (spawnEnemies > 0) {
            direction d = spawnEnemies % 2 ? left : right;
            enemies.push_back({screenWidth / 2, 1, d});
            enemies.push_back({screenWidth / 2 + ENEMY_WIDTH + 1, 1, d});
            enemies.push_back({screenWidth / 2 + ENEMY_WIDTH * 2 + 2, 1, d});
            spawnEnemies -= 3;
        }

        // get user input and update player
        processInput();
        graphics.drawPlayer(player.y, player.x);

        // UI
        graphics.printPoints(points, MAX_BULLETS - bullets.size(), MAX_BULLETS);
    }

    void gameOverScreen() {
        graphics.gameOverScreen(points);
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
    int spawnEnemies;
    int points;
    std::vector<Enemy> enemies;
    std::vector<Bullet> bullets;
};
