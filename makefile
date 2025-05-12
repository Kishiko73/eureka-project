## made in reference to https://www.youtube.com/watch?v=DtGrdB8wQ_8 ##

BINARY=bin

CODE_DIR=src
INCLUDE_DIRS=include
BUILD_DIR=build
CODE_DIRS=$(shell find $(CODE_DIR) -type d)
BUILD_DIRS=$(addprefix $(BUILD_DIR)/,$(CODE_DIRS))

CC=g++
## Lang <c/cpp> ##
LANG=cpp

LIB_FLAGS=-MP -MD -Wall -Wextra
debug ?= 0
ifeq (${debug},1)
	LIB_FLAGS += -g -DDEBUG
else
	LIB_FLAGS += -s
endif

CFLAGS=$(addprefix -I,$(INCLUDE_DIRS)) $(addprefix -I,$(CODE_DIRS)) $(LIB_FLAGS)

## Locate all source (.$LANG) files under CODE_DIRS ##
SOURCES=$(foreach D,$(CODE_DIRS),$(wildcard $(D)/*.$(LANG)))
## Make Targets ##
ASSEMBLY     =$(SOURCES:%.$(LANG)=$(BUILD_DIR)/%.s)
PREPROCCESSES=$(SOURCES:%.$(LANG)=$(BUILD_DIR)/%.i)
OBJECTS      =$(SOURCES:%.$(LANG)=$(BUILD_DIR)/%.o)
DEPENDS      =$(SOURCES:%.$(LANG)=$(BUILD_DIR)/%.d)

.PHONY: run all preproccess assembly clean



run: $(BINARY)
	./$(BINARY)


all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CC) $(LIB_FLAGS) -o $@ $^
	@echo
	@echo Build complete, size: $$(stat -c%s $(BINARY)) bytes
	@echo

$(OBJECTS) $(DEPENDS): | $(BUILD_DIRS)

$(BUILD_DIRS):
	mkdir -p $(BUILD_DIRS)

$(BUILD_DIR)/%.o: %.$(LANG)
	$(CC) $(CFLAGS) -c -o $@ $<


preproccess: $(PREPROCCESSES)

$(BUILD_DIR)/%.i: %.$(LANG)
	$(CC) $(CFLAGS) -E -o $@ $<


assembly: $(ASSEMBLY)

$(BUILD_DIR)/%.s: %.$(LANG)
	$(CC) $(CFLAGS) -S -o $@ $<


clean:
	rm -rf $(BINARY) $(BUILD_DIR) cache


-include $(DEPENDS)
