CXX = c++

default: all

all: server client

server:
	$(CXX) server.cpp -o server -lboost_system -lboost_thread

client:
	$(CXX) client.cpp -o client -lboost_system -pthread

clean:
	rm ./server ./client
