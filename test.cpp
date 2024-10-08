#include "doctest.h"
#include "Player.hpp"
#include "Slot.hpp"
#include "Dice.hpp"
#include <vector>
#include <SFML/Graphics.hpp>




// Test Slot Class

TEST_CASE("Slot Constructor") {
  //(position at board,name,colorGroup,price,rent, houseprice,rentWithHouse,rentWithHotel)
    Slot slot(1, "Boardwalk", sf::Color::Blue, 400, 50, 100, 500, 1000);
    CHECK(slot.getSlotNum() == 1);
    CHECK(slot.getName() == "Boardwalk");
    CHECK(slot.getColorGroup() == sf::Color::Blue);
    CHECK(slot.getPrice() == 400);
    CHECK(slot.getRent() == 50);
    CHECK(slot.getHousePrice() == 100);
    CHECK(slot.getRentWithHouse() == 500);
    CHECK(slot.getRentWithHotel() == 1000);
}

TEST_CASE("Slot get/set Price") {
    Slot slot(1, "Park Lane", sf::Color::Red, 350, 50, 200, 500, 1000);
    CHECK(slot.getPrice() == 350);
    slot.setPrice(400);
    CHECK(slot.getPrice() == 400);
}

TEST_CASE("Slot get/set IsOwne-Ownership") {
    Slot slot(1, "Park Lane", sf::Color::Red, 350, 50, 200, 500, 1000);
    CHECK(slot.getIsOwned() == false);
    slot.setIsOwned(true);
    CHECK(slot.getIsOwned() == true);
}

TEST_CASE("Slot get/set House Price") {
    Slot slot(1, "Park Lane", sf::Color::Red, 350, 50, 200, 500, 1000);
    CHECK(slot.getHousePrice() == 200);
    slot.setHousePrice(250);
    CHECK(slot.getHousePrice() == 250);
}

TEST_CASE("Slot get/set Owner Name") {
    Slot slot(1, "Park Lane", sf::Color::Red, 350, 50, 200, 500, 1000);
    CHECK(slot.getOwnerName() == "");
    slot.setOwnerName("Player1");
    CHECK(slot.getOwnerName() == "Player1");
}

TEST_CASE("Slot get/set Houses") {
    Slot slot(1, "Park Lane", sf::Color::Red, 350, 50, 200, 500, 1000);
    CHECK(slot.getHouses() == 0);
    slot.setHouses(2);
    CHECK(slot.getHouses() == 2);
    slot.addHouse();
    CHECK(slot.getHouses() == 3);
}

TEST_CASE("Slot get/set Hotels") {
    Slot slot(1, "Park Lane", sf::Color::Red, 350, 50, 200, 500, 1000);
    CHECK(slot.getHotels() == 0);
    slot.setHotels(1);
    CHECK(slot.getHotels() == 1);
}

TEST_CASE("Slot get/set Rent") {
    Slot slot(1, "Park Lane", sf::Color::Red, 350, 50, 200, 500, 1000);
    CHECK(slot.getRent() == 50);
    slot.setRent(60);
    CHECK(slot.getRent() == 60);
}

TEST_CASE("Slot get/set Rent With House") {
    Slot slot(1, "Park Lane", sf::Color::Red, 350, 50, 200, 500, 1000);
    CHECK(slot.getRentWithHouse() == 500);
    slot.setRentWithHouse(600);
    CHECK(slot.getRentWithHouse() == 600);
}

TEST_CASE("Slot get/set Rent With Hotel") {
    Slot slot(1, "Park Lane", sf::Color::Red, 350, 50, 200, 500, 1000);
    CHECK(slot.getRentWithHotel() == 1000);
    slot.setRentWithHotel(1200);
    CHECK(slot.getRentWithHotel() == 1200);
}

TEST_CASE("Slot get/set isRail") {
    Slot slot(1, "Railroad", sf::Color::Black, 200, 25, 0, 0, 0);
    CHECK(slot.getIsRail() == false);
    slot.setIsRail(true);
    CHECK(slot.getIsRail() == true);
}

