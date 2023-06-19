#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define max(a, b) ((a) > (b) ? (a) : (b))

typedef struct Centroid
{
    double* selfVector;
    int numOfVectors;
    double** relatedVectors;
}Centroid;


/*
FUNCTIONS DECLARATIONS:
*/

/*Input functions*/
void printMat(double**, int, int);

/*Calculating functions*/
double** deepCopy2DArray(double**, int, int);
double* copyArray(double*, int);
double update(Centroid*, int);
Centroid* calcClosestCentroid(double*, Centroid*, int, int);
double euclidianDistance(double*, double*, int);
void zeroArray(double*, int);
double averageOf(Centroid*, int);
void freeRelatedVectors(Centroid*);
double maxDelta(double*, int);
double** getCentroidsSelfVectors(Centroid*, int);
double** kMeans1(int, int, int, int, double, double**, double**);


#ifdef DEBUG
void printVector(double, int);
#endif