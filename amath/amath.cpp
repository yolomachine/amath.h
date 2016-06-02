#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "amath.h"

bool isNull(pvector a, pvector b) {
	return ((a->size == 1 && a->coords[0] == 0.0 && b->size != 0) ||
		    (b->size == 1 && b->coords[0] == 0.0 && a->size != 0)) ? true : false;
}

pmatrix mxInit(uint size, uint rows, uint cols){
	pmatrix mx = (pmatrix)malloc(sizeof(matrix)); 
	mx->size = size; 
	mx->rowCount = rows; 
	mx->colCount = cols; 
	mx->cells = (mxdata)malloc(sizeof(vecdata)); 
	for (uint i = 0; i < mx->rowCount; ++i)
		mx->cells[i] = (vecdata)calloc(mx->colCount, sizeof(double));
	return mx;
}

pmatrix mxInitMx(pmatrix m){
	pmatrix mx = (pmatrix)malloc(sizeof(matrix));
	mx->size = m->size;
	mx->rowCount = m->rowCount;
	mx->colCount = m->colCount;
	mx->cells = (mxdata)malloc(sizeof(vecdata));
	for (uint i = 0; i < mx->rowCount; ++i)
		mx->cells[i] = (vecdata)calloc(mx->colCount, sizeof(double));
	return mx;
}

pvector vecInit(uint size){
	pvector v = (pvector)malloc(sizeof(vector));
	v->size = size;
	v->coords = (vecdata)calloc(v->size, sizeof(double));
	return v;
}

pvector vecInitVec(pvector vec){
	pvector v = (pvector)malloc(sizeof(vector));
	v->size = vec->size;
	v->coords = (vecdata)calloc(vec->size, sizeof(double));
	return v;
}

double add(double a, double b){
	return a + b;
}

double sub(double a, double b){
	return a - b;
}

pvector vectorOperation(pvector a, pvector b, double(*op)(double, double)){
	pvector res = vecInitVec(a);
	for (uint i = 0; i < res->size; ++i)
		res->coords[i] = op(a->coords[i], b->coords[i]);
	return res;
}

pmatrix matrixOperation(pmatrix a, pmatrix b, double(*op)(double, double)){
	pmatrix res = mxInitMx(a);
	for (uint i = 0; i < res->rowCount; ++i)
		for (uint j = 0; j < res->colCount; ++j)
			res->cells[i][j] = op(a->cells[i][j], b->cells[i][j]);
	return res;
}

pvector createVector(vecdata v, uint sz){
	if (v == NULL || sz == 0) return NULL;
	pvector res = vecInit(sz);
		for (uint i = 0; i < sz; ++i)
			res->coords[i] = v[i];
	return res;
}

void destroyVector(pvector v, pvector* pv){
	if (v == NULL) return;
	free(v->coords);
	free(v);
	*pv = NULL;
}

pvector addVector(pvector a, pvector b){
	if (a == NULL || b == NULL || a->size != b->size || a->size == 0 || b->size == 0)
		return NULL;
	return vectorOperation(a, b, *(add));
}

pvector subVector(pvector a, pvector b){
	if (a == NULL || b == NULL || a->size != b->size || a->size == 0 || b->size == 0)
		return NULL;
	return vectorOperation(a, b, *(sub));
}

pvector mulVector(pvector a, double scalar){
	if (a == NULL || a->size == 0) return NULL;
	pvector res = vecInitVec(a);
	for (uint i = 0; i < res->size; ++i)
		res->coords[i] = a->coords[i] * scalar; 
	return res;
}

double dotVectors(pvector a, pvector b){
	if (a != NULL && b != NULL && ((a->size == b->size && a->size != 0) || isNull(a, b))) {
		double scalar = 0.0;
		for (uint i = 0; i < a->size; ++i)
			scalar += a->coords[i] * b->coords[i];
		return scalar;
	}
	else return -1.0;
}

pvector crossVectors(pvector a, pvector b){
	if (a == NULL || b == NULL || a->size != 3 || b->size != 3) return NULL;
	pvector res = (pvector)malloc(sizeof(vector));
	res->size = 3;
	res->coords = (vecdata)calloc(res->size, sizeof(double));
	res->coords[0] = a->coords[1] * b->coords[2] - b->coords[1] * a->coords[2];
	res->coords[1] = -a->coords[0] * b->coords[2] + b->coords[0] * a->coords[2];
	res->coords[2] = a->coords[0] * b->coords[1] - b->coords[0] * a->coords[1];
	if (res->coords[0] == res->coords[1] && res->coords[1] == res->coords[2]) {
		pvector null_vec = (pvector)malloc(sizeof(vector));
		null_vec->coords = (vecdata)calloc(1, sizeof(double));
		null_vec->coords[0] = 0.0;
		null_vec->size = 1;
		free(res);
		return null_vec;
	}
	return res;
}

