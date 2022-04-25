CC              = g++
SRC             = graph.cpp main.cpp user.cpp
TARGET          = project
OBJ             = $(SRC:.c=.o)
DDDEBUG         =
#------------------------------------------------------
$(TARGET): $(OBJ)
	$(CC)  -o $@ $(OBJ) 

$(OBJ): $(SRC)
	$(CC) -g  -c $(SRC) $(DDDEBUG)

clean:
	rm -f *.o *~ $(TARGET)
