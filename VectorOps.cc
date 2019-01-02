//Here begins file VectorOps.cc
//Has one function, magnitude, which returns the magnitude of a vector of a given dimension.

#include <math.h>
#include "VectorOps.h"
#include <vector>

double VectorOps::magnitude(vector<double> xVector, int dimension) {
    //dimension, for ease
    int n = dimension;
    //place holder
    double magSquared = 0.0;
    
    for (int i = 0 ; i < n ; i++ ){
        double x = xVector[i];
        magSquared += pow(x, 2);
    }
    double mag = sqrt(magSquared);
    
    return mag;
}
