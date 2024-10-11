#ifndef PLAYER_HPP
#define PLAYER_HPP


#include <SFML/Graphics.hpp>
#include "Slot.hpp"
#include "Button.hpp"

class Player
{

private:

    std::string name; // name of the player.
    int index; // This variable serves as an index for the player, often used to identify the player's position in an array or list of players
    int position; //This variable indicates the player's current position on the game board slot, usually represented as an integer corresponding to the slot number or index on the board.
    int money; //the amount of money the player currently has
    std::vector<Slot>& SlotList; //vector containing Slot objects, which represents the list of all available slots (properties) in the game. The use of a reference avoids unnecessary copying of the vector.
    Slot *currSlot; //this is a pointer to the Slot object that the player currently stand on him. It allows for dynamic access to the slot's properties.
    bool inJail; //whether the player is currently in jail. I
    bool isJailable; //this boolean variable specifies whether the player is can to be sent to jail. It could change based on game events (like getting a “Get Out of Jail” card).
    int turnsInJail = 0; // This variable tracks the number of turns the player has been in jail.
    int houses; //number of houses owned by the player
    int hotels; //number of hotels owned by the player
    sf::Sprite sprite; //this variable represents the graphical representation of the player on the game board, using SFML (Simple and Fast Multimedia Library) for rendering graphics.
    sf::RectangleShape player_border; //This variable represents a rectangular shape around the player’s sprite, likely used for visual boundaries or highlighting the player’s presence on the board.
    std::vector<Slot *> ownedSlots; // This vector keeps track of pointers to the Slot objects, owned by the player. Using pointers allows for efficient memory usage and manipulation of slot ownership without unnecessary copies.
    bool isbankrupt; //whether the player is bankrupt.


public:

     // Constructor
        //nisim, 0(in list of players) ,the full board slots , position in the board slots
    Player(std::string playerName, int i, std::vector<Slot> &sl, Slot &csl) ;


//This method, buySlot, allows a player to attempt to purchase a slot (or property) in the game.
    bool buySlot(Slot &slot); //Slot &slot: This is a reference to the Slot (property) the player is attempting to buy.
   


/*

//the buildHouse function allows a player to add a house (or upgrade to a hotel) on a property (slot) they own, 
- You can purchase up to 4 houses per street and then also a hotel
- To buy another house, the player must build the same number of houses in the other color groups
 (that is, let's say I have 2 streets belonging to the same color group and in one I built a house and in the other I didn't.
 It is not possible to build another house on the first street, until a house is built on the second street).
*/


    bool buildHouse(Slot &slot);
    

    // Check if the player can build a house
    /*
    The function canBuildHouse determines if a player can build a house on a specific property (or "slot") based on a few conditions. 
    It checks the following:
    -The player must own all slots in the same color group.
    -Houses must be built evenly across all properties in the color group. 
    You cannot have more houses on one property in the group than on others
    */
    bool canBuildHouse(Slot &slot);
    

/*
The railRoadOwned() function is designed to count
 and return the number of railroad slots that a player owns
*/
    int railRoadOwned() const ;
    

    // Method to attempt getting out of jail
    /*
    
    The attemptToGetOut method allows a player to try to get out of jail in a game 
    
    The player is in prison for 3 turns during which he can try to get out 
    of prison in the following ways:

    1)Use a get out of jail card (which you get from the surprise box).
    2)Pay a fine of NIS 50.
    3)roll the dice and get a "double".

    If 3 turns have passed and the player has not been able to get out of jail, he must pay a tax of NIS 50 and then he gets out of jail.

    If he has no way to pay it, he loses the game and is bankrupt
    */
    void attemptToGetOut(bool rolledDouble, sf::RenderWindow &window);
    

    // Method to pay fine to out of jail 50$
    void payFine();
    


    /*
    The checkBankruptcy function determines whether a player is bankrupt based on the amount they owe 
    and manages the consequences of bankruptcy, 
    such as transferring assets(slots+money) to a creditor or the bank.
    */
    bool checkBankruptcy(int amountOwed, Player* creditor = nullptr);
    

    /*
    
    This function move_slot- moves the player across a board of a specific size 
     and handles special conditions like passing "GO" and collecting money
    
    param i - The number of slots the player is moving (based on dice roll or another event).
    param boardsize - The total number of slots on the board, typically 40 in games like Monopoly (i.e., positions 0 to 39).
    */
    void move_slot(int i, int boardsize) ;
    


    /*
    This function setTexture- configures a player's token (sprite) in the game 
    by setting its texture, defining which part of the texture to display,
    adjusting its size, and optionally setting a color or border for the sprite.
    *This function sets up the texture and appearance for a player's token on the board. 
    It extracts the correct token from a sprite sheet, 
    resizes it to fit the board, and applies an optional tint color. 
    */
    void setTexture(const sf::Texture &texture, float xsize);
   

    // Sets a bright colour for current player playing
    void setActive();
    

    // Sets a darker colour for player not currently playing
    void setInActive();
    


    /*
    The setPos(float x, float y) function sets the position of a player's token (sprite)
    on the game board, ensuring that multiple tokens can fit within the same slot on the board
    */

    void setPos(float x, float y);
    


    /*
    function is responsible for drawing the player's token (sprite) on the game board,
     using the provided window (win) object to render it.

    */
    void draw(sf::RenderWindow &win);
    


    // Getters and setters
    std::string getName() const ;
    int getIndex() const ;
    int getPosition() const ;
    int getMoney() const ;
    bool isInJail() const ;
    bool isBankrupt() const ;
    void setPosition(int newPosition); 
    void setMoney(int newMoney);
    void setInJail(bool jailed) ;
    void setJailable(bool jailable); 
    void addHouse() ;
    void addHotel() ;
    int getHouses() const; 
    int getHotels() const ;
    void setSprite(const sf::Sprite &newSprite) ;
    sf::Sprite& getSprite() ; 
    sf::RectangleShape getPlayerBorder() const ;
    void setPlayerBorder(const sf::RectangleShape &border); 
    
    // Getter function for turnsInJail
int getTurnsInJail() const;



// Setter function for turnsInJail
void setTurnsInJail(int turns);



// Function to increment turnsInJail by 1
void incrementTurnsInJail();



// Getter for isJailable
    bool getIsJailable() const ;

       // Getter for ownedSlots
    const std::vector<Slot*>& getOwnedSlots() const ;

    // Getter for currSlot
    Slot* getCurrSlot() const; 


bool hasCompleteSet(Slot &slot) ;
int getMinHouseCountInSet(Slot &slot);



};

#endif // PLAYER_HPP