#include <stdio.h>
#include <stdlib.h>
#include "sparseMat.h"

#define up neigh[0]
#define down neigh[1]
#define left neigh[2]
#define right neigh[3]


//Element functions

Elem::Elem(int di, int dj)
{
	this->i = di;
	this->j = dj;
	this->value = 1;

	for (int it=0; it<4; it++)
		neigh[it] = NULL; 
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

	this->rows = new List[maxTI];
	this->currRows = new bool[maxTJ];
	this->maxI = this->currI = maxTI;

	for (int i=0; i<this->maxI; i++)
		currRows[i]=true;
}

void SparseMatrix::insertInPos(int di, int dj)
{
	Elem* it = rows[di].first;
	Elem* nElem = new Elem(di,dj);	

	#ifdef _DBG
		printf("Inserting element into position: %d, %d\n", di, dj);
	#endif

	if (!it) {
		rows[di].first = nElem;
		rows[di].last = nElem;
		nElem->right = nElem;
		nElem->left = nElem;
	}
	else {
		while (it->j < dj && it!=rows[di].last) 
			it=it->right;
		
		if (it==rows[di].last && it->j < dj) {
			nElem->right = rows[di].first;
			nElem->left = rows[di].last;
			rows[di].first->left = nElem;
			rows[di].last->right = nElem;

			rows[di].last = nElem;
		}
		else {
			Elem* prev = it->left;
			nElem->left = prev;
			nElem->right = it;
			it->left = nElem;
			prev->right = nElem;

			if (it==rows[di].first) rows[di].first=nElem;
		}
	}

	this->rows[di].tam++;
	
	//Inserting into columns
	it = columns[dj].first;

	if (!it) {
		columns[dj].first = nElem;
		columns[dj].last = nElem;
		nElem->up = nElem;
		nElem->down = nElem;
	}
	else {
		while (it->i < di && it!=columns[dj].last) 
			it=it->down;
		
		if (it==columns[dj].last && it->i < di) {
			nElem->down = columns[dj].first;
			nElem->up = columns[dj].last;
			columns[dj].first->up = nElem;
			columns[dj].last->down = nElem;

			columns[dj].last = nElem;
		}
		else {
			Elem* prev = it->up;
			nElem->up = prev;
			nElem->down = it;
			it->up = nElem;
			prev->down = nElem;

			if (it==columns[dj].first) columns[dj].first=nElem;
		}
	}

	this->columns[dj].tam++;
}



void SparseMatrix::print(bool byCols)
{
	Elem* it = NULL;

	if (byCols) {
		for (int j=0; j<this->maxJ; j++) {
			if (!this->currCols[j]) 
				continue;
			
			it=this->columns[j].first;

			for (int i=0; i<this->maxI; i++) {
				if (!this->currRows[i])
					continue;				

				if (!it) { 
					printf("0 "); 
					continue; 
				}
				
				if (i != it->i) printf("0 ");
				else {
					printf("%d ", it->value);
					it=it->down;
				}
			}

			printf("\n");
		}

		return;
	}

	for (int i=0; i<this->maxI; i++) {
		if (!this->currRows[i]) 
			continue;

		it=this->rows[i].first;

		for (int j=0; j<this->maxJ; j++) {
			if (!this->currCols[j])
				continue;				
			
			if (!it) { 
				printf("0 "); 
				continue; 
			}

			if (j != it->j) printf("0 ");
			else {
				printf("%d ", it->value);
				it=it->right;
			}
		}

		printf("\n");
	}
}

void SparseMatrix::printAsList(bool byCols)
{
	Elem* it = NULL;

	if (byCols) {
		for (int j=0; j<this->maxJ; j++) {
			if (!this->currCols[j]) continue;

			printf("Column %d (size: %d): ", j, this->columns[j].tam);
			
			it = this->columns[j].first;			
			if (!it) { 
				printf("\n"); 
				continue;
			}

			do {
				printf("%d ", it->i);
				it = it->down;
			} while (it!= this->columns[j].first);
			
			printf(": first is %d, last is %d\n", this->columns[j].first->i, 
				this->columns[j].last->i);
			
			printf("\n");
		}
		return;
	}

	for (int i=0; i<this->maxI; i++) {
		if (!this->currRows[i]) continue;

		printf("Row %d (size: %d): ", i, this->rows[i].tam);
		
		it = this->rows[i].first;			
		if (!it) {
			printf("\n");	
			continue;
		}

		do {
			printf("%d ", it->j);
			it = it->right;
		} while (it!= this->rows[i].first);
		
		printf(": first is %d, last is %d\n", this->rows[i].first->j, 
			this->rows[i].last->j);

		printf("\n");
	}
}

//DLX functions

void SparseMatrix::dlxRemoveCol(int y) 
{
	if (!this->currCols[y]) return;

	this->currCols[y]=false;
	this->currJ--;

	Elem* it = this->columns[y].first;
	Elem* prev = NULL, *next = NULL;
	if (!it) return;

	do {
		prev = it->left;
		next = it->right;

		prev->right = next;
		next->left = prev;
		
		if (rows[it->i].tam==1) {
			rows[it->i].first = NULL;
			rows[it->i].last = NULL;
		}

		if (it==rows[it->i].first) rows[it->i].first = next;
		if (it==rows[it->i].last) rows[it->i].last = prev;

		rows[it->i].tam--;

		it=it->down;
	} while (it!=this->columns[y].first);
}

void SparseMatrix::dlxRemoveRow(int x) 
{
	if (!this->currRows[x]) return;

	this->currRows[x]=false;
	this->currI--;

	Elem* it = this->rows[x].first;
	Elem* prev = NULL, *next = NULL;
	if (!it) return;

	do {
		prev = it->up;
		next = it->down;

		prev->down = next;
		next->up = prev;
		
		if (columns[it->j].tam==1) {
			columns[it->j].first = NULL;
			columns[it->j].last = NULL;
		}

		if (it==columns[it->j].first) columns[it->j].first = next;
		if (it==columns[it->j].last) columns[it->j].last = prev;

		columns[it->j].tam--;

		it=it->right;
	} while (it!=this->rows[x].first);
}

void SparseMatrix::dlxReaddCol(int y)
{
	if (this->currCols[y]) return;

	this->currCols[y]=true;
	this->currJ++;

	Elem* it = this->columns[y].first;
	Elem* prev = NULL, *next = NULL;
	if (!it) return;

	do {
		prev = it->left;
		next = it->right;

		prev->right = it;
		next->left = it;

		if (rows[it->i].tam==0) {
			rows[it->i].first = it;
			rows[it->i].last = it;
		}
		else {
			if (it->j < rows[it->i].first->j) rows[it->i].first = it;
			if (it->j > rows[it->i].last->j) rows[it->i].last = it;
		}

		rows[it->i].tam++;

		it=it->down;
	} while (it!=this->columns[y].first);
}

void SparseMatrix::dlxReaddRow(int x)
{
	if (this->currRows[x]) return;

	this->currRows[x]=true;
	this->currI++;

	Elem* it = this->rows[x].first;
	Elem* prev = NULL, *next = NULL;
	if (!it) return;

	do {
		prev = it->up;
		next = it->down;

		prev->down = it;
		next->up = it;

		if (columns[it->j].tam==0) {
			columns[it->j].first = it;
			columns[it->j].last = it;
		}
		else {
			if (it->i < columns[it->j].first->i) columns[it->j].first = it;
			if (it->i > columns[it->j].last->i) columns[it->j].last = it;
		}

		columns[it->j].tam++;

		it=it->right;
	} while (it!=this->rows[x].first);
}
