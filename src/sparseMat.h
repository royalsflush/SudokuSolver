#ifndef SPARSE_MAT_H
#define SPARSE_MAT_H

class Elem {
	public:
	int value;
	int i, j;
	Elem* neigh[4];

	// neigh[0] - up
	// neigh[1] - down
	// neigh[2] - left
	// neigh[3] - right

	Elem(int x, int y);
};

class List {
	public:
	Elem* first;
	Elem* last;
	int tam;

	List();
};

class SparseMatrix {
	List* columns;
	List* rows;
	int maxI, maxJ;
	int currI, currJ;
	bool* currRows, *currCols;

	public:
	SparseMatrix(int maxTI, int maxTJ);
	void insertInPos(int di, int dj);
	void printAsList(bool byCols);
	void print(bool byCols);
	
	void dlxRemoveCol(int y);
	void dlxRemoveRow(int x);
	void dlxReaddCol(int y);
	void dlxReaddRow(int x);
};

#endif /* SPARSE_MAT_H */
