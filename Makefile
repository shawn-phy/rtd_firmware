CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

all: rtd_example

rtd_example: rtd_example.cpp rtd.cpp
	$(CXX) $(CXXFLAGS) -o rtd_example rtd_example.cpp rtd.cpp

clean:
	rm -f rtd_example
