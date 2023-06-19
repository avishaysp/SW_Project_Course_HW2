# define PY_SSIZE_T_CLEAN
# include <Python.h>
# include "kmeans.c"


double** convertPyMatToCMat(PyObject matrix, int row, int col){
    int i;
    int j;
    double** mat;
    PyObject* rowPy;
    PyObject* item;

    mat = (double**) malloc(row * sizeof(double*));
    for (i = 0; i < row; i++) {
        mat[i] = (double*)malloc(col * sizeof(double));

        rowPy = PyList_GetItem(&matrix, i);
        for (j = 0; j < col; j++) {
            item = PyList_GetItem(rowPy, j);
            mat[i][j] = PyFloat_AsDouble(item);  
        }
    }
    return mat;
}

static void fit(PyObject *self, PyObject *args){

    // int K, iter;
    // int numberOfvectors, vectorsLength;
    // double eps;
    // PyObject vectorsList;
    // PyObject centeroids;

    // double **vectors;
    // double **centers;
    // double **finalCenteroids;


    // if(!PyArg_ParseTuple(args, "iiiidOO", &K, &iter, &numberOfvectors, &vectorsLength, &eps, &vectorsList, &centeroids)) {
    //     return;
    // }

    // vectors = convertPyMatToCMat(vectorsList, numberOfvectors, vectorsLength);
    // centers = convertPyMatToCMat(centeroids, K, vectorsLength);

    // finalCenteroids = kMeans1(K, iter, numberOfvectors, vectorsLength, eps, vectors, centers);

    // printMat(finalCenteroids, K, vectorsLength);

    // printf("%d", 5);

}


static PyMethodDef kmeansMethods[] = {
    {"fit",
      (PyCFunction) fit,
      METH_VARARGS,           
      PyDoc_STR("Calculate the K centeroid of list of vector with max number of iteraion iter")}, 
    {NULL, NULL, 0, NULL}     
};

static struct PyModuleDef kmeansmodule = {
    PyModuleDef_HEAD_INIT,
    "mykmeanssp",
    NULL, 
    -1,  
    kmeansMethods 
};

PyMODINIT_FUNC PyInit_mykmeanssp(void)
{
    PyObject *m;
    m = PyModule_Create(&kmeansmodule);
    if (!m) {
        return NULL;
    }
    return m;
}
