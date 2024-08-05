CC = gcc
CFLAGS = -Wall -Wextra -std=c11

SRCS = test_map.c map.c

all: test_map

%.o: %.c
    $(CC) $(CFLAGS) -c $<

clean:
    rm -f $(OBJS) test_map

