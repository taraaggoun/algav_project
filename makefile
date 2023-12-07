CC 			:= gcc
CCFLAGS 	:= -Wall -Wextra -c -pedantic
INCL 		:= -Iinclude
CCO 		:= $(CC) $(CCFLAGS) $(INCL) -o

OBJ		 	:= obj
BIN 		:= bin

TARGETS		:= $(BIN)/test_uint128 $(BIN)/test_mhtree $(BIN)/test_td $(BIN)/test_mharray $(BIN)/test_bst $(BIN)/test_md5
#$(BIN)/test_binomh

#--------------------------------------#

all: directory $(TARGETS)

directory:
	mkdir -p $(OBJ)
	mkdir -p $(BIN)

#--------------------------------------#

$(BIN)/test_uint128: $(OBJ)/test_uint128.o $(OBJ)/uint128.o $(OBJ)/test_utils.o
	$(CC) -o $@ $^

$(BIN)/test_mhtree: $(OBJ)/test_mhtree.o $(OBJ)/mhtree.o  $(OBJ)/uint128.o $(OBJ)/test_utils.o
	$(CC) -o $@ $^ -lm

$(BIN)/test_td: $(OBJ)/test_td.o $(OBJ)/tab_dynamique.o $(OBJ)/uint128.o $(OBJ)/test_utils.o
	$(CC) -o $@ $^

$(BIN)/test_mharray: $(OBJ)/test_mharray.o $(OBJ)/mharray.o $(OBJ)/tab_dynamique.o $(OBJ)/uint128.o $(OBJ)/test_utils.o
	$(CC) -o $@ $^

$(BIN)/test_binomh: $(OBJ)/test_binomh.o $(OBJ)/binomial_heap.o  $(OBJ)/uint128.o $(OBJ)/test_utils.o
	$(CC) -o $@ $^

$(BIN)/test_bst: $(OBJ)/test_bst.o $(OBJ)/binary_search_tree.o $(OBJ)/uint128.o $(OBJ)/test_utils.o 
	$(CC) -o $@ $^

$(BIN)/test_md5: $(OBJ)/test_md5.o $(OBJ)/md5.o $(OBJ)/uint128.o $(OBJ)/test_utils.o
	$(CC) -o $@ $^ -lm

#--------------------------------------#

$(OBJ)/test_utils.o: test/test_utils.c
	$(CCO) $@ $<

$(OBJ)/test_uint128.o: test/test_uint128.c
	$(CCO) $@ $<

$(OBJ)/test_mhtree.o: test/test_mhtree.c
	$(CCO) $@ $<

$(OBJ)/test_td.o: test/test_td.c
	$(CCO) $@ $<

$(OBJ)/test_mharray.o: test/test_mharray.c
	$(CCO) $@ $<

$(OBJ)/test_binomh.o: test/test_binomh.c
	$(CCO) $@ $<

$(OBJ)/test_bst.o: test/test_bst.c
	$(CCO) $@ $<

$(OBJ)/test_md5.o: test/test_MD5.c
	$(CCO) $@ $<


$(OBJ)/uint128.o: src/uint128.c
	$(CCO) $@ $<

$(OBJ)/mhtree.o: src/min_heap_tree.c
	$(CCO) $@ $<

$(OBJ)/tab_dynamique.o: src/tab_dynamique.c
	$(CCO) $@ $<

$(OBJ)/mharray.o: src/min_heap_array.c
	$(CCO) $@ $<

$(OBJ)/binomial_heap.o: src/binomial_heap.c
	$(CCO) $@ $<

$(OBJ)/binary_search_tree.o: src/binary_search_tree.c
	$(CCO) $@ $<

$(OBJ)/md5.o: src/MD5.c
	$(CCO) $@ $<

#--------------------------------------#

clean:
	rm -rf $(OBJ) $(BIN)