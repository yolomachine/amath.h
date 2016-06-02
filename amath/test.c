#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "test.h"

int main(int argc, char* argv[]){
	HINSTANCE hLib = LoadLibrary("amath.dll");
	if (hLib == NULL) return 0;

	_createVector	  =  (__createVector)	GetProcAddress(hLib, "createVector");
	_vectorOperation  =  (__vectorOperation)GetProcAddress(hLib, "vectorOperation");
	_mulVector		  =  (__mulVector)		GetProcAddress(hLib, "mulVector");
	_crossVectors	  =  (__crossVectors)	GetProcAddress(hLib, "crossVectors");
	_dotVectors		  =  (__dotVectors)		GetProcAddress(hLib, "dotVectors");
	_destroyVector	  =  (__destroyVector)	GetProcAddress(hLib, "destroyVector");
	_getVecData		  =  (__getVecData)		GetProcAddress(hLib, "getVecData");
	_getVecSize		  =  (__getVecSize)		GetProcAddress(hLib, "getVecSize");
	_createMatrix	  =  (__createMatrix)	GetProcAddress(hLib, "createMatrix");
	_matrixOperation  =  (__matrixOperation)GetProcAddress(hLib, "matrixOperation");
	_mulMatrix		  =  (__mulMatrix)		GetProcAddress(hLib, "mulMatrix");
	_transpose		  =  (__transpose)		GetProcAddress(hLib, "transpose");
	_getDeterminant	  =  (__getDeterminant)	GetProcAddress(hLib, "getDeterminant");
	_destroyMatrix	  =  (__destroyMatrix)	GetProcAddress(hLib, "destroyMatrix");
	_getMxData		  =  (__getMxData)		GetProcAddress(hLib, "getMxData");
	_getMxSize		  =  (__getMxSize)		GetProcAddress(hLib, "getMxSize");

	return 0;
}