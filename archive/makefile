CC              = gcc
DRIVER          = main.c
SRC             = $(shell find src/*.cpp $(DRIVER))
INC				= lib
TARGET          = project
OBJ             = $(SRC:.c=.o)
DDDEBUG         =
#------------------------------------------------------
$(TARGET): $(OBJ)
	$(CC)  -o $@ $(OBJ) -I $(INC)

$(OBJ): $(SRC)
	$(CC) -g  -c $(SRC) $(DDDEBUG) -I $(INC)

clean:
	rm -f *.o *~ $(TARGET)
