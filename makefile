CC              = g++
DRIVER          = main.cpp
SRC             = $(shell find src/*.cpp $(DRIVER))
INC             = lib
TARGET          = project

$(TARGET): $(SRC)
        gcc $(SRC) -I $(INC) -o $@

clean:
	rm -f *.o *~ $(TARGET)
