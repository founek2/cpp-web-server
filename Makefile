CXX=g++
LD=g++
CXXFLAGS=-std=c++14 -g -Wall -pedantic
SRC_DIR = src
FILES_DIR = files
NETWORK_DIR = network
UTILS_DIR = utils
OBJ_DIR = obj
DOC_DIR = doc
TEST_DIR = test
BIN_NAME = skalima7

MKDIR_P = mkdir -p

SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))
OBJECTS_EXCLUDED = $(patsubst $(SRC_DIR)/main.cpp,, $(SOURCES))

SOURCES_FILES = $(wildcard $(SRC_DIR)/$(FILES_DIR)/*.cpp)
OBJECTS_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES_FILES))

SOURCES_NETWORK = $(wildcard $(SRC_DIR)/$(NETWORK_DIR)/*.cpp)
OBJECTS_NETWORK = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES_NETWORK))

SOURCES_UTILS = $(wildcard $(SRC_DIR)/$(UTILS_DIR)/*.cpp)
OBJECTS_UTILS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES_UTILS))

SOURCES_TEST =  $(wildcard $(SRC_DIR)/$(TEST_DIR)/*.cpp)
OBJECTS_TEST =   $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES_TEST))

all: createBuildDirs HttpServer doc

compile: createBuildDirs HttpServer

run:
	./$(BIN_NAME)

HttpServer: $(OBJECTS) $(OBJECTS_FILES) $(OBJECTS_NETWORK) $(OBJECTS_UTILS)
	${LD} -o $(BIN_NAME)  $^

test: $(OBJECTS_TEST)  $(OBJECTS_EXCLUDED) $(OBJECTS_FILES) $(OBJECTS_NETWORK) $(OBJECTS_UTILS)
	$(CXX) $(CXXFLAGS) -o test $^
	./test

$(OBJECTS): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJECTS_FILES): $(OBJ_DIR)/$(FILES_DIR)/%.o : $(SRC_DIR)/$(FILES_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJECTS_NETWORK): $(OBJ_DIR)/$(NETWORK_DIR)/%.o : $(SRC_DIR)/$(NETWORK_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJECTS_UTILS): $(OBJ_DIR)/$(UTILS_DIR)/%.o : $(SRC_DIR)/$(UTILS_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJECTS_TEST): $(OBJ_DIR)/$(TEST_DIR)/%.o : $(SRC_DIR)/$(TEST_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	 rm -rf $(OBJ_DIR) $(DOC_DIR) $(BIN_NAME)

doc:
	doxygen Doxyfile

createBuildDirs:
	$(MKDIR_P) -p $(OBJ_DIR)/$(FILES_DIR) $(OBJ_DIR)/$(NETWORK_DIR) $(OBJ_DIR)/$(UTILS_DIR) $(OBJ_DIR)/$(TEST_DIR)
