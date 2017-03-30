SOURCE = readdata.cpp
CC = g++ 
CFLAGS =
LIBS = -L/usr/include/curl/lib -lcurl
OBJ = readdata

all: 
	$(CC) $(CFLAGS) $(SOURCE) $(LIBS) -o $(OBJ)

clean:
	rm -f $(OBJ)