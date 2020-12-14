CC = g++ -pthread -g -Wall

all: cc link clean

cc:
	$(CC) -c main.cpp
	$(CC) -c Buffer.cpp
	$(CC) -c Element.cpp
	$(CC) -c BufferMonitor.cpp

link:
	$(CC) -o main Buffer.o Element.o BufferMonitor.o main.o

clean:
	rm *.o

