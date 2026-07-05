# 🟡 Pac-Man

A classic Pac-Man clone built from scratch in **C++** with **SFML 3**. Chomp every pellet in the maze, grab the glowing power pellets in the corners, and stay one step ahead of the ghost.

---

## 📖 Overview

This project recreates the core Pac-Man experience: a tile-based maze, a chomping player character, a wandering ghost, collectible pellets, a live score/lives HUD, and win/lose states — all rendered in real time with SFML.

## ✨ Features

- **Smooth tile-based movement** with proper wall collision on all four sides of the maze
- **Animated chomping mouth** that opens and closes as Pac-Man moves
- **A ghost** with a classic scalloped "skirt" silhouette, googly eyes that track its direction, and simple wandering AI
- **Regular pellets** worth 10 points each
- **4 power pellets** in the maze corners — larger, gold, gently pulsing, worth 50 points each
- **"READY!" countdown** before each round starts, just like the arcade original
- **Live HUD** showing score and remaining lives
- **Win / Game Over screens** with a one-key restart

## 🎮 How to Play

1. Launch the game — you'll land on the title screen.
2. Press **Enter** to begin. A brief **"READY!"** message appears before you gain control.
3. Press the **Right Arrow** key to make Pac-Man start moving. From there, the arrow keys steer him in any direction (**Up**, **Down**, **Left**, **Right**).
4. Eat every pellet in the maze while avoiding the ghost.
5. Grab the four power pellets in the corners for bonus points.
6. Press **Escape** at any time to quit.

### Controls

| Key         | Action                     |
|-------------|----------------------------|
| ↑ ↓ ← →     | Move Pac-Man               |
| Enter       | Start game / Restart       |
| Escape      | Quit                       |

### Scoring

| Item            | Points |
|-----------------|:------:|
| Regular pellet  |   10   |
| Power pellet    |   50   |

You lose a life whenever the ghost catches you. The game ends when you run out of lives (**Game Over**) — or you win by clearing every pellet from the maze (**You Win**). Either way, press **Enter** to play again.

## 🛠️ Building from Source

**Requirements:** a C++20 compiler and [SFML 3.x](https://www.sfml-dev.org/) (graphics, window, and system modules).

```bash
g++ -std=c++20 -Iinclude src/*.cpp -o PacMan -lsfml-graphics -lsfml-window -lsfml-system
./PacMan
```

> Run the executable from the project's root folder so it can find the `assets/` directory (fonts and the map file).

## 📁 Project Structure

```
├── include/          Header files (Game, Player, Ghost, Maze, Pellet, UI, ...)
├── src/              Source files
├── assets/
│   ├── fonts/        Game font
│   └── maps/         Maze layout (level1.txt)
└── README.md
```

## 🕹️ Credits

Built as a learning project exploring 2D game architecture, collision detection, and real-time rendering with SFML.
