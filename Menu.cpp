
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Button.hpp"
#include "Menu.hpp"



/*
The Menu class in your code is responsible for displaying an interactive menu within an SFML window. 
It allows the user to input the number of players and their names for a game, 
using both a button and keyboard inputs. Here's a breakdown of its functionality:
*/


/*

loadMenue-this method takes two parameters:

    int &totalPlayers: A reference to an integer that stores the total number of players entered by the user.
    sf::RenderWindow &window: A reference to the SFML window where the menu is displayed.

Returns: A vector of strings containing the names of the players.
*/

    std::vector<std::string> Menu::loadMenu(int &totalPlayers, sf::RenderWindow &window)
    {
        // Creating vector of names of players
        std::vector<std::string> names;
        totalPlayers = 0;
        int currTurn = -1;

        Button button(220, 200, 150, 100, "Submit");
        button.setButtonColor(sf::Color::Blue); // Set the normal color
        button.setHoverColor(sf::Color::Cyan); // Set the hover color


      // Load background texture
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("images/menu.png")) {
        std::cerr << "Error loading background texture\n";
        return names; // Return empty names vector if there's an error
    }

    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture); // Set the texture to the sprite

    // Scale the background sprite to fit the window
    sf::Vector2u windowSize = window.getSize(); // Get the window size
    float scaleX = static_cast<float>(windowSize.x) / backgroundTexture.getSize().x; // Calculate scale for width
    float scaleY = static_cast<float>(windowSize.y) / backgroundTexture.getSize().y; // Calculate scale for height
    backgroundSprite.setScale(scaleX, scaleY); // Set the scale to the sprite

        




        // Initializing the text we will use along with the font
        //Initializes a sf::Font and sf::Text object for displaying text within the menu.
        sf::Font menuFont;
        if (!menuFont.loadFromFile("Fonts/bebas/Bebas-Regular.ttf")) {
            std::cerr << "Error loading font\n";
            return names; // Return empty names vector if there's an error
        }

        sf::Text menutext; // This is an instance of the sf::Text class, which is part of the SFML (Simple and Fast Multimedia Library) that allows you to display text to screen app
        menutext.setFont(menuFont);
        menutext.setCharacterSize(48);
        menutext.setFillColor(sf::Color::White);

        //Sets up a string menuString to guide the user 
        std::string menuString = "Enter number of players(Between 2-8)\n";
        menutext.setString(menuString); //put the string in the obj Menutext for display
        menutext.setPosition(100, 10);
        std::string inputString = "";

        bool totalPlayersKnown = false; // We dont know the total number of player that will play the game

        


        // this window will only show as long as we are inputing the names of players
        //window open until the user closes it or all players' names are entered.
        while (window.isOpen() && currTurn < totalPlayers)
        {
            sf::Event eve;
            if (totalPlayersKnown)
            {
                while (window.pollEvent(eve)) //checks for various types of events, including key presses and text input.
                {
                    if (eve.type == sf::Event::Closed) // If cross/close is clicked/pressed
                        window.close();

                    // Check if submit button is clicked
                    if (button.isClicked(sf::Mouse::getPosition(window), eve) 
                    && !inputString.empty())
                    {
                        names[currTurn] = inputString;
                        currTurn++;
                        menuString = "Enter name for Player " + std::to_string(currTurn + 1) + "\n";
                        inputString = "";
                        menutext.setString(menuString + inputString);
                    }

                    // If enter key is pressed
                    if (eve.type == sf::Event::KeyPressed && eve.key.code == sf::Keyboard::Enter)
                    {
                        // If input is nothing
                        if (!inputString.empty())
                        {
                            names[currTurn] = inputString;
                            currTurn++;
                            menuString = "Enter name for Player " + std::to_string(currTurn + 1) + "\n";
                            inputString = "";
                            menutext.setString(menuString + inputString);
                        }
                    }

                    // Reading players input
                    if (eve.type == sf::Event::TextEntered)
                    {
                        // Check if the input is a backspace
                        if (eve.text.unicode == '\b' && !inputString.empty())
                        {
                            // Remove the last character if backspace is pressed
                            inputString.pop_back();
                        }
                        // Check if the input is valid and printable (ignoring control characters)
                        else if (eve.text.unicode < 128 && eve.text.unicode > 31)
                        {
                            inputString += static_cast<char>(eve.text.unicode); // Append the character to the string
                        }
                        menutext.setString(menuString + inputString);
                    }
                }
            }
            else
            {
                while (window.pollEvent(eve))
                {
                    if (eve.type == sf::Event::Closed) // If cross/close is clicked/pressed
                        window.close();

                    // Check if submit button is clicked
                    if (button.isClicked(sf::Mouse::getPosition(window), eve) && !inputString.empty())
                    {
                        //convert string to int
                        // check if input of user is between 2-8 players
                        if (std::stoi(inputString) >= 2 && std::stoi(inputString) <= 8)
                        {
                            totalPlayers = std::stoi(inputString); //string to int
                            currTurn = 0;
                            totalPlayersKnown = true;
                            menuString = "Enter name for Player " + std::to_string(currTurn + 1) + "\n";
                            for (int i = 0; i < totalPlayers; i++) // Initialize the names vector
                                names.push_back(std::string());
                        }
                        inputString = "";
                        menutext.setString(menuString + inputString);
                    }

                    // If enter key is pressed
                    if (eve.type == sf::Event::KeyPressed && eve.key.code == sf::Keyboard::Enter)
                    {
                        if (!inputString.empty())
                        {
                            // keep reading until iser input 2-8 players
                            if (std::stoi(inputString) >= 2 && std::stoi(inputString) <= 8)
                            {
                                totalPlayers = std::stoi(inputString);
                                currTurn = 0;
                                totalPlayersKnown = true;
                                menuString = "Enter name for Player " + std::to_string(currTurn + 1) + "\n";
                                for (int i = 0; i < totalPlayers; i++) // Initialize the names vector
                                    names.push_back(std::string());
                            }
                            inputString = "";
                            menutext.setString(menuString + inputString);
                        }
                    }

                    // Enter number of players
                    if (eve.type == sf::Event::TextEntered)
                    {
                        // Check if the input is a backspace
                        if (eve.text.unicode == '\b' && !inputString.empty())
                        {
                            // Remove the last character if backspace is pressed
                            inputString.pop_back();
                        }
                        // Check if the input is valid and printable (ignoring control characters)
                        else if (eve.text.unicode >= '0' && eve.text.unicode <= '9')
                        {
                            inputString += static_cast<char>(eve.text.unicode); // Append the character to the string
                        }
                        menutext.setString(menuString + inputString);
                    }
                }
            }

            button.update(sf::Mouse::getPosition(window));
            window.clear(sf::Color(70, 120, 60)); // create a background color with RGB values
              // Draw the background
            window.draw(backgroundSprite);
            window.draw(menutext);
            button.draw(window);
            window.display();
        }
     for (size_t i = 0; i < names.size(); ++i) {
        std::cout << "[" << i << "] " << names[i] << std::endl;
    }
        return names;
    }
