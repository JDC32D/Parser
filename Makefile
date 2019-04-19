CXX_FLAGS = -O3 -Wall -Werror -pedantic -g -std=c++11
LINK =
BIN = frontEnd
BUILD_DIR = bin
SRCS = $(wildcard *.cpp)
OBJ = $(SRCS:%.cpp=$(BUILD_DIR)/%.o)
DEP = $(OBJ:%.o=%.d)
$(BIN) : $(BUILD_DIR)/$(BIN)
$(BUILD_DIR)/$(BIN) : $(OBJ)
	@mkdir -p $(@D)
	@printf "\e[0;31mDone~\e[0m\n"
	@$(CXX) $(CXX_FLAGS) $(LINK) $^ -o $@
	@mv $(BUILD_DIR)/$(BIN) .
-include $(DEP)
$(BUILD_DIR)/%.o : %.cpp
	@mkdir -p $(@D)
	@#printf "$(CXX) $(CXX_FLAGS) %-17s -o %-s\n" $< $@
	@#printf "\x1b[32;01m $(CXX) $(CXX_FLAGS) %-s \x1b[0m\n" $<
	@printf "\e[0;32m$(CXX) %-s \e[m\n" $<
	@$(CXX) $(CXX_FLAGS) -MMD -c $< -o $@
.PHONY : clean
clean :
	@printf "\e[0;31m"
	@rm -r -v -f $(BIN) $(OBJ) $(DEP) $(BUILD_DIR)
	@printf "\e[m"
	@rm -r -v -f log.txt

brun: $(BIN)
	@optirun ./$(BIN)
run:
	@optirun ./$(BIN)
