## made in reference to https://www.youtube.com/watch?v=DtGrdB8wQ_8 ##

BINARY=bin

CODE_DIR=src
INCLUDE_DIRS=include
BUILD_DIR=build
CODE_DIRS=$(shell find $(CODE_DIR) -type d)
BUILD_DIRS=$(addprefix $(BUILD_DIR)/,$(CODE_DIRS))
#BUILD_DIRS=$(foreach D,$(CODE_DIRS),$(BUILD_DIR)/$(D))

CC=g++
## Lang <c/cpp> ##
LANG=cpp
## Optimization flag ##
OPT=-O0
## Magic flags that tell make about dependecies ##
DEP_FLAGS=-MP -MD
LIB_FLAGS=-Wall -Wextra
CFLAGS=-g $(foreach D,$(INCLUDE_DIRS),-I$(D)) $(foreach D,$(CODE_DIRS),-I$(D)) $(OPT) $(DEP_FLAGS) $(LIB_FLAGS)

## Locate all source (.$LANG) files under CODE_DIRS ##
CFILES=$(foreach D,$(CODE_DIRS),$(wildcard $(D)/*.$(LANG)))
ASSEMBLY=$(CFILES:%.$(LANG)=$(BUILD_DIR)/%.s)
PREPROCCESSES=$(CFILES:%.$(LANG)=$(BUILD_DIR)/%.i)
OBJECTS=$(CFILES:%.$(LANG)=$(BUILD_DIR)/%.o)
DEPENDS=$(CFILES:%.$(LANG)=$(BUILD_DIR)/%.d)

.PHONY: run all preproccess assembly clean



run: $(BINARY)
	./$(BINARY)


all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CC) $(LIB_FLAGS) -o $@ $^
	@echo
	@echo Build complete, size: $$(stat -c%s $(BINARY)) bytes
	@echo

$(OBJECTS): | $(BUILD_DIRS)

$(BUILD_DIR)/%:
	mkdir -p $@

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


-include $(DEPFILES)
