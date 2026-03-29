CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -lpthread

TARGET = corrida
SRC = CorridaDeThreads.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)