SOURCE = testcurl.cpp
CC = g++ 
CFLAGS = -c -I/usr/include/curl
LIBS = -L/usr/lib/libcurl -lcurl
OBJ = testcurl.o
EXCUTE = testcurl

all: 
	$(CC) $(CFLAGS) $(SOURCE) 
	$(CC) -o $(EXCUTE) $(OBJ) $(LIBS)

clean:
	rm -f $(EXCUTE) *.o