/*
I have decided to take an incremental development approach.I have decided to take an sequential	development approach in creating my program.
I have started off by printing the basic empty board and then followed it by displaying one of the two provided boards to work with.
I then worked on developing a way to put a player on the selected map with a set coordinate and direction.
I incrementally added a feature to my program and tested each feature out with input validations and tested their functionality.
This sequencial approach helped me build my program in a more sequential manner so when using multiple intertwined files, it is easier.
The first issue that I faced was trying to get one of the boards to display. I was able to print out the board but couldn’t save it to have a player positioned on it.
I was a bit confused with the concept of when to use pass by reference and pass by values. I then struggled with a few input validations where the whole line needed to be read in several pieces.
I was also not able to stop my program from displaying an unused map when the user wanted to set the starting position of the arrow.
*/

#include "game.h"
#include <iomanip>
#include "helper.h"
#include "board.h"

#include <vector>
using std::string;
// empty board declaration
void emptyboard();
// student information function declaration
void showStudentInformation(string name, string id, string email);

string first_input(string input)
{
    // input validation for menu input
    while (input != "1" && input != "2" && input != "3")
    {
        std::cout << "Welcome to Car Board" << std::endl;
        std::cout << "--------------------" << std::endl;
        std::cout << "1. Play game" << std::endl;
        std::cout << "2. Show student's information" << std::endl;
        std::cout << "3. Quit" << std::endl;
        std::cout << "Please enter your choice: ";
        input = Helper::readInput();
    }
    return input;
}
// prints name,id and eamil
void showStudentInformation(string name, string id, string email)
{
    std::cout << "--------------------" << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "NO: s" << id << std::endl;
    std::cout << "Email: s" << email << std::endl;
    std::cout << "--------------------" << std::endl;
}

string removespace(string s)
{
    // removes whitespaces
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == ' ')
        {
            s.erase(s.begin() + i);
            i--;
        }
    }
    return s;
}
// prints menu options
void menu()
{
    std::cout << "Welcome to Car Board" << std::endl;
    std::cout << "--------------------" << std::endl;
    std::cout << "1. Play game" << std::endl;
    std::cout << "2. Show student's information" << std::endl;
    std::cout << "3. Quit" << std::endl;
    std::cout << "Please enter your choice: ";
}

int main()
{

    bool play = true;

    while (play)
    {
        menu();
        string input = Helper::readInput();

        // checks if input is number
        while (Helper::isNumber(input) == false)
        {
            menu();
            // prompts user to give first input
            input = Helper::readInput();
        }

        input = first_input(input);
        while (input == "2")
        {
            showStudentInformation("Ahnaf Tausif", "3890097", "3890097@student.rmit.edu.au");
            menu();
            input = Helper::readInput();
            input = first_input(input);
        }

        input = removespace(input);

        if (input == "1")
        {
            // prints menu after pressing 1
            std::cout << std::endl;
            std::cout << "You can use the following commands to play the game:" << std::endl;
            std::cout << "load <g>" << std::endl;
            std::cout << "    g: Number of game board to load" << std::endl;
            std::cout << "inint <x>,<y>,<direection>" << std::endl;
            std::cout << "    x: horizontal position of the car on the board (between 0 & 9)" << std::endl;
            std::cout << "    y: vertical position of the car on the board (between 0 & 9)" << std::endl;
            std::cout << "    direction: direction of car's movement(north,south,east,west)" << std::endl;
            std::cout << "forward (or f)" << std::endl;
            std::cout << "turn_left (or 1)" << std::endl;
            std::cout << "turn_right (r)" << std::endl;
            std::cout << "quit" << std::endl;

            emptyboard();
            //starts game
            Game g;
            g.start();
        }
        else if (input == "3")
        {
            std::cout << "GOODBYE!";
            play = false;
        }
    }

    return EXIT_SUCCESS;
}

void emptyboard()
{
    // number headings
    std::cout << "| ";
    for (int i = 0; i < 9; i++)
    {
        std::cout << "|" << (i + 1);
    }
    std::cout << "|" << std::endl;

    // grid

    for (int i = 0; i < 9; i++)
    {
        std::cout << "|" << (i + 1);
        for (int j = 0; j < 9; j++)
        {
            std::cout << "| ";
        }

        std::cout << "|"
                  << "\n";
    }
}
