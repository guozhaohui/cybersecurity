include ../common.mk

PROGS = digest
.PHONY: all
all: $(PROGS)

SRCS = digest.c

OBJS = $(SRCS:.c=.o)

LDFLAGS += -lssl -lcrypto

digest: $(OBJS)
	$(CC) -o $@ $< $(LDFLAGS)


