INC=api
CC=g++
CFLAGS= -C -Wall -I $(INC)
LINKER= -pthread -lpthread
SRC_DIRS= ./
SRCS= $(shell find $(SRC_DIRS) -name '*.cpp' -or -name '*.c')
BUILD_DIR= ./generated
OBJS= $(SRCS:%=$(BUILD_DIR)/%.o)

all: Demo

Demo: $(OBJS)
	mkdir -p Output
	$(CC) $(OBJS) $(LINKER) -o Output/Demo

$(BUILD_DIR)/%.cpp.o : %.cpp
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.c.o : %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf generated

clean_all: clean
	rm -rf Output