TEST_CASE("Slot get/set isCompany") {
    Slot slot(1, "Electric Company", sf::Color::White, 150, 25, 0, 0, 0);
    CHECK(slot.getIsCompany() == false);
    slot.setIsCompany(true);
    CHECK(slot.getIsCompany() == true);
}

TEST_CASE("Slot get/set Name") {
    Slot slot(1, "Park Lane", sf::Color::Red, 350, 50, 200, 500, 1000);
    CHECK(slot.getName() == "Park Lane");
    slot.setName("Boardwalk");
    CHECK(slot.getName() == "Boardwalk");
}

TEST_CASE("Slot get/set Color Group") {
    Slot slot(1, "Park Lane", sf::Color::Red, 350, 50, 200, 500, 1000);
    CHECK(slot.getColorGroup() == sf::Color::Red);
    slot.setColorGroup(sf::Color::Blue);
    CHECK(slot.getColorGroup() == sf::Color::Blue);
}

TEST_CASE("Slot get/set SlotNumber") {
    Slot slot(1, "Park Lane", sf::Color::Red, 350, 50, 200, 500, 1000);
    CHECK(slot.getSlotNum() == 1);
    slot.setSlotNum(2);
    CHECK(slot.getSlotNum() == 2);
}

TEST_CASE("Slot getSlotShape and setSlotShapeSize Shape") {
    Slot slot(1, "Park Lane", sf::Color::Red, 350, 50, 200, 500, 1000);
    sf::RectangleShape shape = slot.getSlotShape();
    slot.setSlotShapeSize(sf::Vector2f(100.f, 50.f));
    CHECK(slot.getSlotShape().getSize() == sf::Vector2f(100.f, 50.f));
}

TEST_CASE("Slot Position and Size All") {
    Slot slot(1, "Park Lane", sf::Color::Red, 350, 50, 200, 500, 1000);
    slot.setPos(200.f, 300.f);
    slot.setSizeAll(100.f, 50.f); // Assume this method affects all elements
    sf::RectangleShape shape = slot.getSlotShape();
    CHECK(shape.getSize() == sf::Vector2f(100.f, 50.f));
}

TEST_CASE("Slot Sprite Setup") {
    Slot slot(1, "Park Lane", sf::Color::Red, 350, 50, 200, 500, 1000);
    sf::Font font;
    // Load the font properly here if required.
    slot.setSprite(200.f, 300.f, font, 100, 50); // This method is mainly visual
}



TEST_CASE("Slot Calculate Rent") {

    Slot slot(0, "Park Lane", sf::Color::Red, 350, 50, 200, 500, 1000);

    std::vector<Slot> boardSlots = {slot};
    Player player("TestPlayer", 0, boardSlots, slot);
    

    player.setMoney(9000);
    player.buySlot(slot);
    CHECK(player.getMoney() == 8650);

    CHECK(slot.calculateRent() == 50);
    CHECK(slot.getHouses() == 0);
    CHECK(slot.getRent() == 50);
    

    player.buildHouse(slot);
    CHECK(slot.getHouses() == 1);    //500     * (2 ^ (1-1)) =500*1=500
    CHECK(slot.calculateRent() == 500);
    CHECK(slot.getRentWithHouse() == 500);

    //std::cout << "TEST2:" << std::endl;

    player.buildHouse(slot);
    CHECK(slot.getHouses() == 2);          //500     * (2 ^ (2-1)) =500*2=1000
    CHECK(slot.calculateRent() == 1000); // houseprice * ( 2^(numberhouse-1) )
    CHECK(slot.getRentWithHouse()* (std::pow(2, slot.getHouses() - 1)) == 1000);

    player.buildHouse(slot);
    CHECK(slot.getHouses() == 3);          //500     * (2 ^ (3-1))=500*4=2000
    CHECK(slot.calculateRent() == 2000); // houseprice * ( 2^(numberhouse-1) )
    CHECK(slot.getRentWithHouse() * (std::pow(2, slot.getHouses() - 1)) == 2000);

    player.buildHouse(slot);
    CHECK(slot.getHouses() == 4);          //500     * (2 ^ (4-1))= 500*8=4000
    CHECK(slot.calculateRent() == 4000); // houseprice * ( 2^(numberhouse-1) )
    CHECK(slot.getRentWithHouse()* (std::pow(2, slot.getHouses() - 1)) == 4000);

}


