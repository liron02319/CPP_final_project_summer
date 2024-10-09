# Variables
CXX = g++                 # Compiler
CXXFLAGS = -c -Wall -std=c++11  # Compilation flags
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system  # SFML libraries
TARGET = MonopolyGame         # Output executable name

SRC = Main.cpp Button.cpp Menu.cpp Dice.cpp Slot.cpp Player.cpp Openning.cpp Game.cpp CreateSlot.cpp # Source files
OBJ = $(SRC:.cpp=.o)       # Object files generated from source files

# Object files for core functionalities
CODE_S = Dice.cpp Slot.cpp Player.cpp Button.cpp
CODE_OBJECTS=$(CODE_S:.cpp=.o)  

# Test source files
TEST_SRC = TestCounter.cpp test.cpp  # Test source files
TEST_OBJ = $(TEST_SRC:.cpp=.o)       # Test object files
TEST_TARGET = test                   # Test executable name

# Default target: Build the program
all: $(TARGET)

# Updated target for the test executable
$(TEST_TARGET): $(CODE_OBJECTS) $(TEST_OBJ) 
	$(CXX) $(CODE_OBJECTS) $(TEST_OBJ) -o $(TEST_TARGET) -lstdc++ -lm $(LDFLAGS)

# Rule to create the executable by linking object files
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(LDFLAGS)

# Rule to compile .cpp files into .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

# Clean up object files and the executable
clean:
	rm -f $(OBJ) $(TARGET) $(TEST_OBJ) $(TEST_TARGET) Button.o Chance_handling.o

# Phony targets (targets that aren't actual files)
.PHONY: all clean