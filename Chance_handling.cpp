#include "Game.hpp"
#include <SFML/Graphics.hpp> // Include necessary SFML headers
#include <vector>
#include <algorithm> // For std::min

// function for assigning chance when player lands on a surprise slot
void Game::Chance_CommunityChest(Player &player, sf::Text &MessageChance, std::vector<Player> &players)
{
    MessageChance.setString(player.getName() + " landed on chance/communitychest");

    int random_outcome = rand() % 16; // can give any outcome of the 16
    if (random_outcome == 0)
        advanceToGo(player, MessageChance);
    else if (random_outcome == 1)
        bankDividend(player, MessageChance);
    else if (random_outcome == 2)
        goBack3Spaces(player, MessageChance);
    else if (random_outcome == 3)
        goToJail(player, MessageChance);
    else if (random_outcome == 4)
        makeRepairs(player, MessageChance);
    else if (random_outcome == 5)
        payPoorTax(player, MessageChance);
    else if (random_outcome == 6)
        tripToReadingRailroad(player, MessageChance);
    else if (random_outcome == 7)
        walkToBoardwalk(player, MessageChance);
    else if (random_outcome == 8)
        electedChairman(player, players, MessageChance);
    else if (random_outcome == 9)
        buildingLoanMatures(player, MessageChance);
    else if (random_outcome == 10)
        getOutOfJailFree(player, MessageChance);
    else if (random_outcome == 11)
        advanceToIllinoisAve(player, MessageChance);
    else if (random_outcome == 12)
        advanceToStCharlesPlace(player, MessageChance);
    else if (random_outcome == 13)
        streetRepairs(player, MessageChance);
    else if (random_outcome == 14)
        advanceToNearestUtility(player, MessageChance);
    else if (random_outcome == 15)
        advanceToNearestRailroad(player, MessageChance);
}

// advance to nearest railroad
void Game::advanceToNearestRailroad(Player &player, sf::Text &message)
{
    // Assume Railroads are at 5, 15, 25, 35
    player.move_slot(1, boardsize);
    while (!player.getCurrSlot()->getIsRail())
    {
        player.move_slot(1, boardsize);
    }
    std::cout << player.getName() << " advanced to the nearest Railroad.\n";
    message.setString(player.getName() + " advanced to the nearest Railroad.\n");
}

// advance to go
void Game::advanceToGo(Player &player, sf::Text &message)
{
    player.setPosition(0);
    player.move_slot(0, boardsize);
    player.setMoney(player.getMoney() + 200);
    std::cout << player.getName() << " advanced to Go and collected $200.\n";
    message.setString(player.getName() + " advanced to Go and collected $200.\n");
}


// collect bank dividend
void Game::bankDividend(Player &player, sf::Text &message)
{
    player.setMoney(player.getMoney() + 50);
    std::cout << player.getName() << " collected a $50 dividend from the bank.\n";
    message.setString(player.getName() + " collected a $50 dividend from the bank.\n");
}

// go back 3 space
void Game::goBack3Spaces(Player &player, sf::Text &message)
{
    int newPosition = player.getPosition() - 3;

    // If the new position is negative, wrap around to the end of the board
    if (newPosition < 0)
    {
        newPosition += boardsize; // Wrap around if necessary
    }

    player.setPosition(newPosition);

    // After moving back, handle any slot logic, rent, etc.
  //  int money = player.getMoney();
    player.move_slot(0, boardsize); // Move slot for this player
 //   player.setMoney(money);

    std::cout << player.getName() << " went back 3 spaces.\n";
    message.setString(player.getName() + " went back 3 spaces.\n");
}

// goes to jail without getting money
void Game::goToJail(Player &player, sf::Text &message)
{
  //  int money = player.getMoney();
    player.move_slot(1, boardsize);
    while (player.getCurrSlot()->getName() != "Jail")
    {
        player.move_slot(1, boardsize);
    }
    player.setInJail(true);
 //   player.setMoney(money); 
  //  player.setInJail(true);
    std::cout << player.getName() << " went directly to Jail!\n";
    message.setString(player.getName() + " went directly to Jail!\n");
}

