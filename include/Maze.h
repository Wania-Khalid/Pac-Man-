
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
class Maze
{
public:
    Maze();
   public:
    bool loadMap(const std::string& filename);
    void draw(sf::RenderWindow& window);
    bool isWall(int row, int col) const;
    bool isWallPixel(float x, float y) const;
    char getTile(int row, int col) const;
    const std::vector<std::string>& getMap() const;
private:
    std::vector<std::string> map;
};