#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "analglib.h"

#define IS_NULL_VECTOR(a, b)\
	((a->size == 1 && a->coords[0] == 0.0 && b->size != 0) ||\
     (b->size == 1 && b->coords[0] == 0.0 && a->size != 0))

#define VEC_LOCAL_INIT(sz)\
	pvector res = (pvector)malloc(sizeof(vector));\
	res->size = sz;\
	res->coords = calloc(res->size, sizeof(double));\

#define VEC_OP(v1, op, v2){\
	for (size i = 0; i < res->size; ++i)\
		res->coords[i] = v1->coords[i] op## v2->coords[i];\
	return res;\
}

#define VEC_SCALAR_OP(v, op, sc){\
	for (size i = 0; i < res->size; ++i)\
		res->coords[i] = v->coords[i] op## sc;\
	return res;\
}

#define MX_LOCAL_INIT(sz, rows, cols)\
	pmatrix res = (pmatrix)malloc(sizeof(matrix));\
	res->size = sz;\
	res->rowCount = rows;\
	res->colCount = cols;\
	res->cells = (mxdata)malloc(sizeof(vecdata));\
	for (size i = 0; i < res->rowCount; ++i)\
		res->cells[i] = calloc(res->colCount, sizeof(double));\

#define MX_OP(mx1, op, mx2){\
	for (size i = 0; i < res->rowCount; ++i)\
		for (size j = 0; j < res->colCount; ++j)\
			res->cells[i][j] = mx1->cells[i][j] op## mx2->cells[i][j];\
	return res;\
}

#define MX_SCALAR_OP(mx, op, sc){\
	for (size i = 0; i < res->rowCount; ++i)\
		for (size j = 0; j < res->colCount; ++j)\
			res->cells[i][j] = mx->cells[i][j] op## sc;\
	return res;\
}

pvector createVector(vecdata v, size sz){
	if (v == NULL || sz == 0) return NULL;
	VEC_LOCAL_INIT(sz)
	for (size i = 0; i < sz; ++i)
		res->coords[i] = v[i];
	return res;
}

void destroyVector(pvector v){
	if (v == NULL) return;
	free(v->coords);
	free(v);
}

pvector addVector(pvector a, pvector b){
	if (a != NULL && b != NULL && a->size == b->size && a->size != 0) {
		VEC_LOCAL_INIT(a->size)
		VEC_OP(a, +, b)
	}
	else return NULL;
}

pvector subVector(pvector a, pvector b){
	if (a != NULL && b != NULL && a->size == b->size && a->size != 0) {
		VEC_LOCAL_INIT(a->size)
		VEC_OP(a, -, b)
	}
	else return NULL;
}

pvector mulVector(pvector a, double scalar){
	if (a != NULL && a->size != 0) {
		VEC_LOCAL_INIT(a->size)
		VEC_SCALAR_OP(a, *, scalar)
	}
	else return NULL;
}

double dotVectors(pvector a, pvector b){
	if (a != NULL && b != NULL && ((a->size == b->size && a->size != 0) || IS_NULL_VECTOR(a, b))) {
		double scalar = 0.0;
		for (size i = 0; i < a->size; ++i)
			scalar += a->coords[i] * b->coords[i];
		return scalar;
	}
	else return -1.0;
}

pvector crossVectors(pvector a, pvector b){
	if (a != NULL && b != NULL && a->size == 3 && b->size == 3) {
		pvector res = (pvector)malloc(sizeof(vector));
		res->size = 3;	
		res->coords = calloc(res->size, sizeof(double));
		res->coords[0] =  a->coords[1] * b->coords[2] - b->coords[1] * a->coords[2];
		res->coords[1] = -a->coords[0] * b->coords[2] + b->coords[0] * a->coords[2];
		res->coords[2] =  a->coords[0] * b->coords[1] - b->coords[0] * a->coords[1];
		if (res->coords[0] == res->coords[1] && res->coords[1] == res->coords[2]) {
			pvector null_vec = (pvector)malloc(sizeof(vector));
			null_vec->coords = calloc(1, sizeof(double));
			null_vec->coords[0] = 0.0;
			null_vec->size = 1;
			free(res);
			return null_vec;
		}
		return res;
	}
	else return NULL;
}

