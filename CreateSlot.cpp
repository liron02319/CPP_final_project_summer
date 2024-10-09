#include "Game.hpp"
#include <SFML/Graphics.hpp> // Include necessary SFML headers
#include <vector>
#include <algorithm> // For std::min
#include "Slot.hpp"


// function that creates the board based on number of slots pushed into slotList
void Game::createslot(std::vector<Slot> &slots, sf::Texture &slot_texture, sf::Vector2u windowSize, sf::Font &font)
{
    //Method Name: push_back- Purpose: Adds an element to the end of a std::vector.
    slots.clear();
    slots.push_back(Slot(0, "GO", CornerColor, 0, 0, 0, 0, 0));
    slots.push_back(Slot(1, "Mediterranean Avenue", sf::Color(0x590C38FF), 100, 6, 30, 50, 90));
    slots.push_back(Slot(2, "Community Chest", CommunityChestColor, 0, 0, 0, 0, 0));
    slots.push_back(Slot(3, "Baltic Avenue", sf::Color(0x590C38FF), 100, 6, 30, 50, 90));
    slots.push_back(Slot(4, "Income Tax", TaxColor, 100, 100, 0, 0, 0));
    slots.push_back(Slot(5, "Reading Railroad", trainColor, 200, 25, 50, 0, 0));
    slots.push_back(Slot(6, "Oriental Avenue", sf::Color(0x87A5D7FF), 150, 8, 40, 50, 100));
    slots.push_back(Slot(7, "Chance", ChanceColor, 0, 0, 0, 0, 0));
    slots.push_back(Slot(8, "Vermont Avenue", sf::Color(0x87A5D7FF), 150, 8, 40, 50, 100));
    slots.push_back(Slot(9, "Connecticut Avenue", sf::Color(0x87A5D7FF), 160, 9, 45, 50, 120));
    slots.push_back(Slot(10, "Jail", CornerColor, 0, 0, 0, 0, 0));
    slots.push_back(Slot(11, "St. Charles Place", sf::Color(0xF8377AFF), 170, 10, 50, 60, 130));
    slots.push_back(Slot(12, "Electric Company", CompanyColor, 150, 0, 0, 0, 0));
    slots.push_back(Slot(13, "States Avenue", sf::Color(0xF8377AFF), 170, 10, 50, 60, 130));
    slots.push_back(Slot(14, "Virginia Avenue", sf::Color(0xF8377AFF), 180, 11, 55, 60, 140));
    slots.push_back(Slot(15, "Pennsylvania Railroad", trainColor, 200, 25, 50, 0, 0));
    slots.push_back(Slot(16, "St. James Place", sf::Color(0xF67F23FF), 190, 12, 60, 70, 150));
    slots.push_back(Slot(17, "Community Chest", CommunityChestColor, 0, 0, 0, 0, 0));
    slots.push_back(Slot(18, "Tennessee Avenue", sf::Color(0xF67F23FF), 190, 12, 60, 70, 150));
    slots.push_back(Slot(19, "New York Avenue", sf::Color(0xF67F23FF), 200, 14, 70, 70, 160));
    slots.push_back(Slot(20, "Free Parking", CornerColor, 0, 0, 0, 0, 0));
    slots.push_back(Slot(21, "Kentucky Avenue", sf::Color(0xEF3B24FF), 220, 18, 90, 80, 170));
    slots.push_back(Slot(22, "Chance", ChanceColor, 0, 0, 0, 0, 0));
    slots.push_back(Slot(23, "Indiana Avenue", sf::Color(0xEF3B24FF), 220, 18, 90, 80, 170));
    slots.push_back(Slot(24, "Illinois Avenue", sf::Color(0xEF3B24FF), 240, 20, 100, 80, 180));
    slots.push_back(Slot(25, "B&O Railroad", trainColor, 200, 25, 50, 0, 0));
    slots.push_back(Slot(26, "Atlantic Avenue", sf::Color(0xFEE703FF), 260, 22, 110, 90, 190));
    slots.push_back(Slot(27, "Ventnor Avenue", sf::Color(0xFEE703FF), 260, 22, 110, 90, 190));
    slots.push_back(Slot(28, "Water Works", CompanyColor, 150, 0, 0, 0, 0));
    slots.push_back(Slot(29, "Marvin Gardens", sf::Color(0xFEE703FF), 280, 24, 120, 90, 200));
    slots.push_back(Slot(30, "Go to Jail", CornerColor, 0, 0, 0, 0, 0));
    slots.push_back(Slot(31, "Pacific Avenue", sf::Color(0x12A65CFF), 300, 26, 130, 100, 210));
    slots.push_back(Slot(32, "North Carolina Avenue", sf::Color(0x12A65CFF), 300, 26, 130, 100, 210));
    slots.push_back(Slot(33, "Community Chest", CommunityChestColor, 0, 0, 0, 0, 0));
    slots.push_back(Slot(34, "Pennsylvania Avenue", sf::Color(0x12A65CFF), 320, 28, 150, 100, 220));
    slots.push_back(Slot(35, "Short Line Railroad", trainColor, 200, 25, 50, 0, 0));
    slots.push_back(Slot(36, "Chance", ChanceColor, 0, 0, 0, 0, 0));
    slots.push_back(Slot(37, "Park Place", sf::Color(0x284EA1FF), 350, 35, 175, 100, 500));
    slots.push_back(Slot(38, "Luxury Tax", TaxColor, 100, 100, 0, 0, 0));
    slots.push_back(Slot(39, "Boardwalk", sf::Color(0x284EA1FF), 400, 50, 200, 100, 600));

    boardsize = slots.size();

    int slotsPerSide = (boardsize + 3) / 4; // Calculate number of slots per side (4 sides)

    // Layout the slots on the board
    //size of the board
    float xPos, yPos;
    const float slotWidth = windowSize.y / (slotsPerSide + 1)-10 ;  // Width of each slot (no gaps) change offset by minusing values to reduce size
    const float slotHeight = windowSize.y / (slotsPerSide + 1)-10; // Height of each slot (no gaps) change offset by minusing values to reduce size

    // Top row
    for (int i = 0; i < std::min(slotsPerSide, boardsize); i++)
    {
        xPos = (((windowSize.x) - (slotWidth * slotsPerSide)) / 2) + (i * slotWidth); // Centering the top row
        yPos = 0;                                                                     // Fixed Y position for top row
        slots[i].setSprite(xPos-150, yPos, font, slotWidth, slotHeight);                  // Set sprite position
    }

    xPos += slotWidth;
    boardleftmost = xPos + slotWidth -120;
    boardrightcolend = (((windowSize.x) - (slotWidth * slotsPerSide)) / 2) + slotWidth;
    boardTopRowBottom = yPos + slotHeight;
    // Right column
    for (int i = slotsPerSide; i < std::min(2 * slotsPerSide, boardsize); i++)
    {
        xPos = xPos;                                                                                        // Fixed X position for right column
        yPos = /*((windowSize.y - (slotHeight * slotsPerSide)) / 2) + */ ((i - slotsPerSide) * slotHeight); // Y position changes
        slots[i].setSprite(xPos-150, yPos, font, slotWidth, slotHeight);
    }
    boardBottomRowTop = yPos;

    yPos += slotHeight;
    // Bottom row
    for (int i = 2 * slotsPerSide; i < std::min(3 * slotsPerSide, boardsize); i++)
    {
        xPos = (((windowSize.x) - (slotWidth * slotsPerSide)) / 2) + (slotsPerSide * slotWidth) - ((i - 2 * slotsPerSide) * slotWidth); // Centering the bottom row
        yPos = yPos;                                                                                                                    //(windowSize.y / 2) + (slotHeight);                                                            // Fixed Y position for bottom row
        slots[i].setSprite(xPos-150, yPos, font, slotWidth, slotHeight);
    }

    xPos -= slotWidth;
    // Left column
    for (int i = 3 * slotsPerSide; i < std::min(4 * slotsPerSide, boardsize); i++)
    {
        xPos = xPos;                                                                // Fixed X position for left column
        yPos = (slotsPerSide * slotHeight) - ((i - 3 * slotsPerSide) * slotHeight); // Y position changes
        slots[i].setSprite(xPos-150, yPos, font, slotWidth, slotHeight);
    }
}

