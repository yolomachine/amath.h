#ifndef _MATHLIB_H
	#define _MATHLIB_H

	#include <stdbool.h>

	#ifdef MATH_DLL
	#ifdef MATH_DLL_BUILD
	#define MATH_FUNC __declspec(dllexport)
	#else
	#define MATH_FUNC __declspec(dllimport)
	#endif
	#else
	#define MATH_FUNC extern
	#endif


	typedef unsigned int uint;
	typedef double* vecdata;
	typedef struct {
		vecdata coords;
		uint size;
	} vector, *pvector;

	MATH_FUNC pvector createVector(vecdata v, uint sz);
	MATH_FUNC pvector addVector(pvector a, pvector b);
	MATH_FUNC pvector subVector(pvector a, pvector b);
	MATH_FUNC pvector mulVector(pvector a, double scalar);
	MATH_FUNC pvector crossVectors(pvector a, pvector b);
	MATH_FUNC double  dotVectors(pvector a, pvector b);
	MATH_FUNC void destroyVector(pvector v, pvector* pv);
	MATH_FUNC int getVecSize(pvector v);
	MATH_FUNC vecdata getVecData(pvector v);

	typedef double** mxdata;
	typedef struct {
		mxdata cells;
		uint rowCount, colCount;
		uint size;
	} matrix, *pmatrix;

	MATH_FUNC pmatrix createMatrix(mxdata mx, uint rows, uint cols);
	MATH_FUNC pmatrix addMatrix(pmatrix a, pmatrix b);
	MATH_FUNC pmatrix subMatrix(pmatrix a, pmatrix b);
	MATH_FUNC pmatrix mulMatrix(pmatrix a, double scalar);
	MATH_FUNC pmatrix transpose(pmatrix mx);
	MATH_FUNC bool equal(pmatrix a, pmatrix b);
	MATH_FUNC void swapLines(pmatrix mx, int i, int j);
	MATH_FUNC double getDeterminant(pmatrix mx);
	MATH_FUNC void destroyMatrix(pmatrix mx, pmatrix* pmx);
	MATH_FUNC int getMxSize(pmatrix mx);
	MATH_FUNC mxdata getMxData(pmatrix mx);

	#undef MATH_FUNC
#endif