pmatrix createMatrix(mxdata mx, uint rows, uint cols){
	if (mx == NULL || rows == 0 || cols == 0) return NULL;
	pmatrix res = mxInit(cols * rows, rows, cols);
	for (uint i = 0; i < rows; ++i) {
		res->cells[i] = (vecdata)calloc(cols, sizeof(double));
		for (uint j = 0; j < cols; ++j)
			res->cells[i][j] = mx[i][j];
	}
	return res;
}

void destroyMatrix(pmatrix mx, pmatrix* pmx){
	if (mx == NULL) return;
	for (uint i = 0; i < mx->rowCount; ++i)
		free(mx->cells[i]);
	free(mx->cells);
	free(mx);
	*pmx = NULL;
}

pmatrix addMatrix(pmatrix a, pmatrix b){
	if (a == NULL || b == NULL || a->size != b->size || a->size == 0 || b->size == 0)
		return NULL;
	return matrixOperation(a, b, *(add));
}

pmatrix subMatrix(pmatrix a, pmatrix b){
	if (a == NULL || b == NULL || a->size != b->size || a->size == 0 || b->size == 0)
		return NULL;
	return matrixOperation(a, b, *(sub));
}

pmatrix mulMatrix(pmatrix a, double scalar){
	if (a == NULL || a->size == 0) return NULL;
	pmatrix res = mxInitMx(a);
		for (uint i = 0; i < res->rowCount; ++i)
			for (uint j = 0; j < res->colCount; ++j)
				res->cells[i][j] = a->cells[i][j] * scalar;
	return res;
}

pmatrix transpose(pmatrix mx){
	if (mx == NULL || mx->rowCount != mx->colCount || mx->size == 0) return NULL;
	pmatrix res = mxInitMx(mx);
		for (uint i = 0; i < res->rowCount; ++i)
			for (uint j = 0; j < res->colCount; ++j)
				res->cells[j][i] = mx->cells[i][j];
	return res;
}

double getDeterminant(pmatrix mx){
	if (mx == NULL || mx->rowCount != mx->colCount || mx->size == 0) return NULL;
	pmatrix res = mxInitMx(mx);
		for (uint i = 0; i < res->rowCount; ++i)
			for (uint j = 0; j < res->colCount; ++j)
				res->cells[i][j] = mx->cells[i][j];

	if (res->size == 1) return res->cells[0][0];

	double det = 1.0; int swapCount = 0;
	for (uint i = 0; i < res->rowCount; ++i) {
		if (res->cells[i][i] == 0.0) {
			for (uint j = i + 1; j < res->rowCount; ++j) {
				if (res->cells[j][i] != 0.0) {
					swapLines(res, i, j);
					++swapCount;
				}
			}
			if (res->cells[i][i] == 0.0) return 0.0;
		}

		double divisor = res->cells[i][i];
		for (uint j = 0; j < res->colCount; ++j)
			res->cells[i][j] /= divisor;
		det *= divisor;

		for (uint j = i + 1; j < res->rowCount; ++j) {
			double mult = res->cells[j][i];
			for (uint k = 0; k < res->colCount; ++k)
				res->cells[j][k] -= res->cells[i][k] * mult;
		}
	}
	return det * pow(-1.0, swapCount);
}

bool equal(pmatrix a, pmatrix b){
	if (a == NULL || b == NULL || a->size == 0 || b->size == 0) return false;
	for (uint i = 0; i < a->rowCount; ++i)
		for (uint j = 0; j < a->colCount; ++j)
			if (a->cells[i][j] != b->cells[i][j]) return false;
	return true;
}

void swapLines(pmatrix mx, int i, int j){
	vecdata tmp = mx->cells[i];
	mx->cells[i] = mx->cells[j];
	mx->cells[j] = tmp;
}

vecdata getVecData(pvector v){
	return v->coords;
}

mxdata getMxData(pmatrix mx){
	return mx->cells;
}

int getVecSize(pvector v){
	return v->size;
}

int getMxSize(pmatrix mx){
	return mx->size;
}