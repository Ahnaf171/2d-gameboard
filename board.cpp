
#include "board.h"
#include "game.h"
#include "player.h"

#include <iostream>

using std::vector;

const vector<vector<Cell>> Board::BOARD_1 =
    {
        {BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY},
        {EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, BLOCKED, EMPTY, BLOCKED, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED}};

const vector<vector<Cell>> Board::BOARD_2 =
    {
        {BLOCKED, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY}};

Board::Board()
{

    board = new vector<vector<Cell>>(DEFAULT_BOARD_DIMENSION, vector<Cell>(DEFAULT_BOARD_DIMENSION, EMPTY));
}

Board::~Board()
{
    
    delete board;
}

void Board::load(int boardId)
{

    if (boardId == 1)
    {
        *board = BOARD_1;
        //displays board before playing
        display(nullptr);
        
    }
    if (boardId == 2)
    {
        *board = BOARD_2;
         //displays board before playing
        display(nullptr);
    }
}

bool Board::placePlayer(Position position)
{
    bool placeP = true;
    //checks if player is set within the board
    if (position.x < 0 || position.x >= DEFAULT_BOARD_DIMENSION || position.y < 0 || position.y >= DEFAULT_BOARD_DIMENSION)
    {
        Helper::printInvalidInput();
        std::cout << std::endl;
        placeP = true;
    }
    //checks to see if the chosen position is blocked
    else if ((*board)[position.y][position.x] == BLOCKED)
    {
        placeP = false;
    }

    //places player
    else{
        (*board)[position.y][position.x] = PLAYER;
    placeP = true;;
    }
    return placeP;
}

PlayerMove Board::movePlayerForward(Player *player)
{
   
    
    Position nextPosition = player->getNextForwardPosition();
    PlayerMove move = PLAYER_MOVED;

     //checks if player is set within the board
    if (nextPosition.x < 0 || nextPosition.x >= DEFAULT_BOARD_DIMENSION || nextPosition.y < 0 || nextPosition.y >= DEFAULT_BOARD_DIMENSION)
    {
        Helper::printInvalidInput();
        move =  OUTSIDE_BOUNDS;
    }
    //checks to see if the chosen position is blocked
    else if ((*board)[nextPosition.y][nextPosition.x] == BLOCKED)
    {
        Helper::printInvalidInput();
        move =  CELL_BLOCKED;
    }
    // moves player from old to new position
    else{
        Position currentPosition = player->position;
    (*board)[currentPosition.y][currentPosition.x] = EMPTY;
    (*board)[nextPosition.y][nextPosition.x] = PLAYER;
    player->updatePosition(nextPosition);
    }
    
    return move;
}

void Board::display(Player *player)
{
    //print colums of map
    int head_num = 0;
    for (int i = 0; i < DEFAULT_BOARD_DIMENSION + 1; i++)
    {
        if (i == 0)
        {
            std::cout << LINE_OUTPUT << EMPTY_OUTPUT;
        }
        else
        {
            std::cout << LINE_OUTPUT << i - 1;
        }
    }

    std::cout << LINE_OUTPUT << std::endl;
    //print rows of map
    for (const vector<Cell> &row : *board)
    {
        std::cout << LINE_OUTPUT << head_num;
        head_num++;
        for (Cell cell : row)
        {
            if (cell == EMPTY)
            {
                std::cout << LINE_OUTPUT << EMPTY_OUTPUT;
            }
            else if (cell == BLOCKED)
            {
                std::cout << LINE_OUTPUT << BLOCKED_OUTPUT;
            }
            else if (cell == PLAYER)
            {
                std::cout << "|";
                player->displayDirection();
            }
        }
        std::cout << LINE_OUTPUT << std::endl;
    }
}