pmatrix createMatrix(mxdata mx, size rows, size cols){
	if (mx == NULL || rows == 0 || cols == 0) return NULL;
	MX_LOCAL_INIT(cols * rows, rows, cols)
	for (size i = 0; i < rows; ++i) {
		res->cells[i] = calloc(cols, sizeof(double));
		for (size j = 0; j < cols; ++j)
			res->cells[i][j] = mx[i][j];
	}
	return res;
}

void destroyMatrix(pmatrix mx){
	if (mx == NULL) return;
	for (size i = 0; i < mx->rowCount; ++i)
		free(mx->cells[i]);
	free(mx->cells);
	free(mx);
}

pmatrix addMatrix(pmatrix a, pmatrix b){
	if (a != NULL && b != NULL && a->size == b->size && a->size != 0) {
		MX_LOCAL_INIT(a->size, a->rowCount, a->colCount)
		MX_OP(a, +, b)
	}
	else return NULL;
}

pmatrix subMatrix(pmatrix a, pmatrix b){
	if (a != NULL && b != NULL && a->size == b->size && a->size != 0) {
		MX_LOCAL_INIT(a->size, a->rowCount, a->colCount)
		MX_OP(a, -, b)
	}
	else return NULL;
}

pmatrix mulMatrix(pmatrix a, double scalar){
	if (a != NULL && a->size != 0) {
		MX_LOCAL_INIT(a->size, a->rowCount, a->colCount)
		for (size i = 0; i < res->rowCount; ++i)
			for (size j = 0; j < res->colCount; ++i)
				res->cells[i][j] = a->cells[i][j];
		MX_SCALAR_OP(a, *, scalar)
	}
	else return NULL;
}

pmatrix transpose(pmatrix mx){
	if (mx != NULL && mx->rowCount == mx->colCount && mx->size != 0) {
		MX_LOCAL_INIT(mx->size, mx->rowCount, mx->colCount)
		for (size i = 0; i < res->rowCount; ++i)
			for (size j = 0; j < res->colCount; ++j)
				res->cells[j][i] = mx->cells[i][j];
		return res;
	}
	else return NULL;
}

double getDeterminant(pmatrix mx){
	if (mx != NULL && mx->rowCount == mx->colCount && mx->size != 0) {
		MX_LOCAL_INIT(mx->size, mx->rowCount, mx->colCount)
		for (size i = 0; i < res->rowCount; ++i)
			for (size j = 0; j < res->colCount; ++j)
				res->cells[i][j] = mx->cells[i][j];

		if (res->size == 1) return res->cells[0][0];

		double det = 1.0; int swapCount = 0;
		for (size i = 0; i < res->rowCount; ++i) {
			if (res->cells[i][i] == 0.0) {
				for (size j = i + 1; j < res->rowCount; ++j) {
					if (res->cells[j][i] != 0.0) {
						swapLines(res, i, j);
						++swapCount;
					}
				}
			if (res->cells[i][i] == 0.0) return 0.0;
			}

			double divisor = res->cells[i][i];
			for (size j = 0; j < res->colCount; ++j)
				res->cells[i][j] /= divisor;
			det *= divisor;

			for (size j = i + 1; j < res->rowCount; ++j) {
				double mult = res->cells[j][i];
				for (size k = 0; k < res->colCount; ++k)
					res->cells[j][k] -= res->cells[i][k] * mult;
			}
		}
		return det * pow(-1.0, swapCount);
	}
	else return -1.0;
}

bool equal(pmatrix a, pmatrix b){
	if (a == NULL || b == NULL || a->size == 0 || b->size == 0) return false;
	for (size i = 0; i < a->rowCount; ++i)
		for (size j = 0; j < a->colCount; ++j)
			if (a->cells[i][j] != b->cells[i][j]) return false;
	return true;
}

void swapLines(pmatrix mx, int i, int j){
	vecdata tmp = mx->cells[i];
	mx->cells[i] = mx->cells[j];
	mx->cells[j] = tmp;
}