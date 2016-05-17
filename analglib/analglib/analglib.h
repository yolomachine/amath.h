#ifndef _ANALGLIB_H
	#define _ANALGLIB_H

	#ifdef __cplusplus
	extern "C" {
	#endif

	typedef unsigned int size;
	typedef double* vecdata;
	typedef struct {
		vecdata coords;
		size size;
	} vector;
	typedef vector* pvector;
	
	vector* createVector(vecdata v, size sz);
	vector* addVector(vector* a, vector* b);
	vector* subVector(vector* a, vector* b);
	vector* mulVector(vector* a, double scalar);
	vector* crossVectors(vector* a, vector*b);
	double  dotVectors(vector* a, vector* b);
	void destroyVector(vector* a);

	typedef double** mxdata;
	typedef struct {
		mxdata cells;
		size rowCount, colCount;
		size size;
	} matrix;
	typedef matrix* pmatrix;
	
	matrix* createMatrix(mxdata mx, size rows, size cols);
	matrix* addMatrix(matrix* a, matrix* b);
	matrix* subMatrix(matrix* a, matrix* b);
	matrix* mulMatrix(matrix* a, double scalar);
	matrix* transpose(matrix* a);
	int getDeterminant(matrix* a);

	#ifdef __cplusplus
	}
	#endif
#endif

#ifndef _CRT_SECURE_NO_WARNINGS
	#define _CRT_SECURE_NO_WARNINGS
#endif