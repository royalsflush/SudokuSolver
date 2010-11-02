#include <stdio.h>
#include "sparseMat.h"
using namespace std;

SparseMatrix sm(3, 3);
SparseMatrix m(4, 3);	

void sparseMatConstruction();
void testPrint(char* matName, SparseMatrix* gen);
void dlxRmCol();
void dlxRmRow();
void dlxMixedTest();

int main() {
	setbuf(stdout, NULL);
	dlxMixedTest();

	return 0;
}

void testPrint(const char* matName, SparseMatrix* gen)
{
	printf("Printing %s as lists\n", matName);

	gen->printAsList(false);
	printf("\n");
	gen->printAsList(true);
	printf("\n");

	printf("Printing %s as matrix\n", matName);
	
	gen->print(false);
	printf("\n");
	printf("By columns\n");
	gen->print(true);
	printf("\n");	
}

void dlxMixedTest()
{
	SparseMatrix wiki(6,7);
	
	wiki.insertInPos(0,0);
	wiki.insertInPos(0,3);
	wiki.insertInPos(0,6);
	
	wiki.insertInPos(1,0);
	wiki.insertInPos(1,3);
	
	wiki.insertInPos(2,3);
	wiki.insertInPos(2,4);
	wiki.insertInPos(2,6);

	wiki.insertInPos(3,2);
	wiki.insertInPos(3,4);
	wiki.insertInPos(3,5);
	
	wiki.insertInPos(4,1);
	wiki.insertInPos(4,2);
	wiki.insertInPos(4,5);
	wiki.insertInPos(4,6);

	wiki.insertInPos(5,1);
	wiki.insertInPos(5,6);
	printf("\n");

	wiki.print(false);
	printf("\n");

	wiki.dlxRemoveCol(0);
	wiki.dlxRemoveCol(3);
	wiki.dlxRemoveCol(6);

	wiki.dlxRemoveRow(0);
	wiki.dlxRemoveRow(1);
	wiki.dlxRemoveRow(2);
	wiki.dlxRemoveRow(4);
	wiki.dlxRemoveRow(5);

	wiki.print(false);
	printf("\n");

	wiki.dlxReaddCol(0);
	wiki.dlxReaddCol(3);
	wiki.dlxReaddCol(6);

	wiki.dlxReaddRow(0);
	wiki.dlxReaddRow(1);
	wiki.dlxReaddRow(2);
	wiki.dlxReaddRow(4);
	wiki.dlxReaddRow(5);

	wiki.print(false);
	printf("\n");

	wiki.dlxRemoveCol(0);
	wiki.dlxRemoveCol(3);

	wiki.dlxRemoveRow(0);
	wiki.dlxRemoveRow(1);
	wiki.dlxRemoveRow(2);

	wiki.print(false);
	printf("\n");
	
	wiki.dlxRemoveCol(2);
	wiki.dlxRemoveCol(4);
	wiki.dlxRemoveCol(5);

	wiki.dlxRemoveRow(3);
	wiki.dlxRemoveRow(4);

	wiki.print(false);
	printf("\n");

	wiki.dlxReaddCol(2);
	wiki.dlxReaddCol(4);
	wiki.dlxReaddCol(5);

	wiki.dlxReaddRow(3);
	wiki.dlxReaddRow(4);

	wiki.print(false);
	printf("\n");
}

void dlxRmRow()
{
	printf("Testing DLX row removal\n");
	
	printf("Now removing row 0 from M\n");
	m.dlxRemoveRow(0);

	testPrint("M", &m);

	printf("Now removing row 2 from M\n");
	m.dlxRemoveRow(2);

	testPrint("M", &m);

	printf("Readding row 2 from M\n");
	m.dlxReaddRow(2);

	testPrint("M", &m);

	printf("Readding row 0 from M\n");
	m.dlxReaddRow(0);

	testPrint("M", &m);
}

void dlxRmCol()
{
	printf("Testing DLX column removal\n");
	
	printf("Now removing column 0 from M\n");
	m.dlxRemoveCol(0);

	testPrint("M", &m);

	printf("Now removing column 2 from M\n");
	m.dlxRemoveCol(2);

	testPrint("M", &m);

	printf("Now readding column 2 from M\n");
	m.dlxReaddCol(2);
	
	testPrint("M", &m);
	
	printf("Finally, readding column 0\n");
	m.dlxReaddCol(0);

	testPrint("M", &m);
}

void sparseMatConstruction()
{
	printf("For starters, a square matrix, SM\n");

	sm.insertInPos(1, 2);
	sm.insertInPos(1, 0);
	sm.insertInPos(1, 1);
	sm.insertInPos(0, 2);
	printf("\n");
	
	printf("Now a more generic matrix, M\n");

	m.insertInPos(0,0);
	m.insertInPos(3,2);
	m.insertInPos(1,0);
	m.insertInPos(0,1);
	m.insertInPos(0, 2);
	printf("\n");

	testPrint("SM", &sm);
	printf("\n");
	testPrint("M", &m);
	printf("\n");
}
