BUILD_DIR = build

# Source files settings
SRC_DIR    = src
SRC_TARGET = $(BUILD_DIR)/chat-client
SRC_FILES  = $(shell find $(SRC_DIR)  -name '*.cpp')
SRC_OBJS   = $(SRC_FILES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/$(SRC_DIR)/%.o)

# Tests files settings
TEST_DIR    = tests
TEST_TARGET = $(BUILD_DIR)/chat-client-test
TEST_SRCS   = $(shell find $(TEST_DIR) -name '*.cpp')
TEST_OBJS   = $(TEST_SRCS:$(TEST_DIR)/%.cpp=$(BUILD_DIR)/$(TEST_DIR)/%.o)

# Compiler settings
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
DBGFLAGS = -g -O0

# Libraries
LDLIBS = -lpthread
GTEST_LIBS = -lgtest -lgtest_main -pthread

# Dependency tracking for header files
DEPS = $(SRC_OBJS:.o=.d) $(TEST_OBJS:.o=.d)
CXXFLAGS += -MMD -MP

.PHONY: all run build debug run_tests build_tests debug_tests clean

all: build build_tests

run: build
	$(SRC_TARGET)

build: $(SRC_OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $(SRC_TARGET) $(LDLIBS)

debug:
	$(MAKE) build CXXFLAGS="$(CXXFLAGS) $(DBGFLAGS)"

run_tests: build_tests
	$(TEST_TARGET)

build_tests: $(SRC_OBJS) $(TEST_OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $(TEST_TARGET) $(LDLIBS) $(GTEST_LIBS)

debug_tests:
	$(MAKE) build_tests CXXFLAGS="$(CXXFLAGS) $(DBGFLAGS)"

# Compile and link source files
$(BUILD_DIR)/$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)/$(SRC_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile and link test files
$(BUILD_DIR)/$(TEST_DIR)/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)/$(TEST_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

# Include generated dependency files
-include $(DEPS)
