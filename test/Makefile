SOURCE = testcurl.cpp
CC = g++ 
#Ubuntu
#CFLAGS = -c -I/usr/include/curl 
#LIBS = -L/usr/lib/libcurl -lcurl
#MAC
CFLAGS = -c -I/usr/local/opt/curl/lib
LIBS = -L/usr/local/opt/curl/lib -lcurl
OBJ = testcurl.o
EXCUTE = testcurl

all: 
	$(CC) $(CFLAGS) $(SOURCE) 
	$(CC) -o $(EXCUTE) $(OBJ) $(LIBS)

clean:
	rm -f $(EXCUTE) *.o