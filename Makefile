CC = gcc -std=c99
PKGCONFIG = $(shell which pkg-config)
# CFLAGS = $(shell $(PKGCONFIG) --cflags gio-2.0 gtk+-3.0 epoxy)
# LIBS = $(shell $(PKGCONFIG) --libs gio-2.0 gtk+-3.0 epoxy) -lm 
CFLAGS = $(shell $(PKGCONFIG) --cflags gio-2.0 gtk4 epoxy)
LIBS = $(shell $(PKGCONFIG) --libs gio-2.0 gtk4 epoxy) -lm 

SRC = main.c
BIN = glarea

ALL = $(SRC)
OBJS = $(ALL:.c=.o)

all: $(BIN)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $(@F) $<

$(BIN): $(OBJS)
	$(CC) -o $(@F) $(OBJS) $(LIBS)

clean:
	@rm -f $(OBJS) $(BIN)
