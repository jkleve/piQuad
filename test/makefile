CXX = c++

default: server client

server:
	$(CXX) server.cpp -o server -lboost_system

client:
	$(CXX) client.cpp -o client -lboost_system -pthread

clean:
	rm ./server ./client
