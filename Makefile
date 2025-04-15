BUILD_DIR = build

SRC_DIR    = src
SRC_TARGET = $(BUILD_DIR)/chat_client
SRC_FILES  = $(shell find $(SRC_DIR)  -name '*.cpp')
SRC_OBJS   = $(SRC_FILES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/$(SRC_DIR)/%.o)

TEST_DIR    = tests
TEST_TARGET = $(BUILD_DIR)/chat-client-test
TEST_SRCS   = $(shell find $(TEST_DIR) -name '*.cpp')
TEST_OBJS   = $(TEST_SRCS:$(TEST_DIR)/%.cpp=$(BUILD_DIR)/$(TEST_DIR)/%.o)

CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
DBGFLAGS = -g -O0

LDLIBS = -lpthread
GTEST_LIBS = -lgtest -lgtest_main -pthread

.PHONY: all build debug clean build_tests

all: build build_tests

info:
	@echo $(SRC_FILES)

build: $(SRC_OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $(SRC_TARGET) $(LDLIBS)

debug:
	$(MAKE) build CXXFLAGS="$(CXXFLAGS) $(DBGFLAGS)"

build_tests: $(SRC_OBJS) $(TEST_OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $(TEST_TARGET) $(LDLIBS) $(GTEST_LIBS)

debug_tests:
	$(MAKE) build_tests CXXFLAGS="$(CXXFLAGS) $(DBGFLAGS)"

$(BUILD_DIR)/$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)/$(SRC_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/$(TEST_DIR)/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)/$(TEST_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)
