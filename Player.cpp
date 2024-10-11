#include "Player.hpp"
#include <SFML/Graphics.hpp>
#include "Slot.hpp"
#include "Button.hpp"





     // Constructor
        //nisim, 0(in list of players) ,the full board slots , position in the board slots
    Player::Player(std::string playerName, int i, std::vector<Slot> &sl, Slot &csl) 
        : name(playerName),
        index(i),  //identifies the player within an array or list of players.
          position(csl.getSlotNum()), //get the current position on the game boar
          money(1500), 
         SlotList(sl), //get the full board slots
          currSlot(&csl), //point to the address where player stand
          inJail(false),
           isJailable(true), 
          turnsInJail(0),
           houses(0), 
           hotels(0), 
          isbankrupt(false) //if player with no money is bankrupt
          {} 


//This method, buySlot, allows a player to attempt to purchase a slot (or property) in the game.
    bool Player::buySlot(Slot &slot) //Slot &slot: This is a reference to the Slot (property) the player is attempting to buy.
    {
        if (!slot.getIsOwned()&& money >= slot.getPrice())
        {
            money -= slot.getPrice(); 
            slot.setIsOwned(true);
            ownedSlots.push_back(&slot);
            slot.setOwnerName(name);
            

            return true;
        }
        return false;
    }


/*

//the buildHouse function allows a player to add a house (or upgrade to a hotel) on a property (slot) they own, 
- You can purchase up to 4 houses per street and then also a hotel
- To buy another house, the player must build the same number of houses in the other color groups
 (that is, let's say I have 2 streets belonging to the same color group and in one I built a house and in the other I didn't.
 It is not possible to build another house on the first street, until a house is built on the second street).
*/


   bool Player::buildHouse(Slot &slot)
{
    // Check if the player owns the slot, can build a house on it, and has enough money to buy a house.
    if (slot.getIsOwned() && canBuildHouse(slot) && money >= slot.getHousePrice())
    {
                  //  std::cout << "enter to buildHouse:" << std::endl;

        // Case 1: Build up to 4 houses
        if (slot.getHouses() < 4 && slot.getHotels() == 0)
        {
                           //     std::cout << "insideeeeee:" << std::endl;

            money -= slot.getHousePrice();  // Deduct the cost of the house.
            slot.addHouse();  // Increment the house count.
            std::cout << "House built, new house count: " << slot.getHouses() << std::endl;
            return true;  // Successfully built a house.
        }

        // Case 2: Build a hotel when there are exactly 4 houses
        else if (slot.getHouses() == 4 && slot.getHotels() == 0)
        {
            // Check if the player has enough money for the hotel
            int hotelPrice = 4 * slot.getHousePrice() + 100; 
            if (money >= hotelPrice)
            {
                money -= hotelPrice; // Deduct the hotel price.
                slot.setHotels(1);   // Set the number of hotels to 1.
                slot.setHouses(0);   // Reset the number of houses to 0, as it is now a hotel.
                
                std::cout << "Hotel built, house count reset to 0, hotel count: " << slot.getHotels() << std::endl;
                return true;  // Successfully built a hotel.
            }
        }
    }

    // If the conditions for building a house or hotel are not met, return false.
    return false;
}

