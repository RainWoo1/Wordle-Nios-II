CC=gcc

CFLAGS=-Wall

EXECUTABLE=wordle

all: $(EXECUTABLE)

$(EXECUTABLE): main.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(EXECUTABLE)