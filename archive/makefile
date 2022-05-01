CC              = gcc
DRIVER          = main.c
SRC             = $(shell find src/*.c $(DRIVER))
INC		= lib
TARGET          = project

$(TARGET): $(SRC)
	gcc $(SRC) -I $(INC) -o $@ -lm

clean:
	rm -f *.o *~ $(TARGET)
