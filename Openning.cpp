#include "Openning.hpp"
#include <SFML/Graphics.hpp>
#include "Button.hpp"
#include <iostream>

#ifdef _WIN32
    #include <windows.h> // For opening URL in Windows
#elif __APPLE__
    #include <cstdlib>   // For opening URL in macOS
#elif __linux__
    #include <cstdlib>   // For opening URL in Linux
#endif

void Openning::displayOpening(sf::RenderWindow &window) {
    // Load background texture
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("images/winner.jpg")) {
        std::cerr << "Error loading background texture\n";
        return;
    }

    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);

    // Get the size of the window and the texture
    sf::Vector2u windowSize = window.getSize();
    sf::Vector2u textureSize = backgroundTexture.getSize();

    // Scale the background sprite to fit the window
    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;
    backgroundSprite.setScale(scaleX, scaleY); // Set the scaling factors

    // Create the buttons
    Button playButton(50, 200, 150, 100, "Play");
    playButton.setButtonColor(sf::Color::Green); // Set the normal color
    playButton.setHoverColor(sf::Color::Yellow); // Set the hover color

    Button rulesButton(50, 350, 150, 100, "Rules");
    rulesButton.setButtonColor(sf::Color::Blue); // Set the normal color
    rulesButton.setHoverColor(sf::Color::Cyan); // Set the hover color

    Button exitButton(50, 500, 150, 100, "Exit");
    exitButton.setButtonColor(sf::Color::Red); // Set the normal color
    exitButton.setHoverColor(sf::Color::Magenta); // Set the hover color

    // Load font for the text label
    sf::Font font;
    if (!font.loadFromFile("Fonts/bebas/Bebas-Regular.ttf")) {
        std::cerr << "Error loading font\n";
        return;
    }

    // Create the text label
    sf::Text developerText;
    developerText.setFont(font);
    developerText.setString("Developed By Liron Cohen");
    developerText.setCharacterSize(24); // Set the font size
    developerText.setFillColor(sf::Color::White); // Set text color
    developerText.setPosition(20, 670); // Position below the buttons (adjust Y as needed)

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Check button clicks
            if (playButton.isClicked(sf::Mouse::getPosition(window), event)) {
                return; // Exit the opening screen and move to the menu
            }
            if (rulesButton.isClicked(sf::Mouse::getPosition(window), event)) {
                // Open the link in the default web browser
                // Open the link in the default web browser
                #ifdef _WIN32
                    ShellExecute(0, 0, L"https://github.com/liron02319/CPP_final_project_summer/tree/main", 0, 0, SW_SHOW);
                #elif __APPLE__
                    system("open https://github.com/liron02319/CPP_final_project_summer/tree/main");
                #elif __linux__
                    system("xdg-open https://github.com/liron02319/CPP_final_project_summer/tree/main");
                #endif
            }
            if (exitButton.isClicked(sf::Mouse::getPosition(window), event)) {
                window.close(); // Close the application
            }
        }

        // Update button states
        playButton.update(sf::Mouse::getPosition(window));
        rulesButton.update(sf::Mouse::getPosition(window));
        exitButton.update(sf::Mouse::getPosition(window));

        // Drawing
        window.clear();
        window.draw(backgroundSprite); // Draw the scaled background
        playButton.draw(window); // Draw the "Play" button
        rulesButton.draw(window); // Draw the "Rules" button
        exitButton.draw(window); // Draw the "Exit" button
        window.draw(developerText); // Draw the developer text
        window.display();
    }
}