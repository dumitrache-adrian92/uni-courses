# Variables
CXX = g++
MPIXX = mpic++
CXXFLAGS = -g -Wall -Wextra -std=c++17 -O3
LIBS = -lpthread -fopenmp
SRC_DIR = src
BIN_DIR = bin
TESTS_DIR = tests
SCRIPTS_DIR = scripts
TESTS_SCRIPT = $(SCRIPTS_DIR)/generate_test_suite.py

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
EXES = $(SRCS:$(SRC_DIR)/%.cpp=$(BIN_DIR)/%)

all: $(EXES)

$(BIN_DIR)/mpi_hybrid_prim: $(SRC_DIR)/mpi_hybrid_prim.cpp | $(BIN_DIR)
	$(MPIXX) $(CXXFLAGS) -o $@ $< $(LIBS)

$(BIN_DIR)/mpi_prim: $(SRC_DIR)/mpi_prim.cpp | $(BIN_DIR)
	$(MPIXX) $(CXXFLAGS) -o $@ $<

$(BIN_DIR)/%: $(SRC_DIR)/%.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $< $(LIBS)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(TESTS_DIR): $(TESTS_SCRIPT)
	mkdir -p $(TESTS_DIR)
	python3 $(TESTS_SCRIPT) $(TESTS_DIR)

clean:
	rm -rf $(BIN_DIR) $(TESTS_DIR)

.PHONY: all clean
