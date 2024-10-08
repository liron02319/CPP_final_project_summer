#ifndef DICE_HPP
#define DICE_HPP


#include <SFML/Graphics.hpp>
#include <random>
#include <time.h>
#include <iostream>

/*

Dice class represents a graphical dice for use in a game. 
The class encapsulates the behavior of rolling a dice, 
displaying its current face, and positioning it on the screen using the SFML library for graphics. 

*/

class Dice
{


private:

    sf::Sprite dice_sp;             // Sprite for the dice -in the context of SFML (Simple and Fast Multimedia Library), a sprite is an object used to display a texture (an image) on the screen. The dice_sp will display the die's current face image.
    sf::Texture dice_text;          // Texture for the dice - holds the image of the dice, and dice_sp uses this image for rendering. It could contain all six faces of the die, and specific parts of it are shown based on the current roll.
    sf::RectangleShape die_border;  // Rectangle shape for the die's border -is used to draw rectangles. Here, it is used to create a visible boundary around the die's image to make it stand out visually.
    int currFace;                   // Current face of the dice




public:

    // Constructor: Initializes the die
    Dice();

    // Roll the die: Randomly changes the current face of the die
    void roll();

    // Set the position of the die and its border
    void setPos(float x, float y);

    // This function draws both the dice sprite and the border to the SFML window.
    void draw(sf::RenderWindow &win);

    // Get the current face of the die
    int getCurrFace() const ;


};

#endif // DICE_HPP