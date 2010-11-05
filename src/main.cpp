#include <stdio.h>
#include <list>

#include "sparseMat.h"
using namespace std;

#define N_SETS 6
#define U_SIZE 7

void buildMat();
void runX();
void xStep();

bool finish;
SparseMatrix sm(N_SETS, U_SIZE);

int main() {
	buildMat();
	runX();
	return 0;
}

void buildMat() {
	sm.insertInPos(0,0);
	sm.insertInPos(0,3);
	sm.insertInPos(0,6);

	sm.insertInPos(1,0);
	sm.insertInPos(1,3);

	sm.insertInPos(2,3);
	sm.insertInPos(2,4);
	sm.insertInPos(2,6);

	sm.insertInPos(3,2);
	sm.insertInPos(3,4);
	sm.insertInPos(3,5);

	sm.insertInPos(4,1);
	sm.insertInPos(4,2);
	sm.insertInPos(4,5);
	sm.insertInPos(4,6);

	sm.insertInPos(5,1);
	sm.insertInPos(5,6);

	sm.print(false);
}

void runX() {
	finish=false;
	int col, minNumElem = N_SETS+1;	
	int numElem;

	for (int i=0; i<U_SIZE; i++) {
		numElem = sm.columns[i].tam;

		if (minNumElem > numElem) {
			minNumElem = numElem;
			col = i;
		}
	}

	printf("Chosen column: %d\n", col);
}

void xStep() {

}
