CXX = g++
CXXFLAGS = -std=c++17 -Wall -g -I. -Iinc -Iutils
TARGET = main

SRC_DIR = src
LANG = cpp

# If you pass PROBLEM=n, it will only build that file + main.cpp + src/solution.cpp (if available)
ifdef PROBLEM
PROBLEM_SRC = $(SRC_DIR)/$(LANG)/$(PROBLEM).cpp
SOLUTION_SRC = $(SRC_DIR)/$(LANG)/solution.cpp
CXXFLAGS += -DTEST_TO_RUN=$(PROBLEM)
ifeq ($(wildcard $(SOLUTION_SRC)),)
SOURCES = main.cpp $(PROBLEM_SRC)
else
SOURCES = main.cpp $(PROBLEM_SRC) $(SOLUTION_SRC)
endif
else
SOURCES = main.cpp $(wildcard $(SRC_DIR)/*.cpp)
endif

# Default target
all: $(TARGET)

# Build the main executable
$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET).exe

# Run the program
run: 
	./main.exe

# Clean up generated files (Windows)
clean:
	del /f $(TARGET).exe 2>nul || echo Clean completed

# Rebuild everything
rebuild: clean all

# Show help
help:
	@echo "Available targets:"
	@echo "  all        - Build the program (default)"
	@echo "  run        - Build and run the program"
	@echo "  clean      - Remove all generated files"
	@echo "  rebuild    - Clean and build"
	@echo "  help       - Show this help"

.PHONY: all run clean rebuild help