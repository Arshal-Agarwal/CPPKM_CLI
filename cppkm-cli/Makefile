# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -Wall -Wextra

# Output binary
TARGET = cppkm

# Source files
SRC = $(wildcard src/*.cpp)

# Object files
OBJ = $(SRC:.cpp=.o)

# Default rule
all: $(TARGET)

# Link object files to build binary
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile .cpp to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(OBJ) $(TARGET)

# PHONY targets
.PHONY: all clean
