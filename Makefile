# Compiler
CC = g++

# Compiler flags
CFLAGS = -g -std=gnu++11

# Directories
SRC_DIR = src
GUI_GLUT_DIR = gui_glut
BIB_DIR = bib
BUILD_DIR = build

# Libraries
LIBS = -lGL -lGLU -lglut -l3ds -lSDL2_image -lIL -lSDL_image -lpthread

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(GUI_GLUT_DIR)/*.cpp) $(wildcard $(BIB_DIR)/*.cpp) main.cpp

# Object files
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Header files
INCLUDES = -I$(SRC_DIR) -I$(GUI_GLUT_DIR) -I$(BIB_DIR)

# Main executable
MAIN = main

.PHONY: all clean

# All target
all: build run

# Default target
build: $(BUILD_DIR)/$(MAIN)

# Clean target
clean:
	rm -f $(BUILD_DIR)/*.o $(BUILD_DIR)/$(MAIN)

# Compile object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/%.o: $(GUI_GLUT_DIR)/%.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/%.o: $(BIB_DIR)/%.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Link object files into executable
$(BUILD_DIR)/$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $^ $(LIBS) -o $@

run: build/main
	./build/main