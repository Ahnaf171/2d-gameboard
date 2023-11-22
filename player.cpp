#include "player.h"

Position::Position()
{

    x = 0;
    y = 0;
}

Position::Position(int x, int y)
{

    this->x = x;
    this->y = y;
}

Player::Player()
{

    position = Position(0, 0);
    direction = NORTH;
    moves = 0;
}

void Player::initialisePlayer(Position *position, Direction direction)
{

    this->position = *position;
    this->direction = direction;
    moves = 0;
}

void Player::turnDirection(TurnDirection turnDirection)
{

    if (turnDirection == TURN_LEFT)
    {
        if (direction == NORTH)
        {
            direction = WEST;
        }
        else if (direction == WEST)
        {
            direction = SOUTH;
        }
        else if (direction == SOUTH)
        {
            direction = EAST;
        }
        else if (direction == EAST)
        {
            direction = NORTH;
        }
    }
    if (turnDirection == TURN_RIGHT)
    {
        if (direction == NORTH)
        {
            direction = EAST;
        }
        else if (direction == WEST)
        {
            direction = NORTH;
        }
        else if (direction == SOUTH)
        {
            direction = WEST;
        }
        else if (direction == EAST)
        {
            direction = SOUTH;
        }
    }
}

Position Player::getNextForwardPosition()
{
    Position nextPosition = this->position;

    if (direction == NORTH)
    {
        nextPosition.y = nextPosition.y - 1;
    }
    else if (direction == EAST)
    {
        nextPosition.x = nextPosition.x + 1;
    }
    else if (direction == SOUTH)
    {
        nextPosition.y = nextPosition.y + 1;
    }
    else if (direction == WEST)
    {
        nextPosition.x = nextPosition.x - 1;
    }

    return nextPosition;
}

void Player::updatePosition(Position position)
{
  
    this->position = position;
    moves++;
}

void Player::displayDirection()
{

    if (direction == NORTH)
    {
        std::cout << DIRECTION_ARROW_OUTPUT_NORTH;
    }
    if (direction == SOUTH)
    {
        std::cout << DIRECTION_ARROW_OUTPUT_SOUTH;
    }
    if (direction == WEST)
    {
        std::cout << DIRECTION_ARROW_OUTPUT_WEST;
    }
    if (direction == EAST)
    {
        std::cout << DIRECTION_ARROW_OUTPUT_EAST;
    }
}
