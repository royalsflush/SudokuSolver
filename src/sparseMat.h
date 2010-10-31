#ifndef SPARSE_MAT_H
#define SPARSE_MAT_H

class Elem {
	public:
	int value;
	int posX, posY;
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
	List* lines;
	int maxI, maxJ;
	int currI, currJ;
	bool* currLines, *currCols;

	public:
	SparseMatrix(int maxTI, int maxTJ);
	void insertInPos(int x, int y);
	void print(bool byCols);
};

#endif /* SPARSE_MAT_H */
