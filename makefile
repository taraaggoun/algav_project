CC 			:= gcc
CCFLAGS 	:= -Wall -c -pedantic
INCL 		:= -Iinclude
CCO 		:= $(CC) $(CCFLAGS) $(INCL) -o

OBJ		 	:= obj
BIN 		:= bin

TARGETS		:= $(BIN)/test_uint128 $(BIN)/test_mhtree 
# $(BIN)/test_tprioritetab

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

# $(BIN)/test_tprioritetab: $(OBJ)/test_tprioritetab.o $(OBJ)/tprioritetab.o $(OBJ)/utils.o  $(OBJ)/uint128.o
# 	$(CC) -o $@ $^

#--------------------------------------#

$(OBJ)/test_uint128.o: test/test_uint128.c
	$(CCO) $@ $<

$(OBJ)/test_mhtree.o: test/test_mhtree.c
	$(CCO) $@ $<

# $(OBJ)/test_tprioritetab.o: test/test_tprioritetab.c
# 	$(CCO) $@ $<

$(OBJ)/test_utils.o: test/test_utils.c
	$(CCO) $@ $<


$(OBJ)/uint128.o: src/uint128.c
	$(CCO) $@ $<

$(OBJ)/mhtree.o: src/mhtree.c
	$(CCO) $@ $<

# $(OBJ)/tprioritetab.o: src/tprioritetab.c
# 	$(CCO) $@ $<

# $(OBJ)/utils.o: src/utils.c
# 	$(CCO) $@ $<

#--------------------------------------#

clean:
	rm -rf $(OBJ) $(BIN)