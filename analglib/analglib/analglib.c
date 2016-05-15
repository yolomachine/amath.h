#include "analglib.h"
#include <stdio.h>
#include <stdlib.h>

#define VEC_OP(v1, op, v2){\
	vector* res = (vector*)malloc(sizeof(vector));\
	res->coords = v1->coords;\
	res->size = v1->size;\
	for (int i = 0; i < res->size; ++i)\
		res->coords[i] op##= v2->coords[i];\
	return res;\
}

#define VEC_SCALAR_OP(v, op, sc){\
	vector* res = (vector*)malloc(sizeof(vector));\
	res->size = v->size;\
	res->coords = v->coords;\
	for (int i = 0; i < res->size; ++i)\
		res->coords[i] op##= scalar;\
	return res;\
}

vector* createVector(double* arr, int n){
	if (arr == NULL || n <= 0) return NULL;
	vector* a = (vector*)malloc(sizeof(vector));
	double* tmp = calloc(n, sizeof(double));
	for (int i = 0; i < n; ++i)
		tmp[i] = arr[i];
	a->coords = tmp;
	a->size   = n;
	return a;
}

void deleteVector(vector* a){
	if (a == NULL) return;
	free(a->coords);
	free(a);
}

vector* addVector(vector* a, vector* b){
	if (a != NULL && b != NULL && a->size == b->size) {
		VEC_OP(a, +, b);
	}
	else return NULL;
}

vector* subVector(vector* a, vector* b){
	if (a != NULL && b != NULL && a->size == b->size) {
		VEC_OP(a, -, b);
	}
	else return NULL;
}

vector* mulVector(vector* a, double scalar){
	if (a!= NULL && a->size != 0) {
		VEC_SCALAR_OP(a, *, scalar);
	}
	else return NULL;
}

double dotVectors(vector* a, vector* b){
	if (a != NULL && b != NULL && a->size == b->size) {
		double scalar = 0.0;
		for (int i = 0; i < a->size; ++i)
			scalar += a->coords[i] * b->coords[i];
		return scalar;
	}
	else return -1.0;
}

vector* crossVectors(vector* a, vector* b){
	if (a != NULL && b != NULL && a->size == 3 && b->size == 3) {
		vector* c = (vector*)malloc(sizeof(vector));
		c->size = 3;	
		c->coords = calloc(c->size, sizeof(double));
		c->coords[0] =  a->coords[1] * b->coords[2] - b->coords[1] * a->coords[2];
		c->coords[1] = -a->coords[0] * b->coords[2] + b->coords[0] * a->coords[2];
		c->coords[2] =  a->coords[0] * b->coords[1] - b->coords[0] * a->coords[1];
		return c;
	}
	else return NULL;
}

int getSize(vector* a) {
	return (a == NULL || a->size <= 0) ? -1 : a->size;
}