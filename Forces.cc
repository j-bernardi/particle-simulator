//Here begins file 'Forces.cc'
//usage:
//a position vector xVector, the dimension of the space x exists in (size of array)
//the constant multiplier A, and finally the power dependence (eg = -2 for inverse square laws)
// function returns a pointer to the first element in the 'force' vector.
//
//EG F_ = A_|r_|^powerDep

#include "Forces.h"
#include "VectorOps.h"
#include <math.h>
#include <vector>

vector<double> Forces::forceCalculator(vector<double> xVector, int dimension, double constA, float powerDep) {
    
    //instantiate vector ops object and the storage variables
    VectorOps vo;
    vector<double> force (dimension);
    double mag = vo.magnitude(xVector, dimension);
    
    //Find the force by the rule f(x) = A*x*magx^powerdep-1 (minus 1 to account for mag x introduced on top
    for ( int i = 0 ; i < dimension ; i++ ){
        force[i] = constA*xVector[i]*pow(mag, powerDep -1 ) ;
    }
    
    return force;
}
