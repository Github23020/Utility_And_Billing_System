# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++11 -Wall -I. -Ih_files -Icpp_files -IUser_Authentication -ITemplate_Classes -MMD -MP

# Directories
BUILD_DIR := build
CPP_DIR := cpp_files
H_DIR := h_files
USER_AUTH_DIR := User_Authentication
TEMPLATE_DIR := Template_Classes

# Source files
MAIN_SRC := main.cpp
TEST_SRC := test.cpp
H_TEST_SRC := h_test.cpp

# Find all .cpp files in cpp_files directory
CPP_SOURCES := $(wildcard $(CPP_DIR)/*.cpp)
# Find common .cpp files in root (if any)
COMMON_SRC := $(filter-out $(MAIN_SRC) $(TEST_SRC) $(H_TEST_SRC), $(wildcard *.cpp))
# Template classes .cpp files
TEMPLATE_SRC := $(wildcard $(TEMPLATE_DIR)/*.cpp)
# User authentication .cpp files
USER_AUTH_SRC := $(wildcard $(USER_AUTH_DIR)/*.cpp)

# Combine all source files
ALL_SRC := $(MAIN_SRC) $(TEST_SRC) $(H_TEST_SRC) $(CPP_SOURCES) $(COMMON_SRC) $(TEMPLATE_SRC) $(USER_AUTH_SRC)

# Object files
MAIN_OBJ := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(MAIN_SRC))
TEST_OBJ := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(TEST_SRC))
H_TEST_OBJ := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(H_TEST_SRC))

# Convert all source files to object files
ALL_OBJ := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(ALL_SRC))

# Remove duplicates
COMMON_OBJ := $(filter-out $(MAIN_OBJ) $(TEST_OBJ) $(H_TEST_OBJ), $(ALL_OBJ))

# Binaries
RUN_BIN := $(BUILD_DIR)/run.out
TEST_BIN := $(BUILD_DIR)/test.out
H_TEST_BIN := $(BUILD_DIR)/h_test.out

# Dependency files
DEPS := $(ALL_OBJ:.o=.d)

# Default target
all: $(RUN_BIN)

# Ensure build dir exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Generic compilation rule for files in root directory
$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	@$(CXX) -c $(CXXFLAGS) -MF $(patsubst %.o,%.d,$@) $< -o $@

# Compilation rule for cpp_files directory
$(BUILD_DIR)/cpp_files/%.o: cpp_files/%.cpp | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	@$(CXX) -c $(CXXFLAGS) -MF $(patsubst %.o,%.d,$@) $< -o $@

# Compilation rule for Template_Classes directory
$(BUILD_DIR)/Template_Classes/%.o: Template_Classes/%.cpp | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	@$(CXX) -c $(CXXFLAGS) -MF $(patsubst %.o,%.d,$@) $< -o $@

# Compilation rule for User_Authentication directory
$(BUILD_DIR)/User_Authentication/%.o: User_Authentication/%.cpp | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	@$(CXX) -c $(CXXFLAGS) -MF $(patsubst %.o,%.d,$@) $< -o $@

# Link targets
$(RUN_BIN): $(MAIN_OBJ) $(COMMON_OBJ)
	$(CXX) $^ -o $@

$(TEST_BIN): $(TEST_OBJ) $(COMMON_OBJ)
	$(CXX) $^ -o $@

$(H_TEST_BIN): $(H_TEST_OBJ) $(COMMON_OBJ)
	$(CXX) $^ -o $@

# Convenience targets
run: $(RUN_BIN)
	./$(RUN_BIN)

test: $(TEST_BIN)
	./$(TEST_BIN)

test_h: $(H_TEST_BIN)
	./$(H_TEST_BIN)

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)

# Include dependency files
-include $(DEPS)

.PHONY: run test test_h clean