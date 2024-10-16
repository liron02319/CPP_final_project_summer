
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
#include "Game.hpp"



using namespace std;



    Game::Game() 
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

    void Game::run()
    {

          // Get the desktop resolution for fullscreen mode
        sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
        //create the window of the game
        sf::RenderWindow window(desktopMode, "Monopoly Card Actions", sf::Style::Default);

        
        Openning openning;
        openning.displayOpening(window); // Display the opening window


        /*
        sf::Texture: It represents an image that is loaded from a file and stored in memory (like a texture on the GPU). 
        It contains the pixel data but cannot be drawn directly.
         It's like the "image data" stored in the background.

         sf::Texture: Stores the image data.
        sf::Sprite: Displays the texture and allows manipulation (e.g., scaling, rotation).
        */

        // loading textures for board, slots and player(tokens)
        sf::Texture Board_Text, player_texure;
        Board_Text.loadFromFile("images/Game_board.jpg");
        player_texure.loadFromFile("images/tokens.png");
     //   slot_texture.loadFromFile("images/Game_board.jpg");



/*
    sf::Sprite: It is used to display textures in the window. 
    A sprite contains a texture and allows you to position, scale, rotate, 
    and draw it on the screen.
     You assign a texture to a sprite, and the sprite handles the visual representation.

*/
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
        /*
        sf::FloatRect is a class in SFML that represents a rectangle using floating-point numbers.
        It is used to define areas, such as the size and position of an object in a 2D space.

        */
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
        if (!font.loadFromFile("Fonts/bebas/Bebas-Regular.ttf"))
            {
                std::cerr << "Error loading font\n";
            }


        std::vector<Slot> slots;
        //create the board-make the slots visualy(It sets the position of each slot on the screen (X and Y coordinates) using setSprite(), which aligns them visually on the board.)
        createslot(slots, windowSize, font);

        // Create players
        std::vector<Player> players;
        int doubleCounter = 3; // max double rolls in a row
        int playersLeft = 0;   // number of players left in game
        Player *winner;        // points to winner



        // Get names and num of players playing and set the names for player
        int numPlayer = 0; 
        Menu menu; //load menu and get the names and number of the player
        std::vector<std::string> name_list = menu.loadMenu(numPlayer, window);
        if (numPlayer == 0) //if error
            return;

        for (int i = 0; i < numPlayer; i++) //create players (name,index,board,first slot(for positon) )
        {
            players.push_back(Player(name_list[i], i, slots, slots[0]));
        }

        // Set each player's sprite with a token from the sprite sheet 
        //set the player sprite on the slot on the board

        for (std::vector<Player>::size_type  i = 0; i < players.size(); i++)
        {
            players[i].setTexture(player_texure, slots[0].getSlotShape().getGlobalBounds().width); // Set to each player texture sprite with token index i
            players[i].setPos(slots[0].getSlotShape().getPosition().x, slots[0].getSlotShape().getPosition().y);         //set the player sprite on the slot on the board

        }

        int currTurn = 0;

        // Text that shows player info
        sf::Font PlayerInfoFont; //font
        PlayerInfoFont.loadFromFile("Fonts/bebas/Bebas-Regular.ttf");

        std::vector<sf::Text> PlayerInfoText; //show the name+money right to board 
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
            PlayerInfoText[i].setPosition(boardleftmost + 10, (i * 60)); //size and names and money right side
        }
        
        // Set color of player name who is currently rolling the dice to yellow and brightens the token color
        PlayerInfoText[currTurn].setFillColor(sf::Color::Yellow);
        players[currTurn].setActive();

        //dice
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
        d[0].setPos(20, 60); //positon the dice sprite in board
        d[1].setPos(82, 60);

        Button button(10, 122, 134, 50, "Roll");       // Create button for rolling the dice
        Button buttonBuild(10, 190, 134, 50, "Build"); // Create button for building huse/hotel


        // create clock for timing message shown of chance
        sf::Clock gameClock; //This is used to track the elapsed time in the game. It allows you to measure the time between frames and can be used to manage timing events, like displaying messages for a limited duration.
        sf::Time deltaTime; //This will store the amount of time that has passed since the last frame, allowing you to update your game logic in a time-consistent manner.
        float elapsedTimechance = 3.0f, elapsedTimeSlot = 3.0f; //These variables keep track of the time that has passed since the last chance card or slot action message was displayed. They are initialized to 2 seconds, meaning the messages will be shown for this duration.

        //showing slot details
        sf::Text slotDetailsText; // Text for showing slot details
        slotDetailsText.setFont(PlayerInfoFont); // Assuming PlayerInfoFont is already loaded
        slotDetailsText.setCharacterSize(24);
        slotDetailsText.setFillColor(sf::Color::White);
        slotDetailsText.setPosition(boardrightcolend -10, boardTopRowBottom + 50); //Sets the position of the text on the screen.

        // create message that shows on chance card
        sf::Text MessageChance, MessageSlot; //This class is used to create and manage text displayed on the screen.
        MessageChance.setFont(PlayerInfoFont); //font
        MessageChance.setPosition(boardrightcolend - 10, boardTopRowBottom + 10); //Sets the position of the text on the screen.
        MessageChance.setCharacterSize(24);
        MessageChance.setFillColor(sf::Color::White);
        MessageChance.setString("");

        // create message that shows on slot action
        MessageSlot.setFont(PlayerInfoFont);
        MessageSlot.setPosition(boardrightcolend + 10, boardBottomRowTop -120);
        MessageSlot.setCharacterSize(24);
        MessageSlot.setFillColor(sf::Color::White);
        MessageSlot.setString("");

        // create ge out of jail card
        sf::RectangleShape GOOJ;
        GOOJ.setFillColor(sf::Color::Magenta);
        GOOJ.setOutlineThickness(1);
        GOOJ.setOutlineColor(sf::Color::Black);
        GOOJ.setSize(sf::Vector2f(10, 10));


        sf::Text SlotCardPrint; //This class is used to create and manage text displayed on the screen.
        SlotCardPrint.setFont(PlayerInfoFont); //font
        SlotCardPrint.setPosition(boardrightcolend - 10, boardTopRowBottom + 10); //Sets the position of the text on the screen.
        SlotCardPrint.setCharacterSize(24);
        SlotCardPrint.setFillColor(sf::Color::White);
        SlotCardPrint.setString("");

        while (window.isOpen()) //the game running
        {
            deltaTime = gameClock.restart(); //Resets the clock and returns the elapsed time since the last call.
            elapsedTimeSlot += deltaTime.asSeconds(); //re updated by adding the elapsed seconds, allowing you to keep track of how long the messages have been displayed.
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

                    //change the player name+money to white(is turn is over)
                    PlayerInfoText[currTurn].setFillColor(sf::Color::White);
                    players[currTurn].setInActive();
                    //do the CasesForHandlingSlot after the rolling
                    CasesForHandlingSlot(players[currTurn], players, MessageChance, MessageSlot, elapsedTimeSlot, elapsedTimechance, window, d, numPlayer);
                    gameClock.restart(); //restart the clock
                    for (int i = 0; i < numPlayer; i++) //GET THE NAME AND MONEY FOR FOR SHOW RIGHT TO BOARD
                        PlayerInfoText[i].setString(players[i].getName() + "\n$" + to_string(players[i].getMoney()));

                    PlayerInfoText[currTurn].setString(players[currTurn].getName() + "\n$" + to_string(players[currTurn].getMoney()));
                    currTurn = (currTurn + 1) % numPlayer;
                    while (players[currTurn].isBankrupt())
                        currTurn = (currTurn + 1) % numPlayer;
                    PlayerInfoText[currTurn].setFillColor(sf::Color::Yellow);
                    players[currTurn].setActive();
                }

                if (eve.type == sf::Event::MouseButtonPressed && eve.mouseButton.button == sf::Mouse::Left) 
                {
                    slotDetailsText.setString("");
                    elapsedTimechance = 0;
                            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                            // Check if any owned slots were clicked
                            for (std::vector<Player>::size_type i = 0; i < players.size(); i++) {
                                for (std::vector<Slot*>::size_type j = 0; j < players[i].getOwnedSlots().size(); j++) {
                                    if (players[i].getOwnedSlots()[j]->getSlotShape().getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                                        // Display slot details
                                        Slot* clickedSlot = players[i].getOwnedSlots()[j];
                                        std::string details = "Name: " + clickedSlot->getName() + "\nOwner:"  + clickedSlot->getOwnerName() +"\nRent: " + std::to_string(clickedSlot->getRent())+"\nhousePrice: " + std::to_string(clickedSlot->getHousePrice());
                                        slotDetailsText.setString(details);

                                        std::cout << "Clicked Slot: " << clickedSlot->getName() << ", Rent: " << clickedSlot->getRent() << std::endl;
                                        break; // Exit the loop if a slot is clicked
                                    }
                                }
                            }
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
                            bool rolledDouble = (d[0].getCurrFace() == d[1].getCurrFace()); //if player get double

                            // Attempt to get out of jail
                            players[currTurn].attemptToGetOut(rolledDouble, window);


                            if (!players[currTurn].isInJail()) //if player is out of jail
                            {
                                // Player is out of jail
                                MessageSlot.setString(players[currTurn].getName() + " is out of jail!");
                                std::cout << players[currTurn].getName() << " is out of jail!.\n";

                                elapsedTimeSlot = 0;

                             //   players[currTurn].move_slot(d[1].getCurrFace() + d[0].getCurrFace(), boardsize);

                                PlayerInfoText[currTurn].setFillColor(sf::Color::White);
                                players[currTurn].setInActive();
                              //  CasesForHandlingSlot(players[currTurn], players, MessageChance, MessageSlot, elapsedTimeSlot, elapsedTimechance, window, d, numPlayer);
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

                            else  //if the player is NOT out of jail
                            { 
                                std::cout << players[currTurn].getName() <<" Turn injail:" <<  players[currTurn].getTurnsInJail()<<endl;
                               // players[currTurn].incrementTurnsInJail();

                                PlayerInfoText[currTurn].setFillColor(sf::Color::White);
                                players[currTurn].setInActive();
                                currTurn = (currTurn + 1) % numPlayer;
                                while (players[currTurn].isBankrupt())
                                    currTurn = (currTurn + 1) % numPlayer;
                                    
                              //  CasesForHandlingSlot(players[currTurn], players, MessageChance, MessageSlot, elapsedTimeSlot, elapsedTimechance, window, d, numPlayer);
                                gameClock.restart();
                                //for (int i = 0; i < numPlayer; i++)
                                  //  PlayerInfoText[i].setString(players[i].getName() + "\n$" + to_string(players[i].getMoney()));
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
                            elapsedTimechance = 0;

                            PlayerInfoText[currTurn].setFillColor(sf::Color::White);
                            players[currTurn].setInActive();



                            currTurn = (currTurn + 1) % numPlayer;
                            while (players[currTurn].isBankrupt())
                                currTurn = (currTurn + 1) % numPlayer;


                           // CasesForHandlingSlot(players[currTurn], players, MessageChance, MessageSlot, elapsedTimeSlot, elapsedTimechance, window, d, numPlayer);
                           // gameClock.restart();
                            for (int i = 0; i < numPlayer; i++)
                                PlayerInfoText[i].setString(players[i].getName() + "\n$" + to_string(players[i].getMoney()));
                            PlayerInfoText[currTurn].setFillColor(sf::Color::Yellow);
                            players[currTurn].setActive();                   
                            gameClock.restart();

                            break; // Skip their turn, do not handle the slot or show messages


                            
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

                     
                            ///

                        // Immediately display the updated player position before button is pressed
                        for (int i = 0; i < boardsize; i++)
                        {
                            slots[i].draw(window); // draw slots
                        }
                        for (std::vector<Player>::size_type i = 0; i < players.size(); i++)
                        {
                            players[i].draw(window); // draw each player token at updated position
                        }
                        
                        // Other rendering logic (like player info, messages, etc.)
                      //  window.display();
                        
                        ////


              

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
                if(buttonBuild.isClicked(sf::Mouse::getPosition(window), eve)) //if button build clicked
                {

                     if (((players[currTurn].getCurrSlot()->getOwnerName())) == players[currTurn].getName() && players[currTurn].canBuildHouse(*(players[currTurn].getCurrSlot())) && players[currTurn].getSamePositionLastTurn()==false )
                        {
                            // Enable the build button because the player owns this slot
                            players[currTurn].buildHouse(*(players[currTurn].getCurrSlot()));
                            MessageSlot.setString(players[currTurn].getName() + " you can build a House!");
                            int rent = (*(players[currTurn].getCurrSlot())).calculateRent(); //calculate the rent 
                            (*(players[currTurn].getCurrSlot())).setRent(rent);

                                elapsedTimeSlot = 0;

                             //   players[currTurn].move_slot(d[1].getCurrFace() + d[0].getCurrFace(), boardsize);

                                PlayerInfoText[currTurn].setFillColor(sf::Color::White);
                                players[currTurn].setInActive();
                              //  CasesForHandlingSlot(players[currTurn], players, MessageChance, MessageSlot, elapsedTimeSlot, elapsedTimechance, window, d, numPlayer);
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
                            // Disable the build button because the player doesn't own the slot
                            MessageSlot.setString(players[currTurn].getName() + " you can NOT build a House!"); 

                        }
                }


                // After updating the text, ensure the window is refreshed
   

                playersLeft = 0;
                for (int i = 0; i < numPlayer; i++)
                {
                    if (players[i].isBankrupt() == false)
                    {
                        playersLeft++;
                        winner = &players[i];
                    }
                }
             
  
            }

   if (playersLeft == 1)
                {
                    break;
                }

            // check if more than one player remain
           
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

            //slot and messages disapear after 2 sec
            if (elapsedTimechance < 3) //print messages
                 window.draw(slotDetailsText);
            if (elapsedTimechance < 3) //print messages
                window.draw(MessageChance);
            if (elapsedTimeSlot < 3)
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

 