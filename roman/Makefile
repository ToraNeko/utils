CFLAGS := -std=gnu99 \
          -O3
CFLAGS += -D_GNU_SOURCE \
          -D_FILE_OFFSET_BITS=64
CFLAGS += -Wall -Wextra

BIN    := $(notdir $(shell pwd))
SRC    := $(BIN).c
OBJ    := $(patsubst %.c, %.o, $(SRC))

CC     := gcc
CP     := cp -i
RM     := rm -f
STRIP  := strip --strip-all

.PHONY : all clean install purge

all : $(BIN)

$(BIN) : depend $(OBJ)
	$(CC)        $(CFLAGS) -o $@ $(filter-out $<, $^)
	$(STRIP) $@

depend : Makefile $(SRC)
	$(CC) -E -MM $(CFLAGS) $(filter-out $<, $^) > depend

%.o : %.c depend
	$(CC) -c     $(CFLAGS) -o $@ $<

clean :
	-$(RM) *.o depend

purge : clean
	-$(RM) $(BIN)

install : $(BIN)
	$(CP) $(BIN) $(HOME)/bin/

-include depend
