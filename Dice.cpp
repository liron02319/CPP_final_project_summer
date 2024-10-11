#include "Dice.hpp"

#include <SFML/Graphics.hpp>
#include <random>
#include <time.h>
#include <iostream>

/*

Dice class represents a graphical dice for use in a game. 
The class encapsulates the behavior of rolling a dice, 
displaying its current face, and positioning it on the screen using the SFML library for graphics. 

*/


    // Constructor: Initializes the die
   Dice::Dice()
    {
        // Loading the die sprite sheet
        if (!dice_text.loadFromFile("images/Die.png")) {
            std::cerr << "Error loading die texture\n"; // Error message if texture loading fails
        }
        currFace = 0; // Initialize current face to 0

        // Set up the border rectangle
        die_border.setFillColor(sf::Color::Black);    // Set the fill color to black (transparent)-ut since we don't need to show the inside color, this color could be made fully transparent.
        die_border.setOutlineThickness(5);            // Set the border thickness
        die_border.setOutlineColor(sf::Color::Black); // Set the border color
        srand(static_cast<unsigned int>(time(0)));    // Seed random number generator with current time-This seeds the random number generator using the current time, ensuring different dice rolls each time the program is run.
    }

    // Roll the die: Randomly changes the current face of the die
    /*
         sf::Texture: Stores the image data.
        sf::Sprite: Displays the texture and allows manipulation (e.g., scaling, rotation).
    */
    
    void Dice::roll()
    {
        int num = rand() % 6; // Generate a random number from 0 to 5
        switch (num)          // Handle each face of the die by setting the corresponding texture
        {
        case 0:
            dice_sp.setTexture(dice_text);
            dice_sp.setTextureRect(sf::IntRect(30, 25, 260, 260)); // Set texture for face 1
            break;
        case 1:
            dice_sp.setTexture(dice_text);
            dice_sp.setTextureRect(sf::IntRect(330, 25, 260, 260)); // Set texture for face 2
            break;
        case 2:
            dice_sp.setTexture(dice_text);
            dice_sp.setTextureRect(sf::IntRect(640, 25, 260, 260)); // Set texture for face 3
            break;
        case 3:
            dice_sp.setTexture(dice_text);
            dice_sp.setTextureRect(sf::IntRect(22, 375, 260, 260)); // Set texture for face 4
            break;
        case 4:
            dice_sp.setTexture(dice_text);
            dice_sp.setTextureRect(sf::IntRect(330, 375, 260, 260)); // Set texture for face 5
            break;
        case 5:
            dice_sp.setTexture(dice_text);
            dice_sp.setTextureRect(sf::IntRect(640, 375, 260, 260)); // Set texture for face 6
            break;
        }

        currFace = num + 1; // Update the current face to match the rolled number (1-6)
        dice_sp.setScale(0.2f, 0.2f); // Scale the die sprite for display-This scales the die image down to a smaller size, making it fit the screen more appropriately (20% of the original image size).
        
        // Update the border size to match the die sprite's size, with a slight margin
        sf::FloatRect dieBounds = dice_sp.getGlobalBounds(); // Get the global bounds of the die sprite-Retrieves the bounding box of the die sprite, which contains its width, height, and position.
        die_border.setSize(sf::Vector2f(dieBounds.width + 10, dieBounds.height + 10));  // Add 10 pixels for the border-Adjusts the size of the die_border to be slightly larger than the die sprite (by adding 10 pixels to its dimensions), creating a border around the die.
        die_border.setPosition(dice_sp.getPosition().x - 5, dice_sp.getPosition().y - 5); // Center the border around the die
    }

    // Set the position of the die and its border
    void Dice::setPos(float x, float y)
    {
        dice_sp.setPosition(x, y); // Set the position of the die sprite
        die_border.setPosition(x - 5, y - 5); // Position the border slightly offset-The border is positioned slightly offset to center it around the die sprite.
    }

    // This function draws both the dice sprite and the border to the SFML window.
    void Dice::draw(sf::RenderWindow &win)
    {
        win.draw(die_border); // Draw the die's border
        win.draw(dice_sp);    // Draw the die sprite
    }

    // Get the current face of the die
    int Dice::getCurrFace() const {
        return currFace; // Return the current face of the die
    }
