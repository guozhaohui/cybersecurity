include ../common.mk

PROGS = ssl_client ssl_server
.PHONY: all
all: $(PROGS)

ssl_client_SRCS = ssl_client.c
ssl_server_SRCS = ssl_server.c

ssl_client_OBJS = $(ssl_client_SRCS:.c=.o)
ssl_server_OBJS = $(ssl_server_SRCS:.c=.o)

LDFLAGS += -lssl -lcrypto

ssl_client: $(ssl_client_OBJS)
	$(CC) -o $@ $< $(LDFLAGS)

ssl_server: $(ssl_server_OBJS)
	$(CC) -o $@ $< $(LDFLAGS)


