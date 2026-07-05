#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Maze.h"
#include "Player.h"
#include "Ghost.h"
#include "Pellet.h"
#include "UI.h"
#include "GameState.h"
class Game
{
public:
    Game();
    void run();
private:
    void processEvents();
    void update();
    void render();
    void loadPellets();
    void resetGame();
private:
    sf::RenderWindow window;
    Maze maze;
    Player player;
    Ghost ghost;
    UI ui;
    std::vector<Pellet> pellets;
    int score = 0;
    GameState state = GameState::Menu;
    // Counts down the brief "READY!" pause after Enter is pressed and
    // before the player/ghost actually start moving.
    // to run  the player we press the right arrow
    sf::Clock readyClock;
    static constexpr float READY_DURATION = 1.f; // seconds
};