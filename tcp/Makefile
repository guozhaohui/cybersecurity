include ../common.mk

PROGS = tcp_client tcp_server

tcp_client_SRCS = tcp_client.c
tcp_server_SRCS = tcp_server.c

tcp_client_OBJS = $(tcp_client_SRCS:.c=.o)
tcp_server_OBJS = $(tcp_server_SRCS:.c=.o)

tcp_client: $(tcp_client_OBJS)
	$(CC) -o $@ $< $(LDFLAGS)

tcp_server: $(tcp_server_OBJS)
	$(CC) -o $@ $< $(LDFLAGS)

all: $(PROGS)

.PHONY: all
