#include "amath.h"

typedef pvector (*__createVector)(vecdata, uint);
typedef pvector (*__vectorOperation)(pvector, pvector);
typedef pvector (*__mulVector)(pvector, double);
typedef pvector (*__crossVectors)(pvector, pvector);
typedef double  (*__dotVectors)(pvector, pvector);
typedef void    (*__destroyVector)(pvector, pvector*);
typedef vecdata (*__getVecData)(pvector);
typedef int     (*__getVecSize)(pvector);

typedef pmatrix (*__createMatrix)(mxdata, uint, uint);
typedef pmatrix (*__matrixOperation)(pmatrix, pmatrix);
typedef pmatrix (*__mulMatrix)(pmatrix, double);
typedef pmatrix (*__transpose)(pmatrix);
typedef double  (*__getDeterminant)(pmatrix);
typedef void    (*__destroyMatrix)(pmatrix, pmatrix*);
typedef pmatrix (*__getMxData)(pmatrix);
typedef int     (*__getMxSize)(pmatrix);

__createVector    _createVector;
__vectorOperation _vectorOperation;
__mulVector       _mulVector;
__crossVectors    _crossVectors;
__dotVectors		  _dotVectors;
__destroyVector   _destroyVector;
__getVecData      _getVecData;
__getVecSize      _getVecSize;

__createMatrix    _createMatrix;
__matrixOperation _matrixOperation;
__mulMatrix       _mulMatrix;
__transpose       _transpose;
__getDeterminant  _getDeterminant;
__destroyMatrix   _destroyMatrix;
__getMxData       _getMxData;
__getMxSize       _getMxSize;
