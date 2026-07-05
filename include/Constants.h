#pragma once

// Grid size
//
// NOTE: level1.txt is genuinely 19 columns wide. COLS previously said 21,
// which was 2 columns too many. Since the map file is loaded with Windows
// line endings (CRLF), std::getline() on a Unix build left a trailing '\r'
// character stuck onto the end of every row string. That stray '\r' was
// neither '#' nor '.', so Maze::isWall() treated it as open floor (not a
// wall) while Game::loadPellets() correctly skipped it (not a pellet
// either). The net effect was a walkable column with no pellet in it -
// pellets appeared to randomly go missing/uncollectable near the right
// edge of the maze. The fix is two-fold: strip the '\r' in Maze::loadMap()
// (see Maze.cpp) and set COLS to match the map's real width.
constexpr int TILE_SIZE = 32;
constexpr int ROWS = 21;
constexpr int COLS = 19;

// Reserved space at the top of the window for the score/lives HUD,
// so the UI text no longer overlaps the top rows of the maze.
constexpr int HUD_HEIGHT = 70;

// Shared left/right text margin inside the HUD bar, so the title, score,
// and lives all line up consistently instead of using ad-hoc numbers.
constexpr float HUD_MARGIN = 15.f;

// Window size
constexpr int WINDOW_WIDTH = COLS * TILE_SIZE;
constexpr int WINDOW_HEIGHT = ROWS * TILE_SIZE + HUD_HEIGHT;

// Gameplay
constexpr float PLAYER_SPEED = 2.5f;
constexpr float GHOST_SPEED = 1.0f;

constexpr float PLAYER_RADIUS = 12.f;
constexpr float GHOST_RADIUS = 12.f;

constexpr int MAX_LIVES = 3;