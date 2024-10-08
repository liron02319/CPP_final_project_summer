#ifndef SLOT_HPP
#define SLOT_HPP
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


class Slot
{

private:

    sf::Sprite slot;  // Sprite for the slot on the game board -in the context of SFML (Simple and Fast Multimedia Library), a sprite is an object used to display a texture (an image) on the screen. 
    int slotNum; //This integer represents the position number(index) of the slot on the board
    sf::RectangleShape slotShape;   // Shape for the slot - used to visually represent the slot/property on the board.
    sf::RectangleShape slotHouse;   // Shape representing houses or hotels on the property- another rectangle shape that specifically represents houses or hotels built on the property.
    sf::Text slotName;              // Text for the slot name-display text name of the property on the game board
    sf::Text slotPrice;             // Text for the slot price-display text price of the property on the game board

    // Street properties
    std::string name;
    sf::Color colorGroup;
    int price;
    int rent;
    int housePrice;
    int rentWithHouse;
    int rentWithHotel;
    int houses;
    int hotels;
    bool isRail; //it means that this slot is a railroad,
    bool isCompany; //it means that this slot is a company
    bool isOwned;
    std::string ownerName;

public:

    // Constructor
    Slot(int Index, const std::string &n, const sf::Color color, int p, int r, int hPrice, int rWithHouse, int rWithHotel);
    


    // Getter and Setter for slot street price
    int getPrice() const ;
    void setPrice(int newPrice) ;



    // Getter and Setter for if the slot street isOwned
    bool getIsOwned() const ;
    void setIsOwned(bool owned) ;



    // Getter and Setter for  housePrice
    int getHousePrice() const ;
    void setHousePrice(int newHousePrice);



    // Getter and Setter for ownerName
    std::string getOwnerName() const ;
    void setOwnerName(const std::string &newOwner) ;



    // Getter and Setter for how much houses in the slot
    int getHouses() const;
    void setHouses(int newHouses) ;



    // Setter for houses (to increment houses)
    void addHouse() ;



    // Getter and Setter for how much hotels in the slot
    int getHotels() const ;
    void setHotels(int newHotels);



    // Getter and Setter for rent
    int getRent() const ;
    void setRent(int newRent) ;



    // Getter and Setter for rentWithHouse
    int getRentWithHouse() const ;
    void setRentWithHouse(int newRentWithHouse) ;



    // Getter and Setter for rentWithHotel
    int getRentWithHotel() const ;
    void setRentWithHotel(int newRentWithHotel);



    // Getter and Setter for isRail- check if slot is a railroad(train)
    bool getIsRail() const ;
    void setIsRail(bool rail) ;


    // Getter and Setter for check if slot is a isCompany
    bool getIsCompany() const ;
    void setIsCompany(bool company);



    // Getter and Setter for name of slot street
    std::string getName() const;
    void setName(const std::string &newName) ;



    // Getter and Setter for colorGroup of the slot
    sf::Color getColorGroup() const ;
    void setColorGroup(const sf::Color &newColorGroup) ;



    // Getter and Setter for slotNum 
    int getSlotNum() const ;
    void setSlotNum(int newSlotNum) ;


     // Getter for slotShape
    const sf::RectangleShape& getSlotShape() const ;



    // Setter for slotShape size
    void setSlotShapeSize(const sf::Vector2f& size) ;



    // Sets the position of the slot
    void setPos(float xpos, float ypos);



    // Sets the size of the slot and associated elements
    //this sets the size of the rectangle (slotShape) to the width and height provided as arguments.
    //this function is used to set the size of the slotShape, which represents the visual area of the slot on the game board.
    void setSizeAll(float width, float height);
   



    // Configures the slot sprite and text
    /*
    this function configures both the appearance and the position of the slot, 
    its associated text (name and price), and the houses or hotels. 
    It also sets up whether the slot represents a railroad or a company based on its color.
    */
    void setSprite(float xpos, float ypos, sf::Font &font, int width, int height);
   



    // Draws the slot and its elements to the SFML window
    //This function is responsible for drawing the slot and its associated elements (such as houses or hotels) to the game window.
    void draw(sf::RenderWindow &window);




    // Calculates the rent based on the number of houses or hotels
    int calculateRent() const;


    bool operator==(const Slot& other) const;


};




#endif // SLOT_HPP