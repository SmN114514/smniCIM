CC = gcc
CFLAGS = -Wall -Iinclude
LIBS = -lncurses

# 添加 setColor.o
OBJS = src/main.o src/command.o src/setColor.o

smnicim: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<