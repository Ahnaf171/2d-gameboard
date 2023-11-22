#include "game.h"
#include "board.h"
#include "player.h"
#include <vector>


Game::Game()
{

    board = new Board();
    player = new Player();
}

Game::~Game()
{

    delete board;
    delete player;
}

void Game::start()
{

    if (loadBoard())
    {
        if (initializePlayer())
        {
            play();
        }
    }
}

bool Game::loadBoard()
{
    bool brd = true;
    bool brd2 = false;
    while (brd)
    {
        std::cout << "At this stage of the program, only two commands are acceptable:" << std::endl;
        std::cout << "load <g>" << std::endl;
        std::cout << "quit" << std::endl;

        std::string input = Helper::readInput();

        // validation for load input
        while (input != "load 1" && input != "load 2" && input != "quit")
        {
            Helper::printInvalidInput();
            input = Helper::readInput();
        }
        //sets boards to respective ID
        while (input == "load 1" || input == "load 2")
        {
            int id = 0;
            if (input == "load 1" || input == "load 2")
            {
                if (input == "load 1")
                {
                    id = 1;}
                if (input == "load 2")
                {
                    id = 2;}
                    
                    // load chosen board
                    board->load(id);
                    std::cout << "At this stage of the program, only three commands are acceptable: " << std::endl;
                    std::cout << "load <g>" << std::endl;
                    std::cout << "init <x>,<y>,<direction>" << std::endl;
                    std::cout << "quit" << std::endl;
                    input = Helper::readInput();
                    if (input.substr(0, 4) == "init")
                    {
                        brd = false;
                        brd2 = true;
                    }
                }
              
        }
        if (input == "quit")
        {
            brd = false;
            brd2 = false;
        }
        
    }
    return brd2;
}



bool Game::initializePlayer()
{
    Position position;
    std::string direction;
    std::string vect_string;
    Direction direct;

    bool loop = true;
    while (loop)
    {
        std::string input;
        std::cout << "At this stage of the program, only three commands are acceptable: " << std::endl;
        std::cout << "<x>,<y>,<direction>" << std::endl;
        std::cout << "quit" << std::endl;
        std::cin >> input;
        //creates a vector and divides the input into the vector
        std::vector<std::string> vect;
        std::cout << vect_string;
        Helper::splitString(input, vect, ",");
        if(vect.size() == 1){
            loop = false;
        }

        direction = vect[2];
        // set input direction
        if (direction == "north")
        {
            direct = NORTH;
        }
        if (direction == "south")
        {
            direct = SOUTH;
        }
        if (direction == "east")
        {
            direct = EAST;
        }
        if (direction == "west")
        {
            direct = WEST;
        }
        if (direction == "quit")
        {
            loop = false;
        }
        //converts the string to int
        int x = std::stoi(vect[0]);
        int y = std::stoi(vect[1]);

        //allocates x and y coordinates
        position.x = x;
        position.y = y;

        //checks if blocked coordinate is selected
        if(!board->placePlayer(position)){
            Helper::printInvalidInput();
            std::cout<<"This position is blocked!"<<std::endl;
        }

        board->placePlayer(position);

        // use initialise player
        player->initialisePlayer(&position, direct);
        player->updatePosition(position);
        loop = false;
    }
    return true;
}

void Game::play()
{

    std::string command;
    bool game_on = true;
    // keeps looping until quit command
    while (game_on)
    {
        //display current board
        board->display(player);

        std::cout << "Enter command (forward, turn_left, turn_right, quit): ";
        std::cin >> command;

        if (command == COMMAND_FORWARD || command == COMMAND_FORWARD_SHORTCUT)
        {
            PlayerMove moveResult = board->movePlayerForward(player);

            if (moveResult == OUTSIDE_BOUNDS)
            {
                std::cout << "You hit the wall. Try again." << std::endl;
            }
            if (moveResult == CELL_BLOCKED)
            {
                std::cout << "The way is blocked. Try again." << std::endl;
            }
            if (moveResult == PLAYER_MOVED)
            {
            
                game_on = true;
                
            }
        }

        else if (command == COMMAND_TURN_LEFT || command == COMMAND_TURN_LEFT_SHORTCUT)
        {
            player->turnDirection(TURN_LEFT);
        }
        else if (command == COMMAND_TURN_RIGHT || command == COMMAND_TURN_RIGHT_SHORTCUT)
        {
            player->turnDirection(TURN_RIGHT);
        }
        else if (command == COMMAND_QUIT)
        {
            game_on = false;
        }
        else
        {
            std::cout << "Invalid command. Please try again." << std::endl;
        }
    }
}