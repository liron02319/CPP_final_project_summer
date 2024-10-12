#ifndef GAME_HPP
#define GAME_HPP

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
private:
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

    int doubleCounter;

    
public:
    Game() ;


    /*

    void run() function in the Game class is responsible for running the main game logic, 
    which includes setting up the game board,
    loading resources (textures, fonts, etc.), creating players, and handling player turns.
    */

    void run();



    void CasesForHandlingSlot(Player &player, std::vector<Player> &players, sf::Text &MessageChance, sf::Text &MessageSlot, float &elapsedTimeSlot, float &elapsedTimechance, sf::RenderWindow &window, std::vector<Dice> &d, int &numplayers);

    void collectTax(Player &player, sf::Text &message, int &numPlayers, std::vector<Player> &players);

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
    void createslot(std::vector<Slot> &slots, sf::Vector2u windowSize, sf::Font &font);


    

};

#endif // GAME_HPP