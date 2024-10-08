#include "Button.hpp"


/*
Constructor
Initializes the button’s position and size using a sf::RectangleShape.
Loads a font and sets the button’s text properties (font, size, position within the button).
Defines the default colors for different button states (normal, hover, active).

*/

      Button::Button(float x, float y, float width, float height, const std::string &buttonText) {
        // Set button shape
        shape.setPosition(x, y);
        shape.setSize(sf::Vector2f(width, height));

        // Load font
        if (!font.loadFromFile("Fonts/bebas/Bebas-Regular.ttf")) {
            std::cerr << "Error loading font\n";
        }

        // Set text properties
        text.setFont(font);
        text.setString(buttonText);
        text.setFillColor(sf::Color::White);
        text.setCharacterSize(24);
        sf::FloatRect textBounds = text.getLocalBounds();
        text.setPosition(
            x + (width / 2.0f) - (textBounds.width / 2.0f), 
            y + (height / 2.0f) - (textBounds.height / 2.0f)
        ); // Set text in middle of the button

        // Set default colors
        normalColor = sf::Color(40,60,30); // dark green
        hoverColor = sf::Color(60,80,50);  // lighter green
        activeColor = sf::Color(50, 70, 40);   // darker green
        shape.setFillColor(normalColor);

        isHovered = false;
    }

/*
This method is responsible for drawing the button and its text on the given sf::RenderWindow. 
The draw method should be called in the game loop to render the button.
*/
 void Button::draw(sf::RenderWindow &window) {
        window.draw(shape);
        window.draw(text);
    }



    /*
Updates the state of the button based on the mouse position.
If the mouse is hovering over the button, it changes the button’s color to the hoverColor.
If the mouse leaves the button, it resets the color to normalColor

*/


 void Button::update(const sf::Vector2i &mousePos) {
        if (shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
            if (!isHovered) {
                shape.setFillColor(hoverColor); // Hover effect
                isHovered = true;
            }
        } else {
            shape.setFillColor(normalColor); // Reset to default
            isHovered = false;
        }
    }

    /*
This method checks if the button is clicked (i.e., if the left mouse button is pressed while the cursor is over the button).
If the button is clicked, it changes the button's color to activeColor and returns true, otherwise it returns false.

*/

 bool Button::isClicked(const sf::Vector2i &mousePos, sf::Event event) {
        if (shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                shape.setFillColor(activeColor); // Active (clicked) state
                return true;
            }
        }
        return false;
    }


// Sets the  color of the button. 
// will display when it is not being hovered over or clicke
void Button::setButtonColor(const sf::Color& color) {
    normalColor = color;
    shape.setFillColor(normalColor);
}



// Sets the color of the button when the mouse is hovering over it. 
// This color provides visual feedback to the user that the button 
// is interactive and ready to be clicked.
void Button::setHoverColor(const sf::Color& color) {
    hoverColor = color;
}


// Sets the color of the button when it is in the active state (i.e., 
// when it has been clicked). This color indicates to the user that 
// the button is currently being pressed.
void Button::setActiveColor(const sf::Color& color) {
    activeColor = color;
}

