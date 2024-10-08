#ifndef Game_h
#define Game_h

#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include "Player.hpp"
#include "Slot.hpp"
#include "Dice.hpp"
#include "Button.hpp"
#include "Menu.hpp"
#include "Openning.hpp"


using namespace std;

class Game
{
public:
//These values help define the playable area of the board, including where rows and columns start and end, and help position various game elements like player tokens or property markers within the visual representation of the board.
    int boardsize; //represents the size of the board
    int boardleftmost; //the X-coordinate (or pixel position) of the leftmost edge of the game board on the screen. It's the left boundary, which helps position elements relative to this edge.
    int boardrightcolend; //This is likely the X-coordinate of the rightmost column's end on the board. It helps determine where the right edge of the board lies on the screen.
    int boardTopRowBottom; //the Y-coordinate of the bottom edge of the top row. It defines the vertical boundary of the top row of the board.
    int boardBottomRowTop; //the Y-coordinate of the top edge of the bottom row. It defines the vertical boundary of the bottom row of the board.

    //These sf::Color variables store the colors associated with different types of properties or slots on the board. Each color is applied to differentiate various elements, making the board visually clearer for players.
    sf::Color trainColor; //This stores the color of train (railroad) properties.
    sf::Color CompanyColor;//this stores the color of company (utility) properties, like waterworks or electric companies. This helps visually separate them from other property types.
    sf::Color ChanceColor; //this stores the color of the Chance card slots. In Monopoly, landing on a Chance slot prompts the player to draw a card with random events, so its distinctive color alerts players.
    sf::Color CommunityChestColor; //This stores the color of the Community Chest slots. Similar to Chance slots, landing on a Community Chest slot means drawing a card with various effects.
    sf::Color TaxColor; //this stores the color of Tax slots. Tax slots usually charge the player a fee or penalty
    sf::Color CornerColor; //This stores the color of the corner slots, which could include special places like "Go", "Jail", or "Free Parking"

    Game() 
    : trainColor(sf::Color(0xCAE8E0FF)),
      CompanyColor(sf::Color::Cyan),
      ChanceColor(sf::Color(0xD6292BFF)),
      CommunityChestColor(sf::Color(0x21418CFF)),
      TaxColor(sf::Color::Yellow),
      CornerColor(sf::Color::White)

    {
     //The call to srand(time(0)); is a function call meant to seed the random number generator, which is not tied to the initialization of any member variable. Therefore, it should stay in the body of the constructor, not in the initializer list.
    srand(time(0)); // still need to seed the random number generator inside the body

    }


    /*

    void run() function in the Game class is responsible for running the main game logic, 
    which includes setting up the game board,
    loading resources (textures, fonts, etc.), creating players, and handling player turns.
    */

