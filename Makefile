CXX=c++
CXXFLAGS=-std=c++17 -Iinclude

all: test

test: test.cpp lk_pair.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f test

.PHONY: all clean
