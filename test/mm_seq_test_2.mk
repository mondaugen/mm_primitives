BASE = $(HOME)/Documents/development
SRCS = $(BASE)/mm_primitives/test/mm_seq_test_2.c $(BASE)/mm_primitives/src/mm_seq.c $(BASE)/mm_primitives/src/mm_event.c
INC  = $(BASE)/mm_primitives/inc $(BASE)/ne_datastructures/inc
CC = clang
BIN = mm_seq_test_2.elf
CFLAGS = $(addprefix -I,$(INC)) -g3

$(BIN) : $(SRCS)
	$(CC) $(CFLAGS) $^ -o $@
