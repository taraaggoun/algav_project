CC 			:= gcc
INCL 		:= -Iinclude
CCFLAGS 	:= -Wall -c
CCO 		:= $(CC) $(CCFLAGS) $(INCL) -c $< -o $@
OBJECTS		:= obj/test_uint128.o obj/uint128.o

TARGETS		:= test_uint128
BUILD_DIR 	:= obj

all: directory $(TARGETS)

directory:
	mkdir -p $(BUILD_DIR)

test_uint128: $(OBJECTS)
	$(CC) -o test_uint128 $(OBJECTS)
	
obj/test_uint128.o: test/test_uint128.c
	$(CCO) $@ $<

obj/uint128.o: src/uint128.c
	$(CCO) $@ $<

clean:
	rm -rf $(TARGET) $(BUILD_DIR)