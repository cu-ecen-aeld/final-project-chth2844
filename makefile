# the compiler: gcc for C program, define as g++ for C++
ifeq ($(CC),)
	CC = $(CROSS_COMPILE)gcc
endif

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
ifeq ($(CFLAGS),)
	CFLAGS  = -g -Wall -Werror
endif

ifeq ($(LDFLAGS),)
	LDFLAGS = -pthread -lrt
endif

all: fps server

default : all 

fps: fps.c 
	$(CC) $(CFLAGS) -o fps fps.c $(LDFLAGS)

server: server.c 
	$(CC) $(CFLAGS) -o server server.c $(LDFLAGS)

.PHONY: all

clean:
	\rm fps
        \rm server
	$(RM) $(TARGET)
