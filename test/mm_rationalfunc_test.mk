BASE = $(HOME)/Documents/development
SRCS = $(BASE)/mm_primitives/test/mm_rationalfunc_test.c
INC  = $(BASE)/mm_primitives/inc 
CC = clang
BIN = mm_rationalfunc_test.elf
CFLAGS = $(addprefix -I,$(INC)) -g3

$(BIN) : $(SRCS)
	$(CC) $(CFLAGS) $^ -o $@
