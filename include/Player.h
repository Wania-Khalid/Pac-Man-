#pragma once
#include <SFML/Graphics.hpp>
#include "Maze.h"
#include "Direction.h"
class Player
{
public:
    Player();
    void update(const Maze& maze);
    void draw(sf::RenderWindow& window);
    void setDirection(Direction dir);
    sf::Vector2f getPosition() const;
    sf::FloatRect getBounds() const;
    void reset();
    void loseLife();
    int getLives() const;
private:
    bool canMove(float x, float y, const Maze& maze);
    void updateMouth();
private:
    sf::CircleShape body;
    sf::ConvexShape mouth;
    sf::Vector2f position;
    Direction direction;
    Direction nextDirection;
    float speed;
    float animTime = 0.f;
    int lives;
};