PROJECT = koi8r
CC = gcc
CFLAGS = -Wall
RM = rm -f
OBJS = gen.o koi8r.o

all: $(PROJECT)

$(PROJECT): $(OBJS)
	$(CC) $^ -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(PROJECT) $(OBJS)
