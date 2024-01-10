CURR_DIR := .
BUILD_DIR := $(CURR_DIR)/build
MODEL_DIR := $(CURR_DIR)/model
VIEW_DIR := $(CURR_DIR)/view
# CTR_DIR := $(CURR_DIR)/controller

RM := rm -f
MK := mkdir -p

EXEC := maze
TEST_EXEC := test
ARCHIVE := $(CURR_DIR)/$(EXEC)

# CLANG := clang-format -n

all: install run

install:
	@$(MK) $(BUILD_DIR)
	@cmake -G"MinGW Makefiles" $(CURR_DIR) -B $(BUILD_DIR)
	@cd $(BUILD_DIR) ; $(MAKE) ; cd ..

run:
	@cd $(BUILD_DIR)
	./leak

clean:
	$(RM) -r $(BUILD_DIR)