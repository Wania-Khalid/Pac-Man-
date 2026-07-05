#include "Player.h"
#include "Constants.h"
#include <cmath>
namespace
{
    constexpr float PI = 3.14159265f;
    float directionToDegrees(Direction dir)
    {
        switch (dir)
        {
            case Direction::Right: return 0.f;
            case Direction::Down:  return 90.f;
            case Direction::Left:  return 180.f;
            case Direction::Up:    return 270.f;
            default:               return 0.f;
        }
    }
}
Player::Player()
{
    body.setRadius(PLAYER_RADIUS);
    body.setOrigin({PLAYER_RADIUS, PLAYER_RADIUS});
    body.setFillColor(sf::Color::Yellow);
    mouth.setPointCount(3);
    mouth.setFillColor(sf::Color::Black);
    position = sf::Vector2f(TILE_SIZE + TILE_SIZE / 2.f, TILE_SIZE + TILE_SIZE / 2.f); // centered on tile (1,1), matching where pellets are placed
    body.setPosition(position);
    speed = PLAYER_SPEED;
    direction = Direction::None;
    lives = MAX_LIVES;
    updateMouth();
}
bool Player::canMove(float x, float y, const Maze& maze)
{
    float r = PLAYER_RADIUS - 1.f;
    return !maze.isWallPixel(x - r, y - r) &&
           !maze.isWallPixel(x + r, y - r) &&
           !maze.isWallPixel(x - r, y + r) &&
           !maze.isWallPixel(x + r, y + r);
}
void Player::setDirection(Direction dir)
{
    direction = dir;
}
void Player::update(const Maze& maze)
{
    float nextX = position.x;
    float nextY = position.y;
    switch (direction)
    {
        case Direction::Up:    nextY -= speed; break;
        case Direction::Down:  nextY += speed; break;
        case Direction::Left:  nextX -= speed; break;
        case Direction::Right: nextX += speed; break;
        default: break;
    }
    if (canMove(nextX, nextY, maze))
    {
        position.x = nextX;
        position.y = nextY;
    }
    body.setPosition(position);

    if (direction != Direction::None)
        animTime += 0.15f;
    updateMouth();
}
void Player::updateMouth()
{
    // Half-angle of the mouth opening oscillates to create a chomping animation.
    float halfAngleDeg = 8.f + 20.f * std::fabs(std::sin(animTime));
    float facingDeg = directionToDegrees(direction == Direction::None ? Direction::Right : direction);
    float a1 = (facingDeg - halfAngleDeg) * PI / 180.f;
    float a2 = (facingDeg + halfAngleDeg) * PI / 180.f;
    mouth.setPoint(0, {0.f, 0.f});
    mouth.setPoint(1, {PLAYER_RADIUS * std::cos(a1), PLAYER_RADIUS * std::sin(a1)});
    mouth.setPoint(2, {PLAYER_RADIUS * std::cos(a2), PLAYER_RADIUS * std::sin(a2)});
    mouth.setPosition(position);
}
void Player::draw(sf::RenderWindow& window)
{
    sf::CircleShape drawBody = body;
    drawBody.move({0.f, static_cast<float>(HUD_HEIGHT)});
    window.draw(drawBody);
    sf::ConvexShape drawMouth = mouth;
    drawMouth.move({0.f, static_cast<float>(HUD_HEIGHT)});
    window.draw(drawMouth);
}
sf::FloatRect Player::getBounds() const
{
    return body.getGlobalBounds();
}
sf::Vector2f Player::getPosition() const
{
    return position;
}
int Player::getLives() const
{
    return lives;
}
void Player::loseLife()
{
    lives--;
}
void Player::reset()
{
    position = sf::Vector2f(TILE_SIZE + TILE_SIZE / 2.f, TILE_SIZE + TILE_SIZE / 2.f); // centered on tile (1,1), matching where pellets are placed
    body.setPosition(position);
    direction = Direction::None;
    animTime = 0.f;
    updateMouth();
}