//
//here
//


    // Check if the player can build a house
    /*
    The function canBuildHouse determines if a player can build a house on a specific property (or "slot") based on a few conditions. 
    It checks the following:
    -The player must own all slots in the same color group.
    -Houses must be built evenly across all properties in the color group. 
    You cannot have more houses on one property in the group than on others
    */
   bool Player::canBuildHouse(Slot &slot) {
    // Step 1: Check if the slot is owned by the player
    if (!slot.getIsOwned() || slot.getOwnerName() != name) {
        return false;  // Player does not own this slot
    }


         //   std::cout << "ENTER canBuildHouse" << std::endl;

    // Step 2: Collect all slots that belong to the same color group
    std::vector<Slot*> colorGroupSlots;
    for (Slot* ownedSlot : ownedSlots) {
        if (ownedSlot->getColorGroup() == slot.getColorGroup()) {
            colorGroupSlots.push_back(ownedSlot);
        }
    }

    // Step 3: Ensure the player owns all slots in this color group
    size_t totalSlotsInColorGroup = 0;
    for (const Slot &s : SlotList) {
        if (s.getColorGroup() == slot.getColorGroup()) {
            totalSlotsInColorGroup++;

        }
    }
        //    std::cout << "totalSlotsInColorGroup" << totalSlotsInColorGroup <<std::endl;
        //    std::cout << "colorGroupSlots.size(" << colorGroupSlots.size() <<std::endl;

    // If the player doesn't own all slots in the color group, they cannot build
    if (colorGroupSlots.size() != totalSlotsInColorGroup) {
        return false;
    }

    // Step 4: Check that the number of houses is evenly distributed
    // Find the minimum number of houses among all slots in the same color group
    int minHouses = colorGroupSlots[0]->getHouses();
  //   std::cout << "minHousesbeforeloop" << minHouses <<std::endl;

    for (Slot* colorSlot : colorGroupSlots) {
        if (colorSlot->getHouses() < minHouses) {
            minHouses = colorSlot->getHouses();
        }
    }


// std::cout << "tslot.getHouses()" << slot.getHouses() <<std::endl;
         //   std::cout << "minHouses(" << minHouses <<std::endl;

    // If the current slot has more houses than the minimum, no house can be built
    if (slot.getHouses() > minHouses) {
        return false;
    }

    // All conditions met: player can build a house on this slot
    return true;
}

