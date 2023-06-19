# define PY_SSIZE_T_CLEAN
# include <Python.h>
# include "kmeans.h"


double** convertPyMatToCMat(PyObject* matrix, int row, int col){
    int i;
    int j;
    double** mat;
    PyObject* rowPy;
    PyObject* item;

    mat = (double**) malloc(row * sizeof(double*));
    printf("%s\n", "***1***");
    for (i = 0; i < row; i++) {
        printf("%s\n", "***2***");
        mat[i] = (double*)malloc(col * sizeof(double));
        printf("%s\n", "***3***");
        rowPy = PyList_GetItem(matrix, i);
        printf("%s\n", "***4***");
        for (j = 0; j < col; j++) {
            printf("%s\n", "***5***");
            item = PyList_GetItem(rowPy, j);
            printf("%s\n", "***6***");
            mat[i][j] = PyFloat_AsDouble(item);
            printf("%s\n", "***7***");
            printf("%f\n", mat[i][j]);
        }
    }
    return mat;
}

static PyObject* fit(PyObject *self, PyObject *args){

    int K, iter;
    int numberOfvectors, vectorsLength;
    double eps;
    PyObject *vectorsList;
    PyObject *centeroids;

    double **vectors;
    double **centers;
    // double **finalCenteroids;

    // PyObject* pyMatrix;
    // PyObject* pyRow;
    // PyObject* pyValue;

    if(!PyArg_ParseTuple(args, "iiiidOO", &K, &iter, &numberOfvectors, &vectorsLength, &eps, &vectorsList, &centeroids)) {
        return NULL;
    }
    
    printf("%ld", PyObject_Length(vectorsList));

    vectors = convertPyMatToCMat(vectorsList, numberOfvectors, vectorsLength);
    centers = convertPyMatToCMat(centeroids, K, vectorsLength);

    // printf("%s", "***3***");

    // finalCenteroids = kMeans1(K, iter, numberOfvectors, vectorsLength, eps, vectors, centers);
    
    // pyMatrix = PyList_New(K);  // Create a new Python list object for the rows

    // if (pyMatrix) {
    //     for (int i = 0; i < K; i++) {
    //         pyRow = PyList_New(vectorsLength);  // Create a new Python list object for each row

    //         if (pyRow) {
    //             for (int j = 0; j < vectorsLength; j++) {
    //                 pyValue = Py_BuildValue("d", finalCenteroids[i][j]);  // Convert C value to Python float
    //                 PyList_SET_ITEM(pyRow, j, pyValue);  // Set the value in the Python row list
    //             }
    //         }

    //         PyList_SET_ITEM(pyMatrix, i, pyRow);  // Set the row list in the Python matrix list
    //     }
    // }

    return Py_BuildValue("i", 5);

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
