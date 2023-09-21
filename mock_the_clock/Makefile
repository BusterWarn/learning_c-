# Compiler options
ifeq ($(CXX), clang++)
	CXX=clang++
else
	CXX=g++
endif

# Catch path and build path (yeah it's not pretty but it works)
CATCH_PATH=../functional_programming_using_cpp/lib
CATCH_BUILD_PATH=../functional_programming_using_cpp/build

CXXFLAGS=-std=c++20 -Wall -isystem$(CATCH_PATH)

# Output directory
OUT_DIR=out

# Catch library
CATCH_OBJ=$(CATCH_BUILD_PATH)/catch2.o

# Source and object files
SRC=$(wildcard *.cpp)
OBJ=$(addprefix $(OUT_DIR)/,$(SRC:.cpp=.o))

# Executables
MAIN=$(OUT_DIR)/main
TEST=$(OUT_DIR)/tests

# Detect OS for mkdir
ifeq ($(OS),Windows_NT)
	MKDIR=if not exist $(OUT_DIR) mkdir $(OUT_DIR)
else
	MKDIR=mkdir -p $(OUT_DIR)
endif

# Default build rule
all: dirs $(MAIN)

dirs:
	$(MKDIR)

# Rule to build the main executable
$(MAIN): $(OUT_DIR)/main.o $(OUT_DIR)/bear.o
	$(CXX) $^ -o $@

# Rule to build the test executable
$(TEST): $(OUT_DIR)/tests.o $(OUT_DIR)/bear.o $(CATCH_OBJ)
	$(CXX) $^ -o $@

# Rule to build catch object file
$(CATCH_OBJ): $(CATCH_PATH)/catch_amalgamated.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Pattern rule for building object files
$(OUT_DIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Build and run tests
test: dirs $(TEST)
	./$(TEST)

# Cleanup
clean:
ifeq ($(OS),Windows_NT)
	rmdir /S /Q $(OUT_DIR)
else
	rm -rf $(OUT_DIR)
endif
