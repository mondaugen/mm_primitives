# requires ne_datastructures library
# assumes it is contained in the parent directory
NEDATASTRUCTURES_PATH = ../ne_datastructures
NEDATASTRUCTURES_INC_PATH = $(NEDATASTRUCTURES_PATH)/inc

MMPRIMITIVES_SRCS_PATH = src
MMPRIMITIVES_SRCS      = $(wildcard $(MMPRIMITIVES_SRCS_PATH)/*.c)
MMPRIMITIVES_INC_PATH  = inc
MMPRIMITIVES_OBJS      = $(MMPRIMITIVES_SRCS:$(MMPRIMITIVES_SRCS_PATH)/%.c=objs/%.o)
# this also includes the dependencies of external libraries and unfortunately
# rebuilds everything when only one item has changed.
MMPRIMITIVES_DEP       = $(wildcard $(MMPRIMITIVES_INC_PATH)/*.h)
MMPRIMITIVES_DEP      += $(wildcard $(NEDATASTRUCTURES_INC_PATH)/*.h)
MMPRIMITIVES_CFLAGS	= -Ofast

INC		= $(NEDATASTRUCTURES_INC_PATH) $(MMPRIMITIVES_INC_PATH)
CFLAGS	= $(foreach inc,$(INC),-I$(inc))

CFLAGS += -ggdb3 -gdwarf-4 -Wall -ffunction-sections -fdata-sections
CFLAGS += -dD
CFLAGS += -Wno-unused-function

ARFLAGS   = rcs

OBJSDIR = objs

LIBDIR  = lib

CC = gcc
AR = ar

BIN = $(LIBDIR)/libmm_primitives.a


all: $(LIBDIR) $(OBJSDIR) $(BIN) 

$(LIBDIR):
	if [ ! -d "$(LIBDIR)" ]; then mkdir $(LIBDIR); fi

$(OBJSDIR):
	if [ ! -d "$(OBJSDIR)" ]; then mkdir $(OBJSDIR); fi

# compile mmdsp 
$(MMPRIMITIVES_OBJS): $(OBJSDIR)/%.o: $(MMPRIMITIVES_SRCS_PATH)/%.c $(MMPRIMITIVES_DEP)
	$(CC) -c $(CFLAGS) $< -o $@ $(MMPRIMITIVES_CFLAGS)

$(BIN): $(MMPRIMITIVES_OBJS)
	$(AR) $(ARFLAGS) $@ $^

clean:
	rm -r $(LIBDIR) $(OBJSDIR)
