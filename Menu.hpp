#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Button.hpp"
#include "Game.hpp"



/*
The Menu class in your code is responsible for displaying an interactive menu within an SFML window. 
It allows the user to input the number of players and their names for a game, 
using both a button and keyboard inputs. Here's a breakdown of its functionality:
*/

class Menu
{


public:


/*

loadMenue-this method takes two parameters:

    int &totalPlayers: A reference to an integer that stores the total number of players entered by the user.
    sf::RenderWindow &window: A reference to the SFML window where the menu is displayed.

Returns: A vector of strings containing the names of the players.
*/

    std::vector<std::string> loadMenu(int &totalPlayers, sf::RenderWindow &window);

};


#endif // MENU_HPP
