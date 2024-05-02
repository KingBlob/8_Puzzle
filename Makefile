TARGET_EXEC := main

BUILD_DIR := ./build
SRC_DIR := ./src

SRC := $(shell find $(SRC_DIR) -name '*.cpp')
OBJS := $(SRC:%=$(BUILD_DIR)/%.o)
DEP := $(OBJS:.o=.d)
INC_DIR := $(shell find $(SRC_DIR) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))
CPPFLAGS := $(INC_FLAGS) -MMD -MP

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@


.PHONY: clean
clean:
	rm -r $(BUILD_DIR)

-include $(DEP)