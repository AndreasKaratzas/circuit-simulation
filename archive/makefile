CC              = gcc
DRIVER          = main.c
SRC             = $(shell find src/*.c $(DRIVER))
BUILD_DIR       = build
INC				= lib
TARGET          = project
OBJ             = $(SRC:%=$(BUILD_DIR)/%.o)
DDDEBUG         =
#------------------------------------------------------
$(TARGET): $(OBJ)
	$(CC)  -o $@ $(OBJ) -I $(INC)

$(OBJ): $(SRC)
	$(CC) -g  -c $(SRC) $(DDDEBUG) -I $(INC)

clean:
	rm -f *.o *~ $(TARGET)
