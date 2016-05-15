#ifndef _ANALGLIB_H
	#define _ANALGLIB_H

	#ifdef __cplusplus
	extern "C" {
	#endif
	
	typedef struct {
		double* coords;
		int size;
	} vector;
	
	vector* createVector(double* arr, int n);
	vector* addVector(vector* a, vector* b);
	vector* subVector(vector* a, vector* b);
	vector* mulVector(vector* a, double scalar);
	vector* crossVectors(vector* a, vector*b);
	double  dotVectors(vector* a, vector* b);
	void destroyVector(vector* a);
	int getSize(vector* a);

	typedef struct {
		double** vectors;
		int rowCount, colCount;
		int size;
	} matrix;
	
	matrix* createMatrix(double** arr, int rows, int cols);
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