// make repairs on houses and hotels
void Game::makeRepairs(Player &player, sf::Text &message)
{
    int cost = player.getHouses() * 25 + player.getHotels() * 100;
    player.setMoney(player.getMoney() - cost);

    std::cout << player.getName() << " paid $" << cost << " for property repairs.\n";
    message.setString(player.getName() + " paid $" + std::to_string(cost) + " for property repairs.\n");
}

// pay poor tax of 15
void Game::payPoorTax(Player &player, sf::Text &message)
{
    player.setMoney(player.getMoney() -15);

    std::cout << player.getName() << " paid a poor tax of $15.\n";
    message.setString(player.getName() + " paid a poor tax of $15.\n");
}

//go to reading rail road if pass go collect 200
void Game::tripToReadingRailroad(Player &player, sf::Text &message)
{
    player.move_slot(1, boardsize);
    while (player.getCurrSlot()->getName() != "Reading Railroad")
    {
        player.move_slot(1, boardsize);
    }
    std::cout << player.getName() << " took a trip to Reading Railroad.\n";
    message.setString(player.getName() + " took a trip to Reading Railroad.\n");
}

// go to broadwalk
void Game::walkToBoardwalk(Player &player, sf::Text &message)
{
    player.move_slot(1, boardsize);
    while (player.getCurrSlot()->getName() != "Boardwalk")
    {
        player.move_slot(1, boardsize);
    }
    std::cout << player.getName() << " advanced to Boardwalk.\n";
    message.setString(player.getName() + " advanced to Boardwalk.\n");
}

// pay every player 50
void Game::electedChairman(Player &player, std::vector<Player> &players, sf::Text &message)
{
    int totalCost = (players.size() - 1) * 50;
    
        player.setMoney(player.getMoney() - totalCost);

    for (auto &p : players)
    {
        if (p.getName() != player.getName())
        {
          
          p.setMoney(p.getMoney() +50);

        }
    }
    std::cout << player.getName() << " was elected Chairman of the Board and paid each player $50.\n";
    message.setString(player.getName() + " was elected Chairman of the Board and paid each player $50.\n");
}

// collect 150
void Game::buildingLoanMatures(Player &player, sf::Text &message)
{
    player.setMoney(player.getMoney() +150 );

    std::cout << player.getName() << " collected $150 from a building loan maturity.\n";
    message.setString(player.getName() + " collected $150 from a building loan maturity.\n");
}

// get card to get out of jail
void Game::getOutOfJailFree(Player &player, sf::Text &message)
{
    // This card could be stored for later use
    player.setJailable(false);
    std::cout << player.getName() << " received a 'Get Out of Jail Free' card.\n";
    message.setString(player.getName() + " received a 'Get Out of Jail Free' card.\n");
}

// go to illinois aveneue
void Game::advanceToIllinoisAve(Player &player, sf::Text &message)
{
    player.move_slot(1, boardsize);
    while (player.getCurrSlot()->getName()  != "Illinois Avenue")
    {
        player.move_slot(1, boardsize);
    }
    std::cout << player.getName() << " advanced to Illinois Avenue.\n";
    message.setString(player.getName() + " advanced to Illinois Avenue.\n");
}

// go to st charles
void Game::advanceToStCharlesPlace(Player &player, sf::Text &message)
{
    player.move_slot(1, boardsize);
    while (player.getCurrSlot()->getName()  != "St. Charles Place")
    {
        player.move_slot(1, boardsize);
    }
    std::cout << player.getName() << " advanced to St. Charles Place.\n";
    message.setString(player.getName() + " advanced to St. Charles Place.\n");
}

// do street repairs
void Game::streetRepairs(Player &player, sf::Text message)
{
    int cost = player.getHouses() * 40 + player.getHotels() * 115;
    player.setMoney(player.getMoney() - cost);

    std::cout << player.getName() << " paid $" << cost << " for street repairs.\n";
    message.setString(player.getName() + " paid $" + std::to_string(cost) + " for street repairs.\n");
}

// go to next utility
void Game::advanceToNearestUtility(Player &player, sf::Text &message)
{
    // Assume Utilities are at positions 12 and 28
    player.move_slot(1, boardsize);
    while (!player.getCurrSlot()->getIsCompany())
    {
        player.move_slot(1, boardsize);
    }
    std::cout << player.getName() << " advanced to the nearest Utility.\n";
    message.setString(player.getName() + " advanced to the nearest Utility.\n");
}