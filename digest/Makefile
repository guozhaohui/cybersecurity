include ../common.mk

PROGS = digest

SRCS = digest.c

OBJS = $(SRCS:.c=.o)

LDFLAGS += -lssl -lcrypto

digest: $(OBJS)
	$(CC) -o $@ $< $(LDFLAGS)

all: $(PROGS)

.PHONY: all
