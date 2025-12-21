CC = gcc

CFLAGS = -IC:/raylib/include
LDFLAGS = -LC:/raylib/lib -lraylib -lopengl32 -lgdi32 -lwinmm

SRC = main.c map.c player.c player.h map.h
TARGET = app.exe

all:
	$(CC) $(SRC) -o $(TARGET) $(CFLAGS) $(LDFLAGS)

clean:
	del $(TARGET)
