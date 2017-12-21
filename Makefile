
CXX=g++
CFLAGS=-pedantic -Wextra -Wall
CXXFLAGS=$(CFLAGS) -std=c++11

AR=ar

SRC_DIR=./
OBJ_DIR=./

INC=-I ./ -I ./libs/include/genetic-algo
INC+=$(shell pkg-config --cflags opencv) $(shell pkg-config --cflags libavcodec)


LIBS=-L/usr/lib/arm-linux-gnueabihf $(shell pkg-config --libs opencv) $(shell pkg-config --libs libavcodec) $(shell pkg-config --libs libavformat)
LIBS+=$(shell pkg-config --libs libavutil) $(shell pkg-config --libs libswscale) $(shell pkg-config --libs libavresample)
LIBS+=-L./libs/ -lgenetic-algo

CXXFLAGS+=$(INC)

SRC=$(shell find . -name "*.cpp")

OBJ=$(patsubst $(SRC_DIR)%.cpp,$(OBJ_DIR)%.o,$(SRC))

EXECUTABLE=CamReader

release: all

all: CFLAGS+=-O2
all: $(EXECUTABLE)

debug: CFLAGS+=-O0 -g
debug: $(EXECUTABLE)

%.cpp%.o:
	$(CXX) -c -o $@ $< $(CXXFLAGS)

# Make the executable named EXECUTABLE using CC
$(EXECUTABLE): $(OBJ)
	$(CXX) -o $@ $(CXXFLAGS) $(OBJ) $(INC) $(LIBS)

# Generate the static library
# TODO: Get this working.
$(LIBRARY): $(OBJ)
	$(AR) rcs $@ $(OBJ)

clean:
	rm -rf $(OBJ)
	rm -f $(EXECUTABLE)
	rm -f $(LIBRARY)
