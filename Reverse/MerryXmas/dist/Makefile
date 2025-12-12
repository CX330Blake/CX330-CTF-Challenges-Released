CC = gcc
TARGET = chal

all: $(TARGET)

$(TARGET): chal.c
	$(CC) $(CFLAGS) -o $(TARGET) chal.c
	strip $(TARGET)

clean:
	rm -f $(TARGET)