    void run()
    {

          // Get the desktop resolution for fullscreen mode
        sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
        sf::RenderWindow window(desktopMode, "Monopoly Card Actions", sf::Style::Default);

         Openning openning;
        openning.displayOpening(window); // Display the opening window


        // loading textures for board, slots and player(tokens)
        sf::Texture Board_Text, player_texure, slot_texture;
        Board_Text.loadFromFile("images/Game_board.jpg");
        player_texure.loadFromFile("images/tokens.png");
        slot_texture.loadFromFile("images/Game_board.jpg");

        // apply texture to board
        sf::Sprite Board_Sprite;
        Board_Sprite.setTexture(Board_Text);

        // Get the desktop resolution for fullscreen mode
       // sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
      //  sf::RenderWindow window(desktopMode, "Monopoly Card Actions", sf::Style::Default);

        // Get the size of the window and the board texture
        sf::Vector2u windowSize = window.getSize();
        sf::Vector2u boardTextureSize = Board_Text.getSize();


       
        /*
        The board's texture is scaled to fit the window.
        The scaling factor is calculated based on the ratio of the window size to the texture size. 
        This ensures that the board maintains its aspect ratio, even when resized
        */
        // Calculate scale factors for both width and height and apply the scale to board
        float scaleX = static_cast<float>(windowSize.x) / boardTextureSize.x;
        float scaleY = static_cast<float>(windowSize.y) / boardTextureSize.y;
        float scaleFactor = min(scaleX, scaleY);
        Board_Sprite.setScale(scaleFactor, scaleFactor);
        sf::FloatRect boardBounds = Board_Sprite.getGlobalBounds(); // Get the size of the scaled board


        //After scaling, the board is centered within the window.
        // Calculate position to center the board in the window
        float xPos = (windowSize.x - boardBounds.width) / 2;
        float yPos = (windowSize.y - boardBounds.height) / 2;

        // Set the sprite position to center it
        Board_Sprite.setPosition(xPos, yPos);



        // Create slots
        sf::Font font;
        font.loadFromFile("Fonts/bebas/Bebas-Regular.ttf");
        std::vector<Slot> slots;
        createslot(slots, slot_texture, windowSize, font);

        // Create players
        std::vector<Player> players;
        int doubleCounter = 3; // max double rolls in a row
        int playersLeft = 0;   // number of players left in game
        Player *winner;        // points to winner

        // Get names and num of players playing and set the names for player
        int numPlayer = 4;
        Menu menu;
        std::vector<std::string> name_list = menu.loadMenu(numPlayer, window);
        if (numPlayer == 0)
            return;

        for (int i = 0; i < numPlayer; i++)
        {
            players.push_back(Player(name_list[i], i, slots, slots[0]));
        }

        // Set each player's sprite with a token from the sprite sheet

        for (std::vector<Player>::size_type  i = 0; i < players.size(); i++)
        {
            players[i].setTexture(player_texure, slots[0].getSlotShape().getGlobalBounds().width); // Set texture with token index i
            players[i].setPos(slots[0].getSlotShape().getPosition().x, slots[0].getSlotShape().getPosition().y);
        }

        int currTurn = 0;

        // Text that shows player info
        sf::Font PlayerInfoFont;
        PlayerInfoFont.loadFromFile("Fonts/bebas/Bebas-Regular.ttf");

        std::vector<sf::Text> PlayerInfoText;
        // One Text object for one player
        for (int i = 0; i < numPlayer; i++)
        {
            PlayerInfoText.push_back(sf::Text());
        }
        // Initialize the Text
        for (std::vector<sf::Text>::size_type  i = 0; i < PlayerInfoText.size(); i++)
        {
            PlayerInfoText[i].setFont(PlayerInfoFont);
            PlayerInfoText[i].setString(players[i].getName() + "\n$" + to_string(players[i].getMoney()));
            PlayerInfoText[i].setFillColor(sf::Color::White);
            PlayerInfoText[i].setCharacterSize(25);
            PlayerInfoText[i].setPosition(boardleftmost + 10, (i * 60)); //size of names and money right side
        }
        // Set color of player name who is currently rolling the dice to yellow and brightens the token color
        PlayerInfoText[currTurn].setFillColor(sf::Color::Yellow);
        players[currTurn].setActive();

        std::vector<Dice> d;
        // create two die
        for (int i = 0; i < 2; i++)
        {
            d.push_back(Dice());
        }
        for (std::vector<Dice>::size_type i = 0; i < d.size(); i++)
        {
            d[i].roll();
        }
        d[0].setPos(20, 60);
        d[1].setPos(82, 60);

        Button button(10, 122, 134, 50, "Roll");       // Crete button for rolling the dice
        Button buttonBuild(10, 190, 134, 50, "Build"); // Crete button for building huse/hotel

        // create clock for timing message shown of chance
        sf::Clock gameClock;
        sf::Time deltaTime;
        float elapsedTimechance = 2.0f, elapsedTimeSlot = 2.0f;

        // create message that shows on chance card
        sf::Text MessageChance, MessageSlot;
        MessageChance.setFont(PlayerInfoFont);
        MessageChance.setPosition(boardrightcolend + 10, boardTopRowBottom + 10);
        MessageChance.setCharacterSize(24);
        MessageChance.setFillColor(sf::Color::White);
        MessageChance.setString("");

        // create message that shows on slot action
        MessageSlot.setFont(PlayerInfoFont);
        MessageSlot.setPosition(boardrightcolend + 10, boardBottomRowTop - 10);
        MessageSlot.setCharacterSize(24);
        MessageSlot.setFillColor(sf::Color::White);
        MessageSlot.setString("");

        // create ge out of jail card
        sf::RectangleShape GOOJ;
        GOOJ.setFillColor(sf::Color::Magenta);
        GOOJ.setOutlineThickness(1);
        GOOJ.setOutlineColor(sf::Color::Black);
        GOOJ.setSize(sf::Vector2f(10, 10));

        while (window.isOpen())
        {
            deltaTime = gameClock.restart();
            elapsedTimeSlot += deltaTime.asSeconds();
            elapsedTimechance += deltaTime.asSeconds();
            sf::Event eve;
            while (window.pollEvent(eve))
            {
                if (eve.type == sf::Event::Closed) // If cross/close is clicked/pressed
                    window.close();                // close the game
                if (eve.type == sf::Event::KeyPressed)
                {
                    elapsedTimechance = 0;
                    // All the functionality is mapped to key F1 - F12  and 1 - 4 sort of like developer codes
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
                        advanceToGo(players[currTurn], MessageChance);
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2))
                        bankDividend(players[currTurn], MessageChance);
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F3))
                        goBack3Spaces(players[currTurn], MessageChance);
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F4))
                        goToJail(players[currTurn], MessageChance);
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F5))
                        makeRepairs(players[currTurn], MessageChance);
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F6))
                        payPoorTax(players[currTurn], MessageChance);
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F7))
                        tripToReadingRailroad(players[currTurn], MessageChance);
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F8))
                        walkToBoardwalk(players[currTurn], MessageChance);
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F9))
                        electedChairman(players[currTurn], players, MessageChance);
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F10))
                        buildingLoanMatures(players[currTurn], MessageChance);
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F11))
                        getOutOfJailFree(players[currTurn], MessageChance);
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F12))
                        advanceToIllinoisAve(players[currTurn], MessageChance);
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
                        advanceToStCharlesPlace(players[currTurn], MessageChance);
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
                        streetRepairs(players[currTurn], MessageChance);
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
                        advanceToNearestUtility(players[currTurn], MessageChance);
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
                        advanceToNearestRailroad(players[currTurn], MessageChance);
                    else
                        elapsedTimechance += 2;

                    // Gives turn to next player and changes colour of text and token accordingly
                    PlayerInfoText[currTurn].setFillColor(sf::Color::White);
                    players[currTurn].setInActive();
                    CasesForHandlingSlot(players[currTurn], players, MessageChance, MessageSlot, elapsedTimeSlot, elapsedTimechance, window, d, numPlayer);
                    gameClock.restart();
                    for (int i = 0; i < numPlayer; i++)
                        PlayerInfoText[i].setString(players[i].getName() + "\n$" + to_string(players[i].getMoney()));
                    PlayerInfoText[currTurn].setString(players[currTurn].getName() + "\n$" + to_string(players[currTurn].getMoney()));
                    currTurn = (currTurn + 1) % numPlayer;
                    while (players[currTurn].isBankrupt())
                        currTurn = (currTurn + 1) % numPlayer;
                    PlayerInfoText[currTurn].setFillColor(sf::Color::Yellow);
                    players[currTurn].setActive();
                }
                // Check if button is clicked
                if (button.isClicked(sf::Mouse::getPosition(window), eve))
                {
                    // Handle jail logic
                    if (players[currTurn].isInJail())
                    {
                        if (players[currTurn].getTurnsInJail() < 3)
                        {
                            // Roll the dice
                            d[0].roll();
                            d[1].roll();
                            for (int i = 0; i < 2; i++)
                                d[i].draw(window);
                            bool rolledDouble = (d[0].getCurrFace() == d[1].getCurrFace());

                            // Attempt to get out of jail
                            players[currTurn].attemptToGetOut(rolledDouble, window);

                            if (!players[currTurn].isInJail())
                            {
                                // Player is out of jail
                                MessageSlot.setString(players[currTurn].getName() + " is out of jail!");
                                elapsedTimeSlot = 0;

                                players[currTurn].move_slot(d[1].getCurrFace() + d[0].getCurrFace(), boardsize);

                                PlayerInfoText[currTurn].setFillColor(sf::Color::White);
                                players[currTurn].setInActive();
                                CasesForHandlingSlot(players[currTurn], players, MessageChance, MessageSlot, elapsedTimeSlot, elapsedTimechance, window, d, numPlayer);
                                currTurn = (currTurn + 1) % numPlayer;
                                while (players[currTurn].isBankrupt())
                                    currTurn = (currTurn + 1) % numPlayer;
                                gameClock.restart();
                                for (int i = 0; i < numPlayer; i++)
                                    PlayerInfoText[i].setString(players[i].getName() + "\n$" + to_string(players[i].getMoney()));
                                PlayerInfoText[currTurn].setFillColor(sf::Color::Yellow);
                                players[currTurn].setActive();

                                gameClock.restart();
                            }
                            else
                            {
                                std::cout << "Turn injail\n";
                                players[currTurn].incrementTurnsInJail();

                                PlayerInfoText[currTurn].setFillColor(sf::Color::White);
                                players[currTurn].setInActive();
                                currTurn = (currTurn + 1) % numPlayer;
                                while (players[currTurn].isBankrupt())
                                    currTurn = (currTurn + 1) % numPlayer;
                                CasesForHandlingSlot(players[currTurn], players, MessageChance, MessageSlot, elapsedTimeSlot, elapsedTimechance, window, d, numPlayer);
                                gameClock.restart();
                                for (int i = 0; i < numPlayer; i++)
                                    PlayerInfoText[i].setString(players[i].getName() + "\n$" + to_string(players[i].getMoney()));
                                PlayerInfoText[currTurn].setFillColor(sf::Color::Yellow);
                                players[currTurn].setActive();
                            }
                        }
                        else
                        {
                            // Player has spent 3 turns in jail
                            // Roll the dice
                            d[0].roll();
                            d[1].roll();
                            players[currTurn].payFine();
                            players[currTurn].move_slot(d[0].getCurrFace() + d[1].getCurrFace(), boardsize);

                            MessageSlot.setString(players[currTurn].getName() + " has paid a fine of NIS 50 to get out of jail!");
                            elapsedTimeSlot = 0;

                            PlayerInfoText[currTurn].setFillColor(sf::Color::White);
                            players[currTurn].setInActive();
                            currTurn = (currTurn + 1) % numPlayer;
                            while (players[currTurn].isBankrupt())
                                currTurn = (currTurn + 1) % numPlayer;
                            CasesForHandlingSlot(players[currTurn], players, MessageChance, MessageSlot, elapsedTimeSlot, elapsedTimechance, window, d, numPlayer);
                            gameClock.restart();
                            for (int i = 0; i < numPlayer; i++)
                                PlayerInfoText[i].setString(players[i].getName() + "\n$" + to_string(players[i].getMoney()));
                            PlayerInfoText[currTurn].setFillColor(sf::Color::Yellow);
                            players[currTurn].setActive();

                            gameClock.restart();
                        }
                    }
                    else
                    {
                        // roll the die and add the result, then call move slot to move the player respective places
                        d[0].roll();
                        d[1].roll();

                        for (int i = 0; i < 2; i++)
                            d[i].draw(window);
                        // if (d[0].currFace != d[1].currFace)
                        players[currTurn].move_slot(d[0].getCurrFace() + d[1].getCurrFace(), boardsize);
                        // Gives turn to next player and changes colour of text and token accordingly
                        PlayerInfoText[currTurn].setFillColor(sf::Color::White);
                        players[currTurn].setInActive();
                        PlayerInfoText[currTurn].setString(players[currTurn].getName() + "\n$" + to_string(players[currTurn].getMoney()));
                        CasesForHandlingSlot(players[currTurn], players, MessageChance, MessageSlot, elapsedTimeSlot, elapsedTimechance, window, d, numPlayer);
                        gameClock.restart();
                        for (int i = 0; i < numPlayer; i++)
                            PlayerInfoText[i].setString(players[i].getName() + "\n$" + to_string(players[i].getMoney()));
                        if (d[0].getCurrFace() != d[1].getCurrFace())
                        {
                            currTurn = (currTurn + 1) % numPlayer;
                            doubleCounter = 3;
                        }
                        while (players[currTurn].isBankrupt())
                            currTurn = (currTurn + 1) % numPlayer;
                        if (d[0].getCurrFace() == d[1].getCurrFace())
                            doubleCounter--;
                        if (doubleCounter == 0)
                        {
                            goToJail(players[currTurn], MessageChance);
                            currTurn = (currTurn + 1) % numPlayer;
                            while (players[currTurn].isBankrupt())
                                currTurn = (currTurn + 1) % numPlayer;
                            doubleCounter = 3;
                        }
                        PlayerInfoText[currTurn].setFillColor(sf::Color::Yellow);
                        players[currTurn].setActive();
                    }
                }
                if (buttonBuild.isClicked(sf::Mouse::getPosition(window), eve))
                {
                    players[currTurn].buildHouse(*(players[currTurn].getCurrSlot()));
                    for (int i = 0; i < numPlayer; i++)
                        PlayerInfoText[i].setString(players[i].getName() + "\n$" + to_string(players[i].getMoney()));
                }
            }
            // check if more than one player remain
            playersLeft = 0;
            for (int i = 0; i < numPlayer; i++)
            {
                if (players[i].isBankrupt() == false)
                {
                    playersLeft++;
                    winner = &players[i];
                }
            }
            if (playersLeft == 1)
            {
                break;
            }
            // checks if one player has more than 4000 money
            bool moremoney = false;
            for (int i = 0; i < numPlayer; i++)
            {
                if (players[i].getMoney() >= 4000)
                {
                    moremoney = true;
                    winner = &players[i];
                    break;
                }
            }
            if (moremoney)
                break;

            button.update(sf::Mouse::getPosition(window));
            buttonBuild.update(sf::Mouse::getPosition(window));

            window.clear(sf::Color(70, 120, 60)); // create a background color with RGB values
            // window.draw(Board_Sprite);            // draw board
            for (int i = 0; i < boardsize; i++)
            {
                // window.draw(slots[i].slot); // draw slots
                slots[i].draw(window);
            }
            for (std::vector<Player>::size_type  i = 0; i < players.size(); i++)
            {
                players[i].draw(window); // draw each player in start
            }
            for (std::vector<Dice>::size_type  i = 0; i < d.size(); i++)
            {
                d[i].draw(window); // draw dice
            }

            for (std::vector<sf::Text>::size_type  i = 0; i < PlayerInfoText.size(); i++)
            {
                window.draw(PlayerInfoText[i]); // draw name+money text indicating player info
                float x = players[i].getSprite().getPosition().x;
                float y = players[i].getSprite().getPosition().y;
                players[i].getSprite().setPosition(PlayerInfoText[i].getGlobalBounds().width + PlayerInfoText[i].getPosition().x, PlayerInfoText[i].getPosition().y);
                players[i].draw(window); //show token neer money
                if (players[i].getIsJailable() == false)
                {
                    GOOJ.setPosition(players[i].getSprite().getPosition().x, players[i].getSprite().getPosition().y);
                    window.draw(GOOJ);
                }
                for (std::vector<Slot*>::size_type j = 0; j < players[i].getOwnedSlots().size(); j++)
                {
                    float width, height, xposition, yposition;
                    width = players[i].getOwnedSlots()[j]->getSlotShape().getGlobalBounds().width;
                    height = players[i].getOwnedSlots()[j]->getSlotShape().getGlobalBounds().height;
                    xposition = players[i].getOwnedSlots()[j]->getSlotShape().getPosition().x;
                    yposition = players[i].getOwnedSlots()[j]->getSlotShape().getPosition().y;
                    players[i].getOwnedSlots()[j]->setSizeAll(PlayerInfoText[i].getGlobalBounds().height, PlayerInfoText[i].getGlobalBounds().height);
                    players[i].getOwnedSlots()[j]->setPos(players[i].getSprite().getPosition().x + players[i].getSprite().getGlobalBounds().width + (j * players[i].getOwnedSlots()[j]->getSlotShape().getGlobalBounds().height / 3), players[i].getSprite().getPosition().y);
                    players[i].getOwnedSlots()[j]->draw(window);// show the slots neer money
                    players[i].getOwnedSlots()[j]->setSizeAll(width - 4, height - 4); // 4 for outline offset
                    players[i].getOwnedSlots()[j]->setPos(xposition, yposition);
                }
                players[i].getSprite().setPosition(x, y);
            }

            button.draw(window);      // Draw button
            buttonBuild.draw(window); // Draw button

            if (elapsedTimechance < 2)
                window.draw(MessageChance);
            if (elapsedTimeSlot < 2)
                window.draw(MessageSlot);
            window.display();
        }

        // create winner text
        sf::Text WinnerText;
        WinnerText.setFont(font);
        WinnerText.setString(winner->getName() + " Won!!");
        WinnerText.setCharacterSize(64);
        WinnerText.setFillColor(sf::Color::White);
        WinnerText.setPosition((windowSize.x - WinnerText.getGlobalBounds().width) / 2, 50);

        // winner window display
        while (window.isOpen())
        {
            sf::Event eve;
            while (window.pollEvent(eve))
            {
                if (eve.type == sf::Event::Closed) // If cross/close is clicked/pressed
                    window.close();
            }
            window.clear(sf::Color(70, 120, 60)); // create a background color with RGB values
            window.draw(WinnerText);
            window.display();
        }
    }

    void CasesForHandlingSlot(Player &player, std::vector<Player> &players, sf::Text &MessageChance, sf::Text &MessageSlot, float &elapsedTimeSlot, float &elapsedTimechance, sf::RenderWindow &window, std::vector<Dice> &d, int &numplayers)
    {
        // check if current slot is chance or community chest(surprise)
        if (player.getCurrSlot()->getColorGroup() == ChanceColor || player.getCurrSlot()->getColorGroup() == CommunityChestColor)
        {
            Chance_CommunityChest(player, MessageChance, players);
            MessageSlot.setString(player.getName() + " landed on chance/communitychest");
            elapsedTimeSlot = 0;
            elapsedTimechance = 0;
        }
        // check if current slot is a street that can be bought
        if (player.getCurrSlot()->getColorGroup() != CornerColor && player.getCurrSlot()->getColorGroup() != TaxColor && player.getCurrSlot()->getColorGroup() != ChanceColor && player.getCurrSlot()->getColorGroup() != CommunityChestColor)
        {
            handleLandingOnSlot(player, players, *(player.getCurrSlot()), window, MessageSlot, d[0].getCurrFace(), d[1].getCurrFace(), numplayers);
            elapsedTimeSlot = 0;
        }
        // check if player is on taxable slot
        else if (player.getCurrSlot()->getColorGroup() == TaxColor)
        {
            collectTax(player, MessageSlot, numplayers, players);
            elapsedTimeSlot = 0;
        }
        // check if player is on go to jail slot
        else if (player.getCurrSlot()->getColorGroup() == CornerColor && player.getCurrSlot()->getName() == "Go to Jail")
        {
            goToJail(player, MessageSlot);
            elapsedTimeSlot = 0;
        }
    }

    void collectTax(Player &player, sf::Text &message, int &numPlayers, std::vector<Player> &players)
    {
        // checks if player can pay for tax
        if (player.checkBankruptcy(player.getCurrSlot()->getRent()))
        {
            message.setString(player.getName() + " went bankrupt!\n");
        }
        else
        {

            player.setMoney(player.getMoney() - player.getCurrSlot()->getRent());
            std::cout << player.getName() << " paid tax of " << player.getCurrSlot()->getRent() << ".\n";
            message.setString(player.getName() + " paid tax of " + std::to_string(player.getCurrSlot()->getRent()) + ".\n");
        }
    }

    void advanceToGo(Player &player, sf::Text &message);
    void bankDividend(Player &player, sf::Text &message);
    void goBack3Spaces(Player &player, sf::Text &message);
    void goToJail(Player &player, sf::Text &message);
    void makeRepairs(Player &player, sf::Text &message);
    void payPoorTax(Player &player, sf::Text &message);
    void tripToReadingRailroad(Player &player, sf::Text &message);
    void walkToBoardwalk(Player &player, sf::Text &message);
    void electedChairman(Player &player, std::vector<Player> &players, sf::Text &message);
    void buildingLoanMatures(Player &player, sf::Text &message);
    void getOutOfJailFree(Player &player, sf::Text &message);
    void advanceToIllinoisAve(Player &player, sf::Text &message);
    void advanceToStCharlesPlace(Player &player, sf::Text &message);
    void streetRepairs(Player &player, sf::Text message);
    void advanceToNearestUtility(Player &player, sf::Text &message);
    void advanceToNearestRailroad(Player &player, sf::Text &message);

    void Chance_CommunityChest(Player &player, sf::Text &MessageChance, std::vector<Player> &players);
    void handleLandingOnSlot(Player &player, std::vector<Player> &players, Slot &slot, sf::RenderWindow &window, sf::Text &message, int d1, int d2, int &numplayers);
    void createslot(std::vector<Slot> &slots, sf::Texture &slot_texture, sf::Vector2u windowSize, sf::Font &font);
};

#endif // GAME_HPP