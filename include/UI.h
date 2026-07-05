#pragma once
#include <SFML/Graphics.hpp>
#include <optional>
#include "GameState.h"
class UI
{
public:
    UI();
    bool load();
    void update(int score, int lives, GameState state);
    void draw(sf::RenderWindow& window);
private:
    sf::Font font;
    std::optional<sf::Text> title;
    std::optional<sf::Text> scoreText;
    std::optional<sf::Text> livesText;
    std::optional<sf::Text> messageText;
    sf::RectangleShape messageBackdrop;
    sf::RectangleShape hudDivider;
};