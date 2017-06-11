all:client server

CPPFLAGS+=-std=c++03 -Wall -pedantic
CPPFLAGS+=-g -O0
CPPFLAGS+=-isystem ~/custom/boost/

LDFLAGS+=-L /home/nanugu/Downloads/boost_1_64_0/stage/lib
LDFLAGS+=-lboost_system -lrt -lpthread -lboost_thread


%:%.cpp
	g++ $(CPPFLAGS) $^ -o $@ $(LDFLAGS) -I /home/nanugu/Downloads/boost_1_64_0/
