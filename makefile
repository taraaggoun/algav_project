CC 			:= gcc
CCFLAGS 	:= -Wall -c
INCL 		:= -Iinclude
CCO 		:= $(CC) $(CCFLAGS) $(INCL) -o

OBJ		 	:= obj
BIN 		:= bin

TARGETS		:= $(BIN)/test_uint128 $(BIN)/test_bt $(BIN)/test_mhtree

#--------------------------------------#

all: directory $(TARGETS)

directory:
	mkdir -p $(OBJ)
	mkdir -p $(BIN)

#--------------------------------------#

$(BIN)/test_uint128: $(OBJ)/test_uint128.o $(OBJ)/uint128.o
	$(CC) -o $@ $^

$(BIN)/test_bt: $(OBJ)/test_bt.o $(OBJ)/binary_tree.o $(OBJ)/uint128.o
	$(CC) -o $@ $^

$(BIN)/test_mhtree: $(OBJ)/test_mhtree.o $(OBJ)/binary_tree.o $(OBJ)/uint128.o
	$(CC) -o $@ $^

#--------------------------------------#

$(OBJ)/test_uint128.o: test/test_uint128.c
	$(CCO) $@ $<

$(OBJ)/test_bt.o: test/test_bt.c
	$(CCO) $@ $<

$(OBJ)/test_mhtree.o: test/test_mhtree.c
	$(CCO) $@ $<

$(OBJ)/uint128.o: src/uint128.c
	$(CCO) $@ $<

$(OBJ)/binary_tree.o: src/binary_tree.c
	$(CCO) $@ $<

$(OBJ)/min_heap_tree.o: src/min_heap_tree.c
	$(CCO) $@ $<

#--------------------------------------#

clean:
	rm -rf $(OBJ) $(BIN)