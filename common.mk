CC := gcc
CXX := g++
#CFLAGS := -Wall -Wextra -Werror
#CXXFLAGS := -Wall -Wextra -Werror
LDFLAGS := -L/usr/lib -lm

TOPDIR := $(dir $(lastword $(MAKEFILE_LIST)))
BINDIR := $(TOPDIR)/bin

.c.o:
	$(CC) $(CFLAGS) -o $@ -c $<

.cpp.o:
	$(CXX) $(CXXFLAGS) -o $@ -c $<

install: all
	for prog in $(PROGS); \
	do \
		install -D $$prog $(BINDIR)/$$prog; \
	done

clean:
	rm *.o
	rm *.exe

debug: CXXFLAGS += -DDEBUG -g
debug: CFLAGS += -DDEBUG -g
debug: all

