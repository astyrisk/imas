CC = gcc
CFLAGS = -Wall -Wextra -std=c99 
LDFLAGS =

SOURCES = main.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = imas

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -lm -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
