#include "Game.h"
#include "Constants.h"

Game::Game()
    : window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Pac-Man")
{
    // Cap the frame rate so gameplay speed and the "READY!" timer behave
    // consistently across machines instead of racing ahead on fast/uncapped
    // displays.
    window.setFramerateLimit(60);

    maze.loadMap("assets/maps/level1.txt");
    loadPellets();
    ui.load();
}

void Game::loadPellets()
{
    pellets.clear();

    // Four larger, higher-value power pellets sit just inside each corner
    // of the maze - the same spots the classic arcade layout uses.
    const int inset = 1;
    const std::vector<std::pair<int, int>> powerPelletTiles = {
        {inset, inset},
        {inset, COLS - 1 - inset},
        {ROWS - 1 - inset, inset},
        {ROWS - 1 - inset, COLS - 1 - inset}
    };

    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col < COLS; col++)
        {
            if (maze.getTile(row, col) == '.')
            {
                bool isPowerPellet = false;
                for (const auto& tile : powerPelletTiles)
                {
                    if (tile.first == row && tile.second == col)
                    {
                        isPowerPellet = true;
                        break;
                    }
                }

                pellets.emplace_back(
                    col * TILE_SIZE + TILE_SIZE / 2.f,
                    row * TILE_SIZE + TILE_SIZE / 2.f,
                    isPowerPellet
                );
            }
        }
    }
}

void Game::processEvents()
{
    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
            window.close();

        if (const auto* key = event->getIf<sf::Event::KeyPressed>())
        {
            switch (key->code)
            {
            case sf::Keyboard::Key::Up:
                player.setDirection(Direction::Up);
                break;

            case sf::Keyboard::Key::Down:
                player.setDirection(Direction::Down);
                break;

            case sf::Keyboard::Key::Left:
                player.setDirection(Direction::Left);
                break;

            case sf::Keyboard::Key::Right:
                player.setDirection(Direction::Right);
                break;

            case sf::Keyboard::Key::Enter:

                if (state == GameState::Menu ||
                    state == GameState::GameOver ||
                    state == GameState::Win)
                {
                    if (state == GameState::GameOver || state == GameState::Win)
                        resetGame();

                    state = GameState::Ready;
                    readyClock.restart();
                }

                break;

            case sf::Keyboard::Key::Escape:

                window.close();
                break;

            default:
                break;
            }
        }
    }
}

void Game::update()
{
    if (state == GameState::Ready &&
        readyClock.getElapsedTime().asSeconds() >= READY_DURATION)
    {
        state = GameState::Playing;
    }

    if (state != GameState::Playing)
    {
        ui.update(score, player.getLives(), state);
        return;
    }

    player.update(maze);
    ghost.update(maze);

    if (player.getBounds().findIntersection(ghost.getBounds()).has_value())
    {
        player.loseLife();

        if (player.getLives() <= 0)
        {
            state = GameState::GameOver;
        }

        player.reset();
        ghost.reset();
    }

    int remaining = 0;

    for (auto& pellet : pellets)
    {
        if (pellet.isEaten())
            continue;

        remaining++;

        if (player.getBounds().findIntersection(pellet.getBounds()).has_value())
        {
            pellet.eat();
            score += pellet.isPower() ? 50 : 10;
            remaining--;
        }
    }

    if (remaining == 0 && state == GameState::Playing)
        state = GameState::Win;

    ui.update(score, player.getLives(), state);
}

void Game::render()
{
    window.clear(sf::Color::Black);

    maze.draw(window);

    for (auto& pellet : pellets)
        pellet.draw(window);

    player.draw(window);
    ghost.draw(window);

    ui.draw(window);

    window.display();
}

void Game::run()
{
    while (window.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

void Game::resetGame()
{
    score = 0;

    player.reset();
    ghost.reset();

    loadPellets();
}
