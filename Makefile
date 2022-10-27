run: SparseMatrix.o
	g++ *.o main.cpp -o run

SparseMatrix.o: SparseMatrix.cpp SparseMatrix.h Node.h
	g++ -c SparseMatrix.cpp

clean:
	del *.o
	del *.exe
