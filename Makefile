CXX = g++ -Wall -Werror
BIN = ../bin

compile: main.o UserFunction.o
	$(CXX) $(BIN)/main.o $(BIN)/UserFunction.o -o $(BIN)/convolution.exe

test: main.o UserFunction.o
	$(CXX) $(BIN)/main.o $(BIN)/UserFunction.o -o $(BIN)/convolution.exe
	$(BIN)/convolution.exe

main.o: main.cpp UserFunction.h
	$(CXX) -c main.cpp -o $(BIN)/main.o

UserFunction.o: UserFunction.cpp UserFunction.h Token.o
	$(CXX) -c UserFunction.cpp $(BIN)/Token.o -o $(BIN)/UserFunction.o

Token.o: Token.cpp Token.h
	$(CXX) -c Token.cpp -o $(BIN)/Token.o

clean:
	rm $(BIN)/convolution.exe
	rm $(BIN)/*.o
