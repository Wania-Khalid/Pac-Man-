# Pac-Man

A classic Pac-Man clone built with C++ and SFML.

![Start screen](docs/screenshots/start-screen.png)

## How to Play

1. Launch the game.
2. Press **Enter** to start.
3. Press the **Right Arrow** key to make Pac-Man start moving — the arrow keys steer him from there (**Up**, **Down**, **Left**, **Right**).
4. Eat all the pellets while avoiding the ghost. The four larger, glowing pellets in the corners are worth extra points.
5. Press **Escape** at any time to quit.

![Gameplay](docs/screenshots/gameplay.png)

## Controls

| Key            | Action              |
|----------------|---------------------|
| Arrow keys     | Move Pac-Man        |
| Enter          | Start / Restart     |
| Escape         | Quit                |

## Scoring

| Item          | Points |
|---------------|--------|
| Regular pellet| 10     |
| Power pellet  | 50     |

You lose a life if a ghost catches you. The game ends when you run out of lives, or you win by clearing every pellet from the maze.

![Game over](docs/screenshots/game-over.png)

## Building

The project uses [SFML](https://www.sfml-dev.org/) 3.x. With SFML installed:

```bash
g++ -std=c++20 -Iinclude src/*.cpp -o PacMan -lsfml-graphics -lsfml-window -lsfml-system
./PacMan
```

Run it from the project's root folder so it can find `assets/`.

## Project Structure

```
include/    Header files
src/        Source files
assets/     Fonts and maps
docs/       Screenshots for this README
```
