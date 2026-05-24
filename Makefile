TARGET = server

TARGET2 = client

CC = gcc

CFLAGS = -Wall

all: $(TARGET) $(TARGET2)

$(TARGET): server.c
	$(CC) $(CFLAGS) -o $(TARGET) server.c

$(TARGET2): client.c
	$(CC) $(CFLAGS) -o $(TARGET2) client.c

clean:
	rm -f $(TARGET) $(TARGET2)
