include ../common.mk

PROGS = udp_client udp_server

udp_client_SRCS = udp_client.c
udp_server_SRCS = udp_server.c

udp_client_OBJS = $(udp_client_SRCS:.c=.o)
udp_server_OBJS = $(udp_server_SRCS:.c=.o)

udp_client: $(udp_client_OBJS)
	$(CC) -o $@ $< $(LDFLAGS)

udp_server: $(udp_server_OBJS)
	$(CC) -o $@ $< $(LDFLAGS)

all: $(PROGS)

.PHONY: all
