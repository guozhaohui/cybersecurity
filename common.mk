CC := gcc
CXX := g++
#CFLAGS := -Wall -Wextra -Werror
#CXXFLAGS := -Wall -Wextra -Werror
LDFLAGS := -L/usr/lib -lm

.c.o:
	$(CC) $(CFLAGS) -o $@ -c $<

.cpp.o:
	$(CXX) $(CXXFLAGS) -o $@ -c $<

debug: CXXFLAGS += -DDEBUG -g
debug: CFLAGS += -DDEBUG -g
debug: all

clean:
	rm *.o
	rm *.exe
