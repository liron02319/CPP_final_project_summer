#include "Slot.hpp"
#include <cmath>  // Required for std::pow
#include <SFML/Graphics.hpp>
#include <iostream>

/*
 * Slot Class
 * 
 * This class represents a property or location slot in a board game (similar to Monopoly).
 * Each Slot can represent different types of properties such as streets, railroads, or companies. 
 * It holds all the essential attributes required for game mechanics, such as:
 * 
 * - Slot appearance: Represented visually with a rectangle shape (`slotShape`) and associated text for the name (`slotName`) and price (`slotPrice`).
 * - Street and building information: Contains details about the slot's ownership, price, rent values, and the number of houses or hotels built on it.
 * - Railroad and company identification: Determines if the slot represents a railroad or company.
 * 
 * Main Features:
 * - The `Slot` can be positioned and resized on the game board using `setPos()` and `setSizeAll()`.
 * - It can be visually updated with a name, price, and different colors depending on the property type.
 * - It supports drawing to an SFML window, rendering the property along with any houses or hotels built on it.
 * - The class can calculate rent based on the number of houses or hotels.
 */


    // Constructor
    Slot::Slot(int Index, const std::string &n, const sf::Color color, int p, int r, int hPrice, int rWithHouse, int rWithHotel)
        : slotNum(Index), 
          name(n), 
          colorGroup(color), 
          price(p), 
          rent(r), 
          housePrice(hPrice), 
          rentWithHouse(rWithHouse), 
          rentWithHotel(rWithHotel), 
          houses(0), 
          hotels(0), 
          isRail(false), 
          isCompany(false), 
          isOwned(false), 
          ownerName("") 
          // Initialize members using an initialization list

    {    

        // Initialize the shape for the slot
        slotShape.setSize(sf::Vector2f(100, 50)); // Set size of the slot visual
        slotShape.setFillColor(colorGroup);       // Set the street color slot visual
        slotShape.setOutlineThickness(2); //The outline is a border around the slot's rectangle.
        slotShape.setOutlineColor(sf::Color::Black); //his sets the color of the outline to black. The border of the slot will be black, regardless of the color of the slot itself.

        slotHouse.setFillColor(sf::Color::Green);
        slotHouse.setOutlineThickness(2);
        slotHouse.setOutlineColor(sf::Color::Black);
    }


    // Getter and Setter for slot street price
    int Slot::getPrice() const {
        return price;
    }

    void Slot::setPrice(int newPrice) {
        price = newPrice;
    }

    // Getter and Setter for if the slot street isOwned
    bool Slot::getIsOwned() const {
        return isOwned;
    }

    void Slot::setIsOwned(bool owned) {
        isOwned = owned;
    }

    // Getter and Setter for  housePrice
    int Slot::getHousePrice() const {
        return housePrice;
    }

    void Slot::setHousePrice(int newHousePrice) {
        housePrice = newHousePrice;
    }

    // Getter and Setter for ownerName
    std::string Slot::getOwnerName() const {
        return ownerName;
    }

    void Slot::setOwnerName(const std::string &newOwner) {
        ownerName = newOwner;
    }

    // Getter and Setter for how much houses in the slot
    int Slot::getHouses() const {
        return houses;
    }

    void Slot::setHouses(int newHouses) {
        houses = newHouses;
    }

       // Setter for houses (to increment houses)
    void Slot::addHouse() {
        // Increment the number of houses
       this->setHouses(++houses);

        //std::cout << "setHousessetHouses: " << houses << std::endl;
       // std::cout << "getHouses: " << getHouses() << std::endl;


    }

    // Getter and Setter for how much hotels in the slot
    int Slot::getHotels() const {
        return hotels;
    }

    void Slot::setHotels(int newHotels) {
        hotels = newHotels;
    }

    // Getter and Setter for rent
    int Slot::getRent() const {
        return rent;
    }

    void Slot::setRent(int newRent) {
        rent = newRent;
    }

    // Getter and Setter for rentWithHouse
    int Slot::getRentWithHouse() const {
        return rentWithHouse;
    }

    void Slot::setRentWithHouse(int newRentWithHouse) {
        rentWithHouse = newRentWithHouse;
    }

    // Getter and Setter for rentWithHotel
    int Slot::getRentWithHotel() const {
        return rentWithHotel;
    }

    void Slot::setRentWithHotel(int newRentWithHotel) {
        rentWithHotel = newRentWithHotel;
    }

    // Getter and Setter for isRail- check if slot is a railroad(train)
    bool Slot::getIsRail() const {
        return isRail;
    }

    void Slot::setIsRail(bool rail) {
        isRail = rail;
    }

    // Getter and Setter for check if slot is a isCompany
    bool Slot::getIsCompany() const {
        return isCompany;
    }

    void Slot::setIsCompany(bool company) {
        isCompany = company;
    }

    // Getter and Setter for name of slot street
    std::string Slot::getName() const {
        return name;
    }

    void Slot::setName(const std::string &newName) {
        name = newName;
    }

    // Getter and Setter for colorGroup of the slot
    sf::Color Slot::getColorGroup() const {
        return colorGroup;
    }

    void Slot::setColorGroup(const sf::Color &newColorGroup) {
        colorGroup = newColorGroup;
    }

    // Getter and Setter for slotNum 
    int Slot::getSlotNum() const {
        return slotNum;
    }

    void Slot::setSlotNum(int newSlotNum) {
        slotNum = newSlotNum;
    }


     // Getter for slotShape
    const sf::RectangleShape& Slot::getSlotShape() const {
        return slotShape;  // Returns a reference to the slot shape
    }

    // Setter for slotShape size
    void Slot::setSlotShapeSize(const sf::Vector2f& size) {
        slotShape.setSize(size); // Set the size of slotShape
    }

    // Sets the position of the slot
    void Slot::setPos(float xpos, float ypos)
    {
        slotShape.setPosition(xpos, ypos);         // Position the shape
        slotName.setPosition(xpos + 5, ypos + 5);  // Position name text slightly inside the shape
        slotPrice.setPosition(xpos + 5, ypos + 20);// Position price text slightly below the name
    }

    // Sets the size of the slot and associated elements
    //this sets the size of the rectangle (slotShape) to the width and height provided as arguments.
    //this function is used to set the size of the slotShape, which represents the visual area of the slot on the game board.
    void Slot::setSizeAll(float width, float height)
    {
        slotShape.setSize(sf::Vector2f(width, height)); // Set size of the slot shape
    }

    // Configures the slot sprite and text
    /*
    this function configures both the appearance and the position of the slot, 
    its associated text (name and price), and the houses or hotels. 
    It also sets up whether the slot represents a railroad or a company based on its color.
    */
    void Slot::setSprite(float xpos, float ypos, sf::Font &font, int width, int height)
    {
        slotShape.setSize(sf::Vector2f(width, height));
        slotShape.setPosition(xpos, ypos); // Position the shape
        slotHouse.setSize(sf::Vector2f(width / 4.5, height / 4.5));
        slotHouse.setPosition(xpos, ypos);

        // Set up the slot name text
        slotName.setFont(font);
        slotName.setString(name);
        slotName.setCharacterSize(10); // Adjust text size
        slotName.setFillColor(sf::Color::Black);
        slotName.setPosition(xpos + 5, ypos + 5);

        // Set up the price text
        slotPrice.setFont(font);
        slotPrice.setString("$" + std::to_string(price));
        slotPrice.setCharacterSize(10);
        slotPrice.setFillColor(sf::Color::Black);
        slotPrice.setPosition(xpos + 5, ypos + 20);

        if (colorGroup == sf::Color(0xCAE8E0FF)) // Light blue color group
        {
            isRail = true;
        }
        if (colorGroup == sf::Color::Cyan)
        {
            isCompany = true;
        }
    }

    // Draws the slot and its elements to the SFML window
    //This function is responsible for drawing the slot and its associated elements (such as houses or hotels) to the game window.
    void Slot::draw(sf::RenderWindow &window)
    {
        window.draw(slotShape); // Draw the shape
        int x = slotShape.getPosition().x;
        int y = slotShape.getPosition().y + slotShape.getGlobalBounds().height - slotHouse.getGlobalBounds().height;

        if (hotels == 0) //if no hotels
        {
            for (int i = 0; i < houses; i++)
            {
                slotHouse.setFillColor(sf::Color::Green);
                slotHouse.setPosition(x + (i * slotHouse.getGlobalBounds().width), y);
                window.draw(slotHouse);
            }
        }
        else
        {
            for (int i = 0; i < hotels; i++)
            {
                slotHouse.setFillColor(sf::Color::Red);
                slotHouse.setPosition(x + (i * slotHouse.getGlobalBounds().width), y);
                window.draw(slotHouse);
            }
        }

        window.draw(slotName);  // Draw the name
        window.draw(slotPrice); // Draw the price
    }

    // Calculates the rent based on the number of houses or hotels
    int Slot::calculateRent() const
    {  
        if (hotels > 0)
       {
        return rentWithHotel; 
        }
        else if (houses == 0)
        {
            return rent;
        }
        else
        {
            return rentWithHouse * (std::pow(2, houses - 1)); // Rent increases 2x for each additional house
        }
    }


//same owner check
    bool Slot::operator==(const Slot& other) const {

            // Get the string from sf::Text
    sf::String sfmlString = this->slotName.getString(); // Get sf::String
    std::string standardString = sfmlString.toAnsiString(); // Convert to std::string

        sf::String sfmlString2 = other.slotName.getString(); // Get sf::String
    std::string standardString2 = sfmlString2.toAnsiString(); // Convert to std::string



        return (this->ownerName == other.ownerName) &&
               (standardString == standardString2);
               // Include any other attributes that should be compared
    }










