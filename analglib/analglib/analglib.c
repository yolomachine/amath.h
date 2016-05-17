#include "analglib.h"
#include <stdio.h>
#include <stdlib.h>

#define VEC_OP(v1, op, v2){\
	pvector res = (pvector)malloc(sizeof(vector));\
	res->size = v1->size;\
	vecdata tmp = calloc(res->size, sizeof(vector));\
	for (size i = 0; i < res->size; ++i)\
		tmp[i] = v1->coords[i] op## v2->coords[i];\
	res->coords = tmp;\
	return res;\
}

#define VEC_SCALAR_OP(v, op, sc){\
	pvector res = (pvector)malloc(sizeof(vector));\
	res->size = v->size;\
	vecdata tmp = calloc(res->size, sizeof(vector));\
	for (size i = 0; i < res->size; ++i)\
		tmp[i] = v->coords[i] op## sc;\
	res->coords = tmp;\
	return res;\
}

#define GET_SIZE(a) (a == NULL) ? -1 : a->size

pvector createVector(vecdata v, size sz){
	if (v == NULL) return NULL;
	pvector a = (pvector)malloc(sizeof(vector));
	vecdata tmp = calloc(sz, sizeof(double));
	for (size i = 0; i < sz; ++i)
		tmp[i] = v[i];
	a->coords = tmp;
	a->size   = sz;
	return a;
}

void deleteVector(pvector a){
	if (a == NULL) return;
	free(a->coords);
	free(a);
}

pvector addVector(pvector a, pvector b){
	if (a != NULL && b != NULL && a->size == b->size) {
		VEC_OP(a, +, b);
	}
	else return NULL;
}

pvector subVector(pvector a, pvector b){
	if (a != NULL && b != NULL && a->size == b->size) {
		VEC_OP(a, -, b);
	}
	else return NULL;
}

pvector mulVector(pvector a, double scalar){
	if (a!= NULL && a->size != 0) {
		VEC_SCALAR_OP(a, *, scalar);
	}
	else return NULL;
}

double dotVectors(pvector a, pvector b){
	if (a != NULL && b != NULL && a->size == b->size) {
		double scalar = 0.0;
		for (size i = 0; i < a->size; ++i)
			scalar += a->coords[i] * b->coords[i];
		return scalar;
	}
	else return -1.0;
}

pvector crossVectors(pvector a, pvector b){
	if (a != NULL && b != NULL && a->size == 3 && b->size == 3) {
		pvector c = (pvector)malloc(sizeof(vector));
		c->size = 3;	
		c->coords = calloc(c->size, sizeof(double));
		c->coords[0] =  a->coords[1] * b->coords[2] - b->coords[1] * a->coords[2];
		c->coords[1] = -a->coords[0] * b->coords[2] + b->coords[0] * a->coords[2];
		c->coords[2] =  a->coords[0] * b->coords[1] - b->coords[0] * a->coords[1];
		return c;
	}
	else return NULL;
}