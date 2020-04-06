CXX = g++ -std=c++11
CXXFLAGS = -g -Wall
all: PA3
PA3: main.o cancer.o
	$(CXX) main.cpp -o PArun
main.o: main.cpp AVLTemplate.h Cancer.h
	$(CXX) $(CXXFLAGS) -c main.cpp #
cancer.o: Cancer.cpp Cancer.h
	$(CXX) $(CXXFLAGS) -c Cancer.cpp
clean: 
	rm -rf *o PArun
run:
	@./PArun
    

