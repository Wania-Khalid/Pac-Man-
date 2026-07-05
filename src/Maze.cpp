#include "Maze.h"
#include "Constants.h"
#include <fstream>
Maze::Maze()
{
}
bool Maze::loadMap(const std::string& filename)
{
    map.clear();
    std::ifstream file(filename);
    if (!file)
        return false;
    std::string line;
    while (getline(file, line))
    {
        while (!line.empty() && (line.back() == '\r' || line.back() == '\n'))
            line.pop_back();

        if (!line.empty())
            map.push_back(line);
    }
    return true;
}
void Maze::draw(sf::RenderWindow& window)
{
    sf::RectangleShape wall;
    wall.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
    wall.setFillColor(sf::Color(40,40,255));
    for (int r = 0; r < (int)map.size(); r++)
    {
        for (int c = 0; c < (int)map[r].size(); c++)
        {
            if (map[r][c] == '#')
            {
                wall.setPosition(sf::Vector2f(c * TILE_SIZE, r * TILE_SIZE + HUD_HEIGHT));
                window.draw(wall);
            }
        }
    }
}
bool Maze::isWall(int row, int col) const
{
    if (row < 0 || col < 0)
        return true;
    if (row >= (int)map.size())
        return true;
    if (col >= (int)map[row].size())
        return true;
    return map[row][col] == '#';
}
bool Maze::isWallPixel(float x, float y) const
{
    int col = static_cast<int>(x) / TILE_SIZE;
    int row = static_cast<int>(y) / TILE_SIZE;
    return isWall(row, col);
}
char Maze::getTile(int row, int col) const
{
    if (row < 0 || row >= map.size())
        return '#';
    if (col < 0 || col >= map[row].size())
        return '#';
    return map[row][col];
}
const std::vector<std::string>& Maze::getMap() const
{
    return map;
}