TEST_CASE("Slot Equality Operator") {
    Slot slot1(1, "Park Lane", sf::Color::Red, 350, 50, 200, 500, 1000);
    Slot slot2(1, "Park Lane", sf::Color::Red, 350, 50, 200, 500, 1000);
    
    CHECK(slot1 == slot2);

  std::vector<Slot> boardSlots = {slot1,slot2};
    Player player("TestPlayer", 0, boardSlots, slot1);

    player.buySlot(slot1);
    CHECK(!(slot1 == slot2));


}





////////////////////////////////////////////////////////////////////////////////////////////
// Test Player Class


TEST_CASE("Player class functionality with Slot interaction") {
    sf::Color blueColor = sf::Color::Blue;

    Slot slot1(0, "Boardwalk", blueColor, 400, 50, 200, 100, 200);
    Slot slot2(1, "Park Place", blueColor, 350, 35, 150, 80, 160);
    std::vector<Slot> boardSlots = {slot1, slot2};

    SUBCASE("Player can buy a slot and update ownership status") {
        Player player("TestPlayer", 0, boardSlots, slot1);
        player.setMoney(1000);

        // Ensure player can buy the slot
        bool purchased = player.buySlot(slot1);

        CHECK(purchased == true);               // Slot was purchased
        CHECK(player.getMoney() == 600);        // Money deducted
        CHECK(slot1.getIsOwned() == true);      // Slot is now owned
        CHECK(slot1.getOwnerName() == "TestPlayer"); // Player owns the slot

        slot1.setOwnerName(""); //default for next test
        CHECK(slot1.getOwnerName() == ""); // Player owns the slot


    }

    SUBCASE("Player cannot buy a slot if not have enough money ") {
        Player player("TestPlayer", 0, boardSlots, slot1);
        player.setMoney(300); // Not enough money for the slot

        bool purchased = player.buySlot(slot1);

        CHECK(purchased == false);            // Slot was not purchased
        CHECK(player.getMoney() == 300);      // Money should remain unchanged
        CHECK(slot1.getIsOwned() == false);   // Slot is still not owned

          slot1.setOwnerName(""); //default for next test
        CHECK(slot1.getOwnerName() == ""); // Player owns the slot
    }


//housecheck
    //Slot slot1(0, "Boardwalk", blueColor, 400, 50, 200, 100, 200);
   // Slot slot2(1, "Park Place", blueColor, 350, 35, 150, 80, 160);

    SUBCASE("Player can build houses on owned slots") {
        Player player("TestPlayer", 0, boardSlots, slot1);
        player.setMoney(1000);

        // Buy the slot first
        bool purchased = player.buySlot(slot1);
        CHECK(purchased == true);
        CHECK(player.getMoney() == 600);

            //std::cout << "slot1afterbuyslot:" << slot1.getHouses() << std::endl;

        // Build a house
        bool canBuild = player.buildHouse(slot1);
       CHECK(canBuild == false);               // House should not be built because no have slot2(need all colors street to build)
        CHECK(player.getMoney() == 600);
           // std::cout << "cantbuildhouseyet:" << slot1.getHouses() << std::endl;


        canBuild = player.buySlot(slot2);     //buy slot2
       CHECK(canBuild == true);               // House should be built
        CHECK(player.getMoney() == 250);


        CHECK(slot1.getOwnerName() == "TestPlayer"); // Player owns the slot
        CHECK(slot2.getOwnerName() == "TestPlayer"); // Player owns the slot

       
//slot1 and slot2 same numberofhouses
     canBuild = player.buildHouse(slot1);
       CHECK(canBuild == true);               // House should be built
        CHECK(slot1.getHouses() == 1);         // Slot should now have 1 house
        CHECK(player.getMoney() == 50);       // Money deducted for house

     //slot1 with 1 house and slot2 with 0 house
                player.setMoney(1000);
     canBuild = player.buildHouse(slot1);
       CHECK(canBuild == false);               // House should not be built
        CHECK(slot1.getHouses() == 1);         // Slot should now have 1 house
        CHECK(player.getMoney() == 1000);       // Money deducted for house




     canBuild = player.buildHouse(slot2);      //slot1 with 1 house and slot2 with 1 house now

       CHECK(canBuild == true);               // House should  be built
        CHECK(slot2.getHouses() == 1);         // Slot should now have 1 house
        CHECK(player.getMoney() == 850);       // Money deducted for house

       //they got each slot 1 house

        canBuild = player.buildHouse(slot1);
       CHECK(canBuild == true);               // House should  be built
        CHECK(slot1.getHouses() == 2);         // Slot should now have 1 house
        CHECK(player.getMoney() == 650);       // Money deducted for house


        CHECK(slot1.getOwnerName() == "TestPlayer"); // Player owns the slot
        CHECK(slot2.getOwnerName() == "TestPlayer"); // Player owns the slot

      //  slot1.setOwnerName(""); //default for next test
     //   CHECK(slot1.getOwnerName() == ""); // Player owns the slot
      //  slot2.setOwnerName("");  //default for next test
       // CHECK(slot2.getOwnerName() == ""); // Player owns the slot

    //std::cout << "TEST1:" <<  slot2.getOwnerName() << std::endl;

    }


    SUBCASE("Player cannot build house on unowned slots") {
        Player player("TestPlayer", 0, boardSlots, slot1);
        Player player2("TestPlayer2", 0, boardSlots, slot1);

  //  std::cout << "TEST2:" << slot2.getOwnerName() << std::endl;

        CHECK(slot1.getIsOwned() == false);   // Slot is still not owned

        // Try building a house on an unowned slot
        bool canBuild = player.buildHouse(slot1);
        CHECK(canBuild == false);              // House should not be built
        CHECK(slot1.getHouses() == 0);         // Slot should still have 0 houses
        CHECK(slot1.getOwnerName() == ""); // Player owns the slot



       //check if player can buy slot of other
        player.buySlot(slot1);
        CHECK(slot1.getIsOwned() == true); 

        bool checkbuy= player2.buySlot(slot1);
       CHECK(checkbuy == false); // Player cant buy
        CHECK(slot1.getOwnerName() == "TestPlayer"); // Player owns the slot

    }

    


    SUBCASE("Player moves to another slot and updates position") {
        Player player("TestPlayer", 0, boardSlots, slot1);

        player.move_slot(3, 2); // Move forward by 3 slots (on a 2-slot board)
        CHECK(player.getPosition() == 1); // New position is 1

    }


}



