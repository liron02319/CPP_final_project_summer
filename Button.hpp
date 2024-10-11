#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

/*
    The Button class represents a clickable button with hover and click effects, designed for use in SFML applications.
    
    The button is composed of a rectangular shape and text. It supports custom font loading and has three distinct 
    visual states: normal, hover (when the mouse is over the button), and active (when the button is clicked).

    Key Features:
    - Display text on the button.
    - Change the button’s color when the mouse hovers over it or when it's clicked.
    - Easily integrate into SFML applications and respond to mouse events.
    
    Methods:
    - Constructor: Initializes the button’s position, size, colors, and text.
    - draw(): Renders the button and text to the provided SFML window.
    - update(): Updates the button's state based on the mouse position (handles hover effects).
    - isClicked(): Checks if the button was clicked (i.e., the left mouse button was pressed over the button).


    SFML (Simple and Fast Multimedia Library) does not provide a built-in, 
    default button class or UI component like some other GUI libraries. 
    Instead, SFML focuses on providing low-level graphics functionality, 
    leaving the creation of user interface components, like buttons, to the developer
*/


class Button {

private:
    sf::RectangleShape shape; //This represents the shape of the button. It is a rectangular area that defines the button's size and position.
    sf::Text text; //The text that will be displayed on the button.
    sf::Font font; //The font used to render the text on the button.
    sf::Color normalColor; //The default button color when it’s not being interacted with.
    sf::Color hoverColor; //The color when the mouse is hovering over the button.
    sf::Color activeColor; //The color when the button is clicked (active state).
    bool isHovered; //A boolean value to track whether the mouse is currently hovering over the button or not.

public:

/*
Constructor
Initializes the button’s position and size using a sf::RectangleShape.
Loads a font and sets the button’s text properties (font, size, position within the button).
Defines the default colors for different button states (normal, hover, active).

*/
    Button(float x, float y, float width, float height, const std::string &buttonText) ;




/*
This method is responsible for drawing the button and its text on the given sf::RenderWindow. 
The draw method should be called in the game loop to render the button.
*/

    void draw(sf::RenderWindow &window) ;


/*
Updates the state of the button based on the mouse position.
If the mouse is hovering over the button, it changes the button’s color to the hoverColor.
If the mouse leaves the button, it resets the color to normalColor

*/
    void update(const sf::Vector2i &mousePos);

/*
This method checks if the button is clicked (i.e., if the left mouse button is pressed while the cursor is over the button).
If the button is clicked, it changes the button's color to activeColor and returns true, otherwise it returns false.

*/
    bool isClicked(const sf::Vector2i &mousePos, sf::Event event);


// Sets the  color of the button. 
// will display when it is not being hovered over or clicke
    void setButtonColor(const sf::Color& color);



// Sets the color of the button when the mouse is hovering over it. 
// This color provides visual feedback to the user that the button 
// is interactive and ready to be clicked.
    void setHoverColor(const sf::Color& color);

// Sets the color of the button when it is in the active state (i.e., 
// when it has been clicked). This color indicates to the user that 
// the button is currently being pressed.
    void setActiveColor(const sf::Color& color);
    




  

};

#endif // BUTTON_HPP