#include "UI.h"
#include "Constants.h"

UI::UI()
{
}

bool UI::load()
{
    if (!font.openFromFile("assets/fonts/PressStart2P-Regular.ttf"))
        return false;

    // Title, score, and lives all live inside the HUD bar at the top of the
    // window, above the maze, so they never overlap the tiles. Everything
    // shares a consistent left/right margin and sits on a clear two-row
    // rhythm (title row, then a score/lives row) instead of the score and
    // lives text fighting over the same baseline.
    title.emplace(font, "PAC-MAN", 18);
    title->setFillColor(sf::Color::Yellow);
    title->setPosition({HUD_MARGIN, 10.f});

    scoreText.emplace(font, "Score: 0", 12);
    scoreText->setPosition({HUD_MARGIN, 42.f});

    livesText.emplace(font, "Lives: 3", 12);
    livesText->setPosition({HUD_MARGIN, 42.f});

    messageText.emplace(font, "", 16);
    messageText->setPosition({0.f, 0.f});

    messageBackdrop.setFillColor(sf::Color(0, 0, 0, 180));

    hudDivider.setSize({static_cast<float>(WINDOW_WIDTH), 2.f});
    hudDivider.setPosition({0.f, static_cast<float>(HUD_HEIGHT) - 2.f});
    hudDivider.setFillColor(sf::Color(40, 40, 255));

    return true;
}

void UI::update(int score, int lives, GameState state)
{
    scoreText->setString("Score: " + std::to_string(score));
    livesText->setString("Lives: " + std::to_string(lives));

    // Right-align the lives counter within the HUD bar, mirroring the
    // left-aligned score so the row reads as one balanced line.
    sf::FloatRect livesBounds = livesText->getLocalBounds();
    livesText->setPosition({WINDOW_WIDTH - livesBounds.size.x - HUD_MARGIN, 42.f});

    switch (state)
    {
    case GameState::Menu:
        messageText->setString("PRESS ENTER\nTO START");
        break;

    case GameState::Ready:
        messageText->setString("READY!");
        break;

    case GameState::GameOver:
        messageText->setString("GAME OVER\nPress Enter to Play Again");
        break;

    case GameState::Win:
        messageText->setString("YOU WIN!\nPress Enter to Play Again");
        break;

    case GameState::Playing:
    default:
        messageText->setString("");
        break;
    }

    if (!messageText->getString().isEmpty())
    {
        sf::FloatRect bounds = messageText->getLocalBounds();
        messageText->setOrigin({bounds.position.x + bounds.size.x / 2.f,
                                 bounds.position.y + bounds.size.y / 2.f});
        messageText->setPosition({WINDOW_WIDTH / 2.f,
                                   HUD_HEIGHT + (ROWS * TILE_SIZE) / 2.f});

        sf::FloatRect gb = messageText->getGlobalBounds();
        messageBackdrop.setSize({gb.size.x + 40.f, gb.size.y + 30.f});
        messageBackdrop.setOrigin({messageBackdrop.getSize().x / 2.f,
                                    messageBackdrop.getSize().y / 2.f});
        messageBackdrop.setPosition(messageText->getPosition());
    }
}

void UI::draw(sf::RenderWindow& window)
{
    window.draw(*title);
    window.draw(*scoreText);
    window.draw(*livesText);
    window.draw(hudDivider);

    if (!messageText->getString().isEmpty())
        window.draw(messageBackdrop);

    window.draw(*messageText);
}
