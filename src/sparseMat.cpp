#include <stdio.h>
#include <stdlib.h>
#include "sparseMat.h"

#define up neigh[0]
#define down neigh[1]
#define left neigh[2]
#define right neigh[3]


//Element functions

Elem::Elem(int x, int y)
{
	this->posX = x;
	this->posY = y;
	this->value = 1;

	for (int i=0; i<4; i++)
		neigh[i] = NULL; 
}

//List functions

List::List()
{
	this->first = NULL;
	this->last = NULL;
	this->tam = 0;
}

//Sparse Matrix functions

SparseMatrix::SparseMatrix(int maxTI, int maxTJ)
{
	this->columns = new List[maxTJ];
	this->currCols = new bool[maxTJ];
	this->maxJ = this->currJ = maxTJ;

	for (int i=0; i<this->maxJ; i++)
		currCols[i]=true;

	this->lines = new List[maxTI];
	this->currLines = new bool[maxTJ];
	this->maxI = this->currI = maxTI;

	for (int i=0; i<this->maxI; i++)
		currLines[i]=true;
}

void SparseMatrix::insertInPos(int x, int y)
{
	Elem* it = lines[x].first;
	Elem* nElem = new Elem(x,y);	

	#ifdef _DBG
		printf("Inserting element into position %d, %d\n", x, y);
	#endif

	if (!it) {
		lines[x].first = nElem;
		lines[x].last = nElem;
		nElem->right = nElem;
		nElem->left = nElem;
	}
	else {
		while (it->posY < y && it!=lines[x].last) 
			it=it->right;
		
		if (it==lines[x].last && it->posY < y) {
			nElem->right = lines[x].first;
			nElem->left = lines[x].last;
			lines[x].first->left = nElem;
			lines[x].last->right = nElem;

			lines[x].last = nElem;
		}
		else {
			Elem* prev = it->left;
			nElem->left = prev;
			nElem->right = it;
			it->left = nElem;
			prev->right = nElem;

			if (it==lines[x].first) lines[x].first=nElem;
		}
	}

	this->lines[x].tam++;
	
	//Inserting into columns
	it = columns[y].first;

	if (!it) {
		columns[y].first = nElem;
		columns[y].last = nElem;
		nElem->up = nElem;
		nElem->down = nElem;
	}
	else {
		while (it->posX < x && it!=columns[y].last) 
			it=it->down;
		
		if (it==columns[y].last && it->posX < x) {
			nElem->down = columns[y].first;
			nElem->up = columns[y].last;
			columns[y].first->up = nElem;
			columns[y].last->down = nElem;

			columns[y].last = nElem;
		}
		else {
			Elem* prev = it->up;
			nElem->up = prev;
			nElem->down = it;
			it->up = nElem;
			prev->down = nElem;

			if (it==columns[y].first) columns[y].first=nElem;
		}
	}

	this->columns[y].tam++;
}

void SparseMatrix::print(bool byCols)
{
	Elem* it = NULL;
	int lastY;

	if (byCols) {
		for (int j=0; j<this->currJ; j++) {
			it=this->columns[j].first;

			for (int i=0; i<this->currI; i++) {
				if (!it) { 
					printf("0 "); 
					continue; 
				}
				
				if (i != it->posX) printf("0 ");
				else {
					printf("%d ", it->value);
					it=it->down;
				}
			}

			printf("\n");
		}

		return;
	}

	for (int i=0; i<this->currI; i++) {
		it=this->lines[i].first;

		for (int j=0; j<this->currJ; j++) {
			if (!it) { 
				printf("0 "); 
				continue; 
			}

			if (j != it->posY) printf("0 ");
			else {
				printf("%d ", it->value);
				it=it->right;
			}
		}

		printf("\n");
	}
}
