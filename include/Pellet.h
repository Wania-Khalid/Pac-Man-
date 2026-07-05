#pragma once
#include <SFML/Graphics.hpp>
class Pellet
{
public:
    Pellet(float x, float y, bool power = false);
    void draw(sf::RenderWindow& window);
    bool isEaten() const;
    void eat();
    bool isPower() const;
    sf::FloatRect getBounds() const;
private:
    sf::CircleShape body;
    bool eaten = false;
    bool power = false;
    // Drives the gentle pulse animation on power pellets.
    sf::Clock pulseClock;
};
