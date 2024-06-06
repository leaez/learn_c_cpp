
#
#
#
# pip3 install matplotlib
CXX := g++
PYBIND11_INCLUDE := $(shell python3 -m pybind11 --includes)
PYTHON3_INCLUDE := $(shell python3-config --includes)
PYTHON3_LIBS := $(shell python3-config --ldflags)

CXXFLAGS := -O3 -Wall -std=c++11 $(PYBIND11_INCLUDE) $(PYTHON3_INCLUDE)
LDFLAGS := $(PYTHON3_LIBS)

TARGET := main

SRC := pybind_plot.cpp
#SRC := cppp_callpy.cpp
OBJ = $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX)  $(OBJ) -o $(TARGET) $(LDFLAGS)

.cpp.o: 
	$(CXX)  -c $(CXXFLAGS) -o $*.o $<

$(TARGET).o: $(OBJ)


clean:
	rm -f *.o $(TARGET)