// handels the processing of each slot players lands on
void Game::handleLandingOnSlot(Player &player, std::vector<Player> &players, Slot &slot, sf::RenderWindow &window, sf::Text &message, int d1, int d2, int &numplayers)
{
    // check if slot is owned by any player
    if (slot.getIsOwned())
    {
        int rent = 0;
        bool flag = false;
        // check if slot is railroad
        if (slot.getColorGroup() == trainColor)
        {
            Player *railroadOwner;
            for (auto &p : players)
            {
                if (p.getName() == slot.getOwnerName())
                {
                    if (p.getName() == player.getName())
                    {
                        flag = true;
                    }
                    railroadOwner = &p;
                }
            }
            rent = railroadOwner->railRoadOwned() * 50;
            if (!flag)
            {
                if (player.checkBankruptcy(rent, railroadOwner))
                {
                    message.setString(player.getName() + " went bankrupt!\n");
                }
                else
                {
                    railroadOwner->setMoney(railroadOwner->getMoney() + rent); // Update railroad owner's money
                    player.setMoney(player.getMoney() - rent); // Deduct rent from the player's money
                    
                }
            }
        }
        // check if slot is company
        else if (slot.getColorGroup() == CompanyColor)
        {
            rent = (d1 + d2) * 10;
            Player *companyowner;
            for (auto &p : players)
            {
                if (p.getName() == slot.getOwnerName())
                {
                    if (p.getName() == player.getName())
                    {
                        flag = true;
                    }
                    companyowner = &p;
                }
            }
            if (!flag)
            {
                if (player.checkBankruptcy(rent, companyowner))
                {
                    message.setString(player.getName() + " went bankrupt!\n");
                }
                else
                {

                    companyowner->setMoney(companyowner->getMoney() + rent); // Update railroad owner's money
                    player.setMoney(player.getMoney() - rent); // Deduct rent from the player's money
                }
            }
        }
        // check if slot is street
        else
        {
            rent = slot.calculateRent();
            Player *slotOwner;
            for (auto &p : players)
            {
                if (p.getName() == slot.getOwnerName())
                {
                    if (p.getName() == player.getName())
                    {
                        flag = true;
                    }
                    slotOwner = &p;
                }
            }
            if (!flag)
            {
                if (player.checkBankruptcy(rent, slotOwner))
                {
                    message.setString(player.getName() + " went bankrupt!\n");
                }
                else
                {

                    slotOwner->setMoney(slotOwner->getMoney() + rent); // Update slot owner's money
                    player.setMoney(player.getMoney() - rent); // Deduct rent from the player's money
                    
                }
            }
        }
        if (player.isBankrupt())
            return;
        if (flag)
        {
            std::cout << player.getName() << " owns " << slot.getName() << std::endl;
            message.setString(player.getName() + " owns " + slot.getName());
            return;
        }
        std::cout << player.getName() << " pays $" << rent << " rent to the owner of " << slot.getName() << std::endl;
        message.setString(player.getName() + " pays $" + std::to_string(rent) + " rent to the owner of " + slot.getName());
    }
    else
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
        buyPrompt.setString("Do you want to buy " + slot.getName() + " for $" + std::to_string(slot.getPrice()) + "?");
        buyPrompt.setCharacterSize(24);
        buyPrompt.setFillColor(sf::Color::White);
        buyPrompt.setPosition(50, 450); // Adjust position as needed

        sf::RectangleShape background;
        background.setSize(sf::Vector2f(10 + buyPrompt.getGlobalBounds().width, 10 + buyPrompt.getGlobalBounds().height));
        background.setPosition(45, 445);
        background.setFillColor(sf::Color(70, 120, 60));

        bool decisionMade = false;
        bool wantsToBuy = false; // Keep track of player's decision

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
                window.draw(background);

                // Draw the buy prompt message
                window.draw(buyPrompt);

                // Draw the buttons
                yesButton.draw(window);
                noButton.draw(window);

                window.display();

                // Check for clicks
                if (yesButton.isClicked(mousePos, event))
                {
                    wantsToBuy = true;
                    decisionMade = true;
                }
                else if (noButton.isClicked(mousePos, event))
                {
                    wantsToBuy = false;
                    decisionMade = true;
                }
            }
        }

        if (wantsToBuy)
        {
            if (player.buySlot(slot))
            {
                slot.setIsOwned(true);
                std::cout << player.getName() << " bought " << slot.getName() << " for $" << slot.getPrice() << std::endl;
                message.setString(player.getName() + " bought " + slot.getName()  + " for $" + std::to_string(slot.getPrice()));
                std::cout << &slot << std::endl;
            }
            else
            {
                std::cout << player.getName() << " cannot buy " << slot.getName()  << std::endl;
                message.setString(player.getName() + " cannot buy " + slot.getName() );
            }
        }
        else
        {
            std::cout << player.getName() << " decided not to buy " << slot.getName()  << std::endl;
            message.setString(player.getName() + " decided not to buy " + slot.getName() );
        }
    }
}