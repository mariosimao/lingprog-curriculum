rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

LD = g++
LFLAGS = -Wall -std=c++11

INCLUDES = $(ALL_CPP_FILES)

ALL_CPP_FILES := $(call rwildcard,src/,*.cpp)

SERVER_EXECUTABLE = server

all:
	$(LD) $(LFLAGS) -o $(SERVER_EXECUTABLE) server.cpp $(INCLUDES) -lpqxx -lpq -lboost_date_time -pthread -lboost_system -lcrypto -lssl -lcpprest

clean:
	rm -rf *.o $(CLI_EXECUTABLE) $(SERVER_EXECUTABLE)
