INC = -I$(HOME)/Documents/development/ne_tester/inc \
    -I$(HOME)/Documents/development/mm_primitives/inc
CC = clang
CFLAGS = -g3
BIN = mm_dllist_test.elf
SRC = mm_dllist_test.c

$(BIN): $(SRC)
	$(CC) $(CFLAGS) $^ $(INC) -o $@ 

clean:
	rm $(BIN)
    
