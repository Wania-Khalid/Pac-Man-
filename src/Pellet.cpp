#include "Pellet.h"
#include "Constants.h"
#include <cmath>
Pellet::Pellet(float x, float y, bool power)
    : power(power)
{
    float radius = power ? 9.f : 4.f;
    body.setRadius(radius);
    body.setOrigin({radius, radius});
    // Power pellets get a warm gold color so they read as special/valuable
    // at a glance, on top of being noticeably bigger.
    body.setFillColor(power ? sf::Color(255, 184, 82) : sf::Color::White);
    body.setPosition({x, y});
    eaten = false;
}
void Pellet::draw(sf::RenderWindow& window)
{
    if (eaten)
        return;
    // Position/collision stay in maze-grid space; only the drawn
    // copy is shifted down below the HUD bar.
    sf::CircleShape drawBody = body;
    if (power)
    {
        // Slow, subtle pulse to draw the eye without being distracting.
        float t = pulseClock.getElapsedTime().asSeconds();
        float scale = 1.f + 0.15f * std::sin(t * 4.f);
        drawBody.setScale({scale, scale});
    }
    drawBody.move({0.f, static_cast<float>(HUD_HEIGHT)});
    window.draw(drawBody);
}
bool Pellet::isEaten() const
{
    return eaten;
}
void Pellet::eat()
{
    eaten = true;
}
bool Pellet::isPower() const
{
    return power;
}
sf::FloatRect Pellet::getBounds() const
{
    return body.getGlobalBounds();
}
