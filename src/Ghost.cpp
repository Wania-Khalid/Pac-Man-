#include "Ghost.h"
#include "Constants.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
Ghost::Ghost()
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    buildBody();
    body.setFillColor(sf::Color::Red);
    // A subtle darker outline helps the scalloped skirt read clearly
    // against the maze instead of blending into a flat red blob.
    body.setOutlineColor(sf::Color(120, 0, 0));
    body.setOutlineThickness(1.5f);
    float eyeR = GHOST_RADIUS * 0.32f;
    eyeLeft.setRadius(eyeR);
    eyeRight.setRadius(eyeR);
    eyeLeft.setOrigin({eyeR, eyeR});
    eyeRight.setOrigin({eyeR, eyeR});
    eyeLeft.setFillColor(sf::Color::White);
    eyeRight.setFillColor(sf::Color::White);
    float pupilR = eyeR * 0.5f;
    pupilLeft.setRadius(pupilR);
    pupilRight.setRadius(pupilR);
    pupilLeft.setOrigin({pupilR, pupilR});
    pupilRight.setOrigin({pupilR, pupilR});
    pupilLeft.setFillColor(sf::Color(30, 30, 120));
    pupilRight.setFillColor(sf::Color(30, 30, 120));
    position = sf::Vector2f(17 * TILE_SIZE + TILE_SIZE / 2.f, TILE_SIZE + TILE_SIZE / 2.f); // centered on tile (1,17)
    body.setPosition(position);
    speed = GHOST_SPEED;
    direction = Direction::Left;
}
void Ghost::buildBody()
{
    // Classic ghost silhouette: a rounded dome on top and a wavy,
    // scalloped skirt on the bottom, built as one polygon centered
    // on the origin so it can just be positioned each frame.
    float R = GHOST_RADIUS;
    body.setPointCount(16);
    int i = 0;
    // Dome: 7 points sweeping from the left side, over the top, to the right side.
    for (int step = 0; step <= 6; ++step)
    {
        float theta = (180.f - step * 30.f) * 3.14159265f / 180.f;
        body.setPoint(i++, {R * std::cos(theta), -R * std::sin(theta)});
    }
    // Right side, straight down into the skirt.
    body.setPoint(i++, {R, R});
    // Skirt: alternating scallop tips and notches, right to left.
    body.setPoint(i++, {0.75f * R, R + 0.6f * R});
    body.setPoint(i++, {0.5f * R,  R});
    body.setPoint(i++, {0.25f * R, R + 0.6f * R});
    body.setPoint(i++, {0.f,       R});
    body.setPoint(i++, {-0.25f * R, R + 0.6f * R});
    body.setPoint(i++, {-0.5f * R,  R});
    body.setPoint(i++, {-0.75f * R, R + 0.6f * R});
    // Left side back up (closes toward the first dome point).
    body.setPoint(i++, {-R, R});
    body.setOrigin({0.f, 0.f});
}
bool Ghost::canMove(float x, float y, const Maze& maze)
{
    // Same fix as Player::canMove: test a box centered on (x, y) - the
    // ghost's actual position - instead of one shifted down-and-right by
    // a full body-width, which caused phantom wall collisions near the
    // top row and left column of the maze.
    float r = GHOST_RADIUS - 1.f;
    return !maze.isWallPixel(x - r, y - r) &&
           !maze.isWallPixel(x + r, y - r) &&
           !maze.isWallPixel(x - r, y + r) &&
           !maze.isWallPixel(x + r, y + r);
}
void Ghost::chooseDirection(const Maze& maze)
{
    std::vector<Direction> choices;
    if (direction != Direction::Down &&
        canMove(position.x, position.y - speed, maze))
        choices.push_back(Direction::Up);
    if (direction != Direction::Up &&
        canMove(position.x, position.y + speed, maze))
        choices.push_back(Direction::Down);
    if (direction != Direction::Right &&
        canMove(position.x - speed, position.y, maze))
        choices.push_back(Direction::Left);
    if (direction != Direction::Left &&
        canMove(position.x + speed, position.y, maze))
        choices.push_back(Direction::Right);
    if (!choices.empty())
        direction = choices[rand() % choices.size()];
}
void Ghost::update(const Maze& maze)
{
    float nextX = position.x;
    float nextY = position.y;
    switch (direction)
    {
    case Direction::Up:
        nextY -= speed;
        break;
    case Direction::Down:
        nextY += speed;
        break;
    case Direction::Left:
        nextX -= speed;
        break;
    case Direction::Right:
        nextX += speed;
        break;
    default:
        break;
    }
    if (canMove(nextX, nextY, maze))
    {
        position = {nextX, nextY};
    }
    else
    {
        chooseDirection(maze);
    }
    if (rand() % 45 == 0)
        chooseDirection(maze);
    body.setPosition(position);
    // Eyes stay near the top of the dome; pupils shift toward the
    // direction the ghost is currently moving.
    sf::Vector2f eyeOffset(GHOST_RADIUS * 0.38f, -GHOST_RADIUS * 0.25f);
    eyeLeft.setPosition({position.x - eyeOffset.x, position.y + eyeOffset.y});
    eyeRight.setPosition({position.x + eyeOffset.x, position.y + eyeOffset.y});
    sf::Vector2f look(0.f, 0.f);
    switch (direction)
    {
        case Direction::Up:    look = {0.f, -1.f}; break;
        case Direction::Down:  look = {0.f, 1.f};  break;
        case Direction::Left:  look = {-1.f, 0.f}; break;
        case Direction::Right: look = {1.f, 0.f};  break;
        default: break;
    }
    float pupilShift = GHOST_RADIUS * 0.14f;
    pupilLeft.setPosition({eyeLeft.getPosition().x + look.x * pupilShift,
                            eyeLeft.getPosition().y + look.y * pupilShift});
    pupilRight.setPosition({eyeRight.getPosition().x + look.x * pupilShift,
                             eyeRight.getPosition().y + look.y * pupilShift});
}
void Ghost::draw(sf::RenderWindow& window)
{
    sf::Vector2f offset(0.f, static_cast<float>(HUD_HEIGHT));
    sf::ConvexShape drawBody = body;
    drawBody.move(offset);
    window.draw(drawBody);
    sf::CircleShape le = eyeLeft, re = eyeRight, lp = pupilLeft, rp = pupilRight;
    le.move(offset); re.move(offset); lp.move(offset); rp.move(offset);
    window.draw(le);
    window.draw(re);
    window.draw(lp);
    window.draw(rp);
}
sf::Vector2f Ghost::getPosition() const
{
    return position;
}
sf::FloatRect Ghost::getBounds() const
{
    return body.getGlobalBounds();
}
void Ghost::reset()
{
    position = sf::Vector2f(17 * TILE_SIZE + TILE_SIZE / 2.f, TILE_SIZE + TILE_SIZE / 2.f); // centered on tile (1,17)
    direction = Direction::Left;
    body.setPosition(position);
}