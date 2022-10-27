run: SparseMatrix.o
	g++ *.o main.cpp -o run

SparseMatrix.o: SparseMatrix.cpp SparseMatrix.hpp Node.hpp
	g++ -c SparseMatrix.cpp

clean:
	del *.o
	del *.exe
