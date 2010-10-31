#include <stdio.h>
#include "sparseMat.h"
using namespace std;

int main() {
	setbuf(stdout, NULL);

	SparseMatrix sm(3, 3);
	sm.insertInPos(1, 2);
	sm.insertInPos(1, 0);
	sm.insertInPos(1, 1);

	sm.insertInPos(0, 2);

	sm.print(false);
	printf("\n");
	sm.print(true);

	SparseMatrix m(4, 3);	
	m.insertInPos(0,0);
	m.insertInPos(3,2);
	m.insertInPos(1,0);
	m.insertInPos(0,1);
	m.insertInPos(0, 2);

	m.print(true);
	printf("\n");
	m.print(false);

	return 0;
}
