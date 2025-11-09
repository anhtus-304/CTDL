## Simplified Makefile for MSYS2 / POSIX make

.PHONY: all run clean

CXX := g++
MKDIR := /usr/bin/mkdir
RM := /usr/bin/rm

CXXFLAGS := -std=c++17 -Wall -I./src -I./src/managers -I./src/menu -I./src/models -I./src/utils

SRC := $(wildcard src/*.cpp src/*/*.cpp src/*/*/*.cpp)
BUILD_DIR := build
TARGET := $(BUILD_DIR)/main.exe

all: $(TARGET)

$(TARGET): $(SRC)
	@$(MKDIR) -p $(BUILD_DIR)
	$(CXX) $(SRC) -o $(TARGET) $(CXXFLAGS) && echo Build successful: $(TARGET)

run: all
	./$(TARGET)

clean:
	$(RM) -f $(TARGET)