////



TEST_CASE("Player class functionalities") {
    sf::Color blueColor = sf::Color::Blue;

    Slot slot1(0, "Boardwalk", blueColor, 400, 50, 200, 100, 200);
    Slot slot2(1, "Park Place", blueColor, 350, 35, 150, 80, 160);
    std::vector<Slot> boardSlots = {slot1, slot2}; // Use pointers to slots

    Player player("mimi", 0, boardSlots, slot1);
              //  std::cout << "TEST1ssssssgetMoney:" <<  player.getMoney()  <<  std::endl;

    // Test canBuildHouse
    SUBCASE("canBuildHouse") {
        player.buySlot(slot1); // Assume player buys slot1
        player.buySlot(slot2); // Assume player buys slot2

        //    std::cout << "TEST2sssssssgetMoney:" <<  player.getMoney()  <<  std::endl;

        
        CHECK(player.canBuildHouse(slot1) == true); // Should be able to build on slot1
        CHECK(player.canBuildHouse(slot2) == true); // Should be able to build on slot2
        
        player.buildHouse(slot1);
        CHECK(player.canBuildHouse(slot2) == true); // Should not be able to build more on slot2
    }

    // Test railRoadOwned
    SUBCASE("railRoadOwned") {

        Slot railroad1(2, "Reading Railroad", sf::Color(0xCAE8E0FF), 200, 25, 100, 50, 100);
        Slot railroad2(3, "Pennsylvania Railroad", sf::Color(0xCAE8E0FF), 250, 30, 120, 60, 120);
        player.buySlot(railroad1); // Player buys first railroad
        player.buySlot(railroad2); // Player buys second railroad

        CHECK(railroad1.getOwnerName() == "mimi");
        CHECK(railroad2.getOwnerName() == "mimi");

        CHECK(player.railRoadOwned() == 2); // Player should own 2 railroads

    }

   

    // Test payFine
    SUBCASE("payFine") {
        player.setMoney(1500);
        player.setInJail(true); // Set player in jail
        player.payFine(); // Player attempts to pay fine
        CHECK(player.isInJail() == false); // Player should own 2 railroads

        CHECK(player.getMoney() == 1450); // Check if the fine was deducted correctly
    }




}


