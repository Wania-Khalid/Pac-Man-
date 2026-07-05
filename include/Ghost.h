#pragma once
#include <SFML/Graphics.hpp>
#include "Maze.h"
#include "Direction.h"
class Ghost
{
public:
    Ghost();
    void update(const Maze& maze);
    void draw(sf::RenderWindow& window);
    void reset();
    sf::Vector2f getPosition() const;
    sf::FloatRect getBounds() const;
private:
    bool canMove(float x, float y, const Maze& maze);
    void chooseDirection(const Maze& maze);
    void buildBody();
    sf::ConvexShape body;
    sf::CircleShape eyeLeft, eyeRight;
    sf::CircleShape pupilLeft, pupilRight;
    sf::Vector2f position;
    float speed;
    Direction direction;
};