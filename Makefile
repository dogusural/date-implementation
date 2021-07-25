BINARY_FOLDER := build
LIB_DIR := libs

TEST := $(BINARY_FOLDER)/date_tests
SHARED_LIB := $(BINARY_FOLDER)/libddate.so
STATIC_LIB := $(BINARY_FOLDER)/libddate.a

CC := g++
AR := ar

OBJECT_FOLDER := $(BINARY_FOLDER)/objects

SOURCE_DIR := source

TEST_SOURCE_DIR := $(SOURCE_DIR)/test

OUTPUT_LIB_DIR := build


LIBS =

DEFINES =

INCLUDE = \
-I./include


CFLAGS = -Wextra -pedantic -Wall -Werror -fPIC -std=c++17


FLAGS = $(INCLUDE) -L ${LIB_DIR} $(LIBS) $(DEFINES)
SHARED_LIB_FLAGS = -shared
STATIC_LIB_FLAGS = -rcs



$(OBJECT_FOLDER)/%.o: $(SOURCE_DIR)/%.cpp
	@mkdir -p $(OBJECT_FOLDER)
	$(CC) $(FLAGS) $(CFLAGS) -c $< -o $@

$(OBJECT_FOLDER)/%.o: $(TEST_SOURCE_DIR)/%.cpp
	@mkdir -p $(OBJECT_FOLDER)
	$(CC)  $(CFLAGS) -c $< -o $@



TEST_SOURCE_CPP :=  $(shell find $(TEST_SOURCE_DIR) -name '*.cpp')

TEST_SOURCE_OBJECTS :=  $(addprefix $(OBJECT_FOLDER)/,$(notdir $(TEST_SOURCE_CPP:.cpp=.o)))

DATE_SOURCE_CPP :=  $(shell find $(SOURCE_DIR) -maxdepth 1 -name '*.cpp' )

DATE_SOURCE_OBJECTS :=  $(addprefix $(OBJECT_FOLDER)/,$(notdir $(DATE_SOURCE_CPP:.cpp=.o)))



$(TEST): $(TEST_SOURCE_OBJECTS)
	@mkdir -p $(BINARY_FOLDER)
	$(CC) $(FLAGS) $< -L$(OUTPUT_LIB_DIR) -lddate -o $@

$(SHARED_LIB): $(DATE_SOURCE_OBJECTS)
	@mkdir -p $(BINARY_FOLDER)
	$(CC) $(FLAGS) $(SHARED_LIB_FLAGS) $^ -o $@

$(STATIC_LIB): $(DATE_SOURCE_OBJECTS)
	@mkdir -p $(BINARY_FOLDER)
	$(AR) $(STATIC_LIB_FLAGS) $@ $^ 

.PHONY: test lib debug clean

all: lib install test 

test: $(TEST)

lib: $(SHARED_LIB) $(STATIC_LIB)

debug:
	@echo  $(TEST_SOURCE_CPP) "\n\n"$(TEST_SOURCE_OBJECTS) "\n\n"$(DATE_SOURCE_CPP) "\n\n"$(DATE_SOURCE_OBJECTS)

install:
	sudo cp $(SHARED_LIB) /usr/local/lib
	sudo cp $(STATIC_LIB) /usr/local/lib
	sudo cp ./include/Date.h /usr/local/include

clean:
	rm -rf $(BINARY_FOLDER)

