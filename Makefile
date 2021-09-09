rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

LD = g++
LFLAGS = -Wall

INCLUDES = main.cpp $(ALL_CPP_FILES)

ALL_CPP_FILES := $(call rwildcard,src/,*.cpp)

EXECUTABLE = c

all:
	$(LD) $(LFLAGS) -g -o $(EXECUTABLE) $(INCLUDES) -lpqxx -lpq

clean:
	rm -rf *.o $(EXECUTABLE)
