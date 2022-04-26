CC              = g++
SRC             = src/utils.cpp src/graph.cpp main.cpp
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
