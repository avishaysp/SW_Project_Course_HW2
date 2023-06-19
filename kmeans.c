#include "kmeans.h"

/*
FUNCTIONS IMPLEMENTATION:
*/


void printMat(double** mat, int vectorsLength, int numOfVectors){
    int i;
    int j;

    for(i=0; i<numOfVectors; i++) {
        for(j=0; j<vectorsLength; j++) {
            printf("%.4f", mat[i][j]);
            if (j < vectorsLength - 1) {
                printf(",");
            }
        }
        printf("\n");
    }
}

int main(int argc, char** argv)
{
    return 0;
}


#ifdef DEBUG
void printVector(double *vec, int vectorsLength) {
    int i;
    for (i = 0;i < vectorsLength; i++) {
        printf("%f,", vec[i]);
    }
    printf("\n");
}
#endif

double** kMeans1(int K, int maxIter, int numberOfVectors, int vectorsLength, double eps, double** vectorsList, double** initCentroids) {
    int i;
    int currentIteration = 0;
    double maxMiuK;
    Centroid *closestCentroid;
    double **result;
    Centroid* centroids = (Centroid*)malloc(K * sizeof(Centroid));
    double* deltas = (double*)calloc(numberOfVectors, sizeof(double));

    /*Create Centroids*/
    for (i = 0; i < K; i++) {
        centroids[i].selfVector = copyArray(initCentroids[i], vectorsLength);
        centroids[i].numOfVectors = 0;
        centroids[i].relatedVectors = (double**)malloc(numberOfVectors * sizeof(double*));
    }
    do {
        for (i = 0; i < numberOfVectors; i++) {
            #ifdef DEBUG
                printf("Inside for. Iteration #%d\nThe vectors:\n", i);
                printMat(vectorsList, vectorsLength, numberOfVectors);
                printf("The centroids:\n");
                printMat(getCentroidsSelfVectors(centroids, K), vectorsLength, K);
                printf("Before calcClosestCentroid.\n"); */
            #endif
            closestCentroid = calcClosestCentroid(vectorsList[i], centroids, K, vectorsLength);
            #ifdef DEBUG
                printf("After calcClosestCentroid.\n");
                printf("Centroid: ");
                printVector(closestCentroid->selfVector, vectorsLength);
                printf("Vector: ");
                printVector(vectorsList[i], vectorsLength);
            #endif
            closestCentroid->relatedVectors[closestCentroid->numOfVectors] = vectorsList[i];
            closestCentroid->numOfVectors++;
        }
        #ifdef DEBUG
            printf("The Centroids before updating:\n");
            printMat(getCentroidsSelfVectors(centroids, K), vectorsLength, K);
        #endif
        for (i = 0; i < K; i++) {
            deltas[i] = update(&centroids[i], vectorsLength);
        }
        #ifdef DEBUG
            printf("The deltas:\n");
            printVector(deltas, K);
            printf("The Centroids after updating:\n");
            printMat(getCentroidsSelfVectors(centroids, K), vectorsLength, K);
        #endif
        maxMiuK = maxDelta(deltas, numberOfVectors);
        zeroArray(deltas, vectorsLength);
        for (i = 0; i < K; i++) {
            centroids[i].numOfVectors = 0;
        }
        currentIteration++;
    } while (currentIteration < maxIter && maxMiuK >= eps);
    result = getCentroidsSelfVectors(centroids, K);
    free(centroids);
    return result;
}

double maxDelta(double *deltas, int numberOfVectors) {
    int i;
    double maxVal = 0.0;

    for (i = 0; i < numberOfVectors; i++)
        maxVal = max(maxVal, deltas[i]);
    return maxVal;
}

double update(Centroid* centroid, int vectorsLength) {
    int i;
    double delta;
    double* oldCentroidVector;

    if (centroid->numOfVectors == 0) {
        return 0.0;
    }
    oldCentroidVector = copyArray(centroid->selfVector, vectorsLength);
    for (i = 0; i < vectorsLength; i++) {
        centroid->selfVector[i] = averageOf(centroid, i);
    }
    delta = euclidianDistance(oldCentroidVector, centroid->selfVector, vectorsLength);
    free(oldCentroidVector);
    centroid->numOfVectors = 0;
    return delta;
}

double** getCentroidsSelfVectors(Centroid* centroids, int K) {
    int i;
    double** selfVectors = (double**) malloc(K * sizeof(double*));

    for (i = 0; i < K; i ++) {
        selfVectors[i] = centroids[i].selfVector;
    }
    return selfVectors;
}

double averageOf(Centroid* centroid, int i) {
    double sum = 0.0;
    int j;

    for (j = 0; j < centroid->numOfVectors; j++) {
        sum += centroid->relatedVectors[j][i];
    }
    return sum / centroid->numOfVectors;
}

void freeRelatedVectors(Centroid* centroid) {
    int i;

    for (i = 0; i < centroid->numOfVectors; i++) {
        free(centroid->relatedVectors[i]);
    }
    free(centroid->relatedVectors);
    centroid->numOfVectors = 0;
}


    Centroid* calcClosestCentroid(double* vector, Centroid* centroids, int K, int vectorsLength) {
    int i;
    Centroid* closestCentroid = centroids;
    double distToClosest = euclidianDistance(vector, centroids[0].selfVector, vectorsLength);
    double currentDist;

    for (i = 1; i < K; i++) {
        currentDist = euclidianDistance(vector, centroids[i].selfVector, vectorsLength);
        if (currentDist < distToClosest) {
            closestCentroid = &centroids[i];
            distToClosest = currentDist;
        }
    }
    return closestCentroid;
}


double euclidianDistance(double *vector1, double *vector2, int vectorsLength) {
    double sum = 0.0;
    int i;

    for (i = 0; i < vectorsLength; i++) {
        sum += pow(vector1[i] - vector2[i], 2);
    }
    return sqrt(sum);
}

double* copyArray(double* inputArray, int rows) {
    int i;
    double* arrayCopy = (double*)malloc(rows * sizeof(double));

    if (arrayCopy == NULL) 
        return NULL;
    for (i = 0; i < rows; i++)
        arrayCopy[i] = inputArray[i];
    return arrayCopy;
}


void zeroArray(double* array, int arrayLength) {
    int i;

    for (i = 0; i < arrayLength; i++)
        array[i] = 0.0;
}
