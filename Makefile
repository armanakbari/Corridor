CC := g++
CFLAGS := -lpthread

all: server client

server: server.cpp serverh.cpp
	$(CC) -std=c++11 -o server server.cpp serverh.cpp $(CFLAGS) -I. 

client: 
	$(CC) -std=c++11 -o client client.cpp $(CFLAGS) -I.

clean:
	rm -f server client