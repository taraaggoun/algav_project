CC 			:= gcc
INCL 		:= -Iinclude
CCFLAGS 	:= -Wall -c
CCO 		:= $(CC) $(CCFLAGS) $(INCL) -c -o
OBJECTS		:= obj/test_uint128.o obj/uint128.o obj/arbre_binaire.o

OBJ		 	:= obj
BIN 		:= bin

TARGETS		:= test_uint128

all: directory $(TARGETS)

directory:
	mkdir -p $(OBJ)
	mkdir -p $(BIN)

$(BIN)/test_uint128: $(OBJECTS)
	$(CC) -o test_uint128 $(OBJECTS)
	
obj/test_uint128.o: test/test_uint128.c
	$(CCO) $@ $<

obj/uint128.o: src/uint128.c
	$(CCO) $@ $<

obj/arbre_binaire.o: src/arbre_binaire.c
	$(CCO) $@ $<

clean:
	rm -rf $(OBJ) $(BIN)