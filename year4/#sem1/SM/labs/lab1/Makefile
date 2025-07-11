CXX = g++
CXXFLAGS = -Wall -g -fopenmp
TARGET = lab1

$(TARGET): lab1.o
	$(CXX) $(CXXFLAGS) -o $(TARGET) lab1.o

lab1.o: lab1.cpp
	$(CXX) $(CXXFLAGS) -c lab1.cpp

clean:
	rm -f *.o $(TARGET)
