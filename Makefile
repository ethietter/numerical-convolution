CXX = g++ -Wall -Werror -std=c++0x
BIN = ../bin
DIR = ~/lib/boost_1_56_0

compile: main.o Token.o UserFunction.o
	$(CXX) -I $(DIR) $(BIN)/main.o $(BIN)/Token.o $(BIN)/UserFunction.o -o $(BIN)/convolution.exe

test: 
	make compile	
	$(BIN)/convolution.exe

main.o: main.cpp
	$(CXX) -I $(DIR) -c main.cpp -o $(BIN)/main.o

UserFunction.o: UserFunction.cpp UserFunction.h
	$(CXX) -I $(DIR) -c UserFunction.cpp -o $(BIN)/UserFunction.o

Token.o: Token.cpp Token.h
	$(CXX) -I $(DIR) -c Token.cpp -o $(BIN)/Token.o

clean:
	rm $(BIN)/convolution.exe
	rm $(BIN)/*.o