/*
The railRoadOwned() function is designed to count
 and return the number of railroad slots that a player owns
*/
    int Player::railRoadOwned() const
    {
        int i = 0;
        for (size_t j = 0; j < ownedSlots.size(); j++)
        {
            //  std::cout << "ownedSlots[j]:" <<  ownedSlots[j] <<  std::endl;

            if (ownedSlots[j]->getIsRail())
            {
                i++;
            }

        }
        return i;
    }

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
    void Player::attemptToGetOut(bool rolledDouble, sf::RenderWindow &window)
    {

    if(turnsInJail<3)
    {
            
        bool canUseMoney = true; //This flag is initially set to true, indicating that the player can use money to get out unless specified otherwise later in the method.

        if (rolledDouble) //if player rolled double result in dice he gets out of jail
        {
            inJail = false;  // Player rolled double and gets out
            turnsInJail = 0; // Reset turns in jail
            canUseMoney = false; //as the player does not need to pay to get out.
        }

        else if (!isJailable) //if the player have a card "get out of jail(GOOJ)"
        {
            // Create Yes and No buttons
            Button yesButton(50, 500, 100, 50, "Yes");
            Button noButton(250, 500, 100, 50, "No");


            // Create the message asking if the player wants to use jailcard
            sf::Font font;// Font style of text
            if (!font.loadFromFile("Fonts/bebas/Bebas-Regular.ttf"))
            {
                std::cerr << "Error loading font\n";
            }

            sf::Text buyPrompt; //obj for show text to screen
            buyPrompt.setFont(font);
            buyPrompt.setString("Do you want to use get out of jailcard to get out?");
            buyPrompt.setCharacterSize(24);
            buyPrompt.setFillColor(sf::Color::White);
            buyPrompt.setPosition(50, 450); // Adjust position as needed

            sf::RectangleShape background; //A rectangle shape is created to serve as a background for the text prompt
            background.setSize(sf::Vector2f(10 + buyPrompt.getGlobalBounds().width, 20 + buyPrompt.getGlobalBounds().height)); //The size of the rectangle is set based on the dimensions of the text to ensure it fits nicely.
            background.setPosition(45, 445);
            background.setFillColor(sf::Color(70, 120, 60));

            bool decisionMade = false; //boolean flag tracks whether the player has made a decision regarding using the card (i.e., clicked "Yes" or "No").
            bool wantsToUseJailCard = false; //  This boolean keeps track of whether the player wants to use the "Get Out of Jail" card (true) or not (false).

            while (!decisionMade && window.isOpen()) //checks if the player has made a decision (yes or no).
            { //This loop continues to run as long as decisionMade is false and the application window is open.
                sf::Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                    {
                        window.close();
                    }

                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    // Update and draw buttons
                    yesButton.update(mousePos);
                    noButton.update(mousePos);

                    // window.clear();

                    // Draw the buy prompt message
                    window.draw(buyPrompt);

                    // Draw the buttons
                    yesButton.draw(window);
                    noButton.draw(window);


                    // Check for clicks
                    if (yesButton.isClicked(mousePos, event)) //pressed yes- he want to use card out of jail
                    {
                        wantsToUseJailCard = true;
                        decisionMade = true;
                        window.draw(background);
                        
                    }
                    else if (noButton.isClicked(mousePos, event)) //pressed no -//he dont want to use card out of jail
                    {
                        wantsToUseJailCard = false;
                        decisionMade = true;
                        window.draw(background);
                    }
                    window.display();
                }
            }

            if (wantsToUseJailCard) //he decide to use card out of jail
            {
                isJailable = true; // Use the card
                inJail = false;    // Player is out of jail
                turnsInJail = 0;   // Reset turns in jail
                canUseMoney = false;
            }
            else
            {
                canUseMoney = true;
            }
        }//END if the player have a card "get out of jail(GOOJ)"




        if (canUseMoney) //he need to pay money to out of jail
        {
            // Create Yes and No buttons
            Button yesButton(50, 500, 100, 50, "Yes");
            Button noButton(250, 500, 100, 50, "No");

            // Create the message asking if the player wants to buy the slot
            sf::Font font;
            if (!font.loadFromFile("Fonts/bebas/Bebas-Regular.ttf"))
            {
                std::cerr << "Error loading font\n";
            }

            sf::Text buyPrompt;
            buyPrompt.setFont(font);
            buyPrompt.setString("Do you want to use $50 to get out?");
            buyPrompt.setCharacterSize(24);
            buyPrompt.setFillColor(sf::Color::White);
            buyPrompt.setPosition(50, 450); // Adjust position as needed

            bool decisionMade = false;
            bool wantsToPay = false; // Keep track of player's decision

            while (!decisionMade && window.isOpen())
            {
                sf::Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                    {
                        window.close();
                    }

                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    // Update and draw buttons
                    yesButton.update(mousePos);
                    noButton.update(mousePos);

                    // window.clear();

                    // Draw the buy prompt message
                    window.draw(buyPrompt);

                    // Draw the buttons
                    yesButton.draw(window);
                    noButton.draw(window);

                    window.display();

                    // Check for clicks
                    if (yesButton.isClicked(mousePos, event))
                    {
                        wantsToPay = true;
                        decisionMade = true;
                    }
                    else if (noButton.isClicked(mousePos, event))
                    {
                        wantsToPay = false;
                        decisionMade = true;
                    }
                }
            }

            if (wantsToPay) //decide to pay to get out of jail
            {
                payFine();
            }
            else
            {
                turnsInJail++; // Increment turns in jail
            }
        }
    }
    else{

        if(checkBankruptcy(50)==false){
            payFine();
        }
        else{
        checkBankruptcy(50);
            //implement here checkBankruptcy
        }
    }
    }

    // Method to pay fine to out of jail 50$
    void Player::payFine()
    {
        if (money >= 50)
        {
            money -= 50;
            inJail = false;  // Player is out of jail
            turnsInJail = 0; // Reset turns in jail
        }
    }


    /*
    The checkBankruptcy function determines whether a player is bankrupt based on the amount they owe 
    and manages the consequences of bankruptcy, 
    such as transferring assets(slots+money) to a creditor or the bank.
    */
    bool Player::checkBankruptcy(int amountOwed, Player* creditor )
    {
        if (money < amountOwed) //if you got not enough money 
        {
            // Player is bankrupt
            if (creditor)
            {
                // Transfer all assets to the creditor
                creditor->money += money;          
                // insert(where to put,from where, until where)                                                            // Transfer money
                creditor->ownedSlots.insert(creditor->ownedSlots.end(), ownedSlots.begin(), ownedSlots.end()); // Transfer properties
                money = 0;
                ownedSlots.clear(); // Clear the bankrupt player's properties
            }
            else
            {
                // Debt to the bank, erase ownership of streets
                for (size_t i = 0; i < ownedSlots.size(); i++)
                {
                    ownedSlots[i]->setIsOwned(false);
                    ownedSlots[i]->setHouses(0);
                    ownedSlots[i]->setHotels(0);
                }
                money = 0;
                ownedSlots.clear(); // Lose all properties
            }
            setPos(SlotList[0].getSlotShape().getPosition().x, 0); //The player’s position is reset to the starting position on the game board
            isbankrupt = true;
            return true; // Indicate bankruptcy
        }
        isbankrupt = false;
        return false; // Not bankrupt
    }

    /*
    
    This function move_slot- moves the player across a board of a specific size 
     and handles special conditions like passing "GO" and collecting money
    
    param i - The number of slots the player is moving (based on dice roll or another event).
    param boardsize - The total number of slots on the board, typically 40 in games like Monopoly (i.e., positions 0 to 39).
    */
    void Player::move_slot(int i, int boardsize) 
    {

        int previousPosition = position; // Store previous position
        position = (position + i) % boardsize; // Update position

        // Check if the player passed "Go"
        if (position < previousPosition )
        {
            std::cout << "go passed! you got 200$\n";
            money += 200; // Collect $200
        }

        currSlot = &(SlotList[position]); // Update currSlot to the new position
        setPos(currSlot->getSlotShape().getPosition().x, currSlot->getSlotShape().getPosition().y); // Update graphical position

        // Debugging output
        std::cout << this->getName() << " Moving from " << previousPosition << " to " << position << std::endl;
        std::cout << "Current Slot Number: " << currSlot->getSlotNum() << std::endl;
        std::cout << "Total Slots: " << boardsize << std::endl;
        /*
        position = position + i; //The player's current position is updated by adding i (the number of slots to move). position is the player's current slot number, and this line moves the player forward by i slots.
        position = position % boardsize; // As position is in range 0 - 39

        // If player passes go collects 200
        if (currSlot->getSlotNum() > position)
        {
            std::cout << "go passed\n";
            money += 200;
        }
        currSlot = &(SlotList[position]);  //The player's current slot is updated to the new position. SlotList is an array or vector of slots, and position is used to index into this list. currSlot is a pointer to the new slot where the player has landed.
        setPos(currSlot->getSlotShape().getPosition().x, currSlot->getSlotShape().getPosition().y); // set position to new slot - The player's graphical position is updated on the game board. 
        */
    }


    /*
    This function setTexture- configures a player's token (sprite) in the game 
    by setting its texture, defining which part of the texture to display,
    adjusting its size, and optionally setting a color or border for the sprite.
    *This function sets up the texture and appearance for a player's token on the board. 
    It extracts the correct token from a sprite sheet, 
    resizes it to fit the board, and applies an optional tint color. 
    */
    void Player::setTexture(const sf::Texture &texture, float xsize)
    {
        // each token is 666x400 in size
        const int tokenWidth = 600;
        const int tokenHeight = 425;

        // Calculate the position of the token in the sprite sheet
        int tokenX = ((index % 3) * tokenWidth);  // Assuming 3 tokens per row
        int tokenY = ((index / 3) * tokenHeight); // Assuming sprite sheet has multiple rows

        // Set the sprite to the portion of the texture for the specific token
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(tokenX + 66, tokenY + 55, tokenWidth, tokenHeight));                           // 66 and 55 arre gaps between tokens in sprite sheet
        sprite.setScale(xsize / (1.5 * sprite.getGlobalBounds().width), xsize / (1.5 * sprite.getGlobalBounds().width)); // The size of sprite is .75 times that of a single slot
        sprite.setColor(sf::Color(207, 177, 68));

        // If you want to add border to the player token uncomment the code below and also the code in setPos and draw
        // Update the border size to match the die sprite's size, with a slight margin
        // sf::FloatRect playerBounds = sprite.getGlobalBounds();
        // player_border.setSize(sf::Vector2f(playerBounds.width + 10, playerBounds.height + 10)); // Add 10 pixels for the border
        // player_border.setPosition(sprite.getPosition().x - 5, sprite.getPosition().y - 5);      // Center the border around the die
        // player_border.setFillColor(sf::Color(0, 0, 20 * index));
    }

    // Sets a bright colour for current player playing
    void Player::setActive()
    {
        sprite.setColor(sf::Color(243, 254, 184));
    }

    // Sets a darker colour for player not currently playing
    void Player::setInActive()
    {
        sprite.setColor(sf::Color(207, 177, 68));
    }


    /*
    The setPos(float x, float y) function sets the position of a player's token (sprite)
    on the game board, ensuring that multiple tokens can fit within the same slot on the board
    */

    void Player::setPos(float x, float y)
    {
        // each token will be in a 2x4 grid so they all can fit in every slot of the board
        sprite.setPosition(x + ((index % 2) * sprite.getGlobalBounds().width) / 2, y + ((index / 2) * sprite.getGlobalBounds().height) / 4);
        // player_border.setPosition(x + ((index % 2) * sprite.getGlobalBounds().width)/2, y  + ((index / 2) * sprite.getGlobalBounds().height)/4);
    }


    /*
    function is responsible for drawing the player's token (sprite) on the game board,
     using the provided window (win) object to render it.

    */
    void Player::draw(sf::RenderWindow &win)
    {
        // win.draw(player_border);
        win.draw(sprite);
    }

    // Getters and setters
    std::string Player::getName() const { return name; }
    int Player::getIndex() const { return index; }
    int Player::getPosition() const { return position; }
    int Player::getMoney() const { return money; }
    bool Player::isInJail() const { return inJail; }
    bool Player::isBankrupt() const { return isbankrupt; }
    void Player::setPosition(int newPosition) { position = newPosition; }
    void Player::setMoney(int newMoney) { money = newMoney; }
    void Player::setInJail(bool jailed) { inJail = jailed; }
    void Player::setJailable(bool jailable) { isJailable = jailable; }
    void Player::addHouse() { houses++; }
    void Player::addHotel() { hotels++; }
    int Player::getHouses() const { return houses; }
    int Player::getHotels() const { return hotels; }
    void Player::setSprite(const sf::Sprite &newSprite) { sprite = newSprite; }
    sf::Sprite& Player::getSprite()  { return sprite; }
    sf::RectangleShape Player::getPlayerBorder() const { return player_border; }
    void Player::setPlayerBorder(const sf::RectangleShape &border) { player_border = border; }
    
    // Getter function for turnsInJail
int Player::getTurnsInJail() const
{
    return turnsInJail;
}

// Setter function for turnsInJail
void Player::setTurnsInJail(int turns)
{
    if (turns >= 0)  // Ensuring that the value is non-negative
    {
        turnsInJail = turns;
    }
}

// Function to increment turnsInJail by 1
void Player::incrementTurnsInJail()
{
    turnsInJail++;
}

// Getter for isJailable
    bool Player::getIsJailable() const { return isJailable; }

       // Getter for ownedSlots
    const std::vector<Slot*>& Player::getOwnedSlots() const { return ownedSlots; }

    // Getter for currSlot
    Slot* Player::getCurrSlot() const { return currSlot; }

