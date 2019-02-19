include ../common.mk

PROGS = AES_encryption

SRCS = AES_encryption.c

OBJS = $(SRCS:.c=.o)

LDFLAGS += -lssl -lcrypto

AES_encryption: $(OBJS)
	$(CC) -o $@ $< $(LDFLAGS)

all: $(PROGS)

.PHONY: all
