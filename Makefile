SOURCE = readdata.cpp
CC = g++ 
CFLAGS =
#ubuntu
#LIBS = -L/usr/include/curl/lib -lcurl
#mac
LIBS = -L/usr/local/opt/curl/lib -lcurl 
OBJ = readdata

all: 
	$(CC) $(CFLAGS) $(SOURCE) $(LIBS) -o $(OBJ)

clean:
	rm -f $(OBJ)