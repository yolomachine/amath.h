#ifndef _ANALGLIB_H
	#define _ANALGLIB_H
	
	#ifdef __cplusplus
	extern "C" {
	#else
	#include <stdbool.h>
	#endif

	#define GET_SIZE(a) (a == NULL) ? -1 : a->size

	typedef unsigned int size;
	typedef double* vecdata;
	typedef struct {
		vecdata coords;
		size size;
	} vector, *pvector;
	
	extern pvector createVector(vecdata v, size sz);
	extern pvector addVector(pvector a, pvector b);
	extern pvector subVector(pvector a, pvector b);
	extern pvector mulVector(pvector a, double scalar);
	extern pvector crossVectors(pvector a, pvector b);
	extern double  dotVectors(pvector a, pvector b);
	extern void destroyVector(pvector v);

	typedef double** mxdata;
	typedef struct {
		mxdata cells;
		size rowCount, colCount;
		size size;
	} matrix, *pmatrix;
	
	extern pmatrix createMatrix(mxdata mx, size rows, size cols);
	extern pmatrix addMatrix(pmatrix a, pmatrix b);
	extern pmatrix subMatrix(pmatrix a, pmatrix b);
	extern pmatrix mulMatrix(pmatrix a, double scalar);
	extern pmatrix transpose(pmatrix mx);
	extern bool equal(pmatrix a, pmatrix b);
	extern void swapLines(pmatrix mx, int i, int j);
	extern double getDeterminant(pmatrix mx);
	extern void destroyMatrix(pmatrix mx);

	#ifdef __cplusplus
	}
	#endif
#endif