TEST_CASE("Hotels") {

        Slot slot1(0, "Boardwalk", sf::Color::Red, 400, 50, 200, 100, 200);
         std::vector<Slot> boardSlots = {slot1};
        Player player("TestPlayer", 0, boardSlots, slot1);

        player.buySlot(slot1);  //1500-400=110

        CHECK(player.getMoney() == 1100);       // Money deducted for house
        CHECK(player.canBuildHouse(slot1)==true);


        CHECK(player.buildHouse(slot1)==true); //1        //1100-200=900
         CHECK(slot1.getHouses() == 1); 
                 CHECK(player.getMoney() == 900);       // Money deducted for house


        CHECK(player.buildHouse(slot1)==true); //2      //900-200=700
        CHECK(player.canBuildHouse(slot1)==true);
        CHECK(slot1.getHouses() == 2); 
        CHECK(player.getMoney() == 700);       // Money deducted for house


        CHECK(player.buildHouse(slot1)==true); //3  //700-200=500
        CHECK(slot1.getHouses() == 3); 
        CHECK(player.getMoney() == 500);       // Money deducted for house


        CHECK(player.buildHouse(slot1)==true);// 4   //500-200=300
        CHECK(slot1.getHouses() == 4); 
        CHECK(player.getMoney() == 300);       // Money deducted for house


        CHECK(player.buildHouse(slot1)==false);// not have money to build hotel
         CHECK(slot1.getHouses() == 4); 
         CHECK(slot1.getHotels() == 0); 

        player.setMoney(1500);
          CHECK(player.buildHouse(slot1)==true);// hotel //4*200+100=900
         CHECK(slot1.getHouses() == 0); 
         CHECK(slot1.getHotels() == 1); 
          CHECK(player.getMoney() == 600);       // Money deducted for house


        CHECK(slot1.getOwnerName() == "TestPlayer"); // Player owns the slot

}



/////////////////////////////////////////////////////

// Test case for Dice class
TEST_CASE("Testing the Dice class") {

    // Create a Dice object
    Dice dice;



    SUBCASE("Rolling the dice") {
        // Roll the dice multiple times to test the random behavior
        for (int i = 0; i < 100; ++i) {
            dice.roll();
            int face = dice.getCurrFace();

            // Check that the face value is always between 1 and 6
            CHECK(face >= 1);
            CHECK(face <= 6);
        }
    }

    SUBCASE("Set and get current face of dice") {
        // Since getCurrFace() relies on roll(), ensure the dice roll changes the face properly
        dice.roll();
        int rolledFace = dice.getCurrFace();
        CHECK(rolledFace >= 1);
        CHECK(rolledFace <= 6);
    }

    
}