CXX = g++ -Wall -Werror

test: main.o UserFunction.o
	$(CXX) main.o UserFunction.o -o convolution.exe
	convolution.exe

main.o: main.cpp UserFunction.h
	$(CXX) -c main.cpp -o main.o

UserFunction.o: UserFunction.cpp UserFunction.h
	$(CXX) -c UserFunction.cpp -o UserFunction.o

clean:
	rm convolution.exe
	rm *.o
