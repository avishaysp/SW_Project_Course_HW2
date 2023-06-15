# define PY_SSIZE_T_CLEAN
# include <Python.h>
# include <kmeans.h>

static PyObject* fit(PyObject *self, PyObject *args){
    
    int K, iter;
    int numberOfvectors, vectorsLength;
    double eps;
    PyObject vectorsList;
    PyObject centeroids;

    double **vectors;
    double **centers;
    double **finalCenteroids;

    PyObject* pyMatrix;


    if(!PyArg_ParseTuple(args, "iiiidoo", &K, &iter, &numberOfvectors, &vectorsLength, &eps, &vectorsList, &centeroids)) {
        return NULL; 
    }

    vectors = convertPyMatToCMat(vectorsList, numberOfvectors, vectorsLength);
    centers = convertPyMatToCMat(centeroids, K, vectorsLength);

    finalCenteroids = kMeans(K, iter, numberOfvectors, vectorsLength, eps, vectors, centers);
    
    pyMatrix = Py_BuildValue("[");
    for (int i = 0; i < rows; i++) {
        PyObject* pyRow = Py_BuildValue("[");
        for (int j = 0; j < cols; j++) {
            PyObject* pyValue = Py_BuildValue("d", cMatrix[i][j]);
            PyList_Append(pyRow, pyValue);
            Py_DECREF(pyValue);
        }
        PyList_Append(pyMatrix, pyRow);
        Py_DECREF(pyRow);
    }
    return pyMatrix;
}

double** convertPyMatToCMat(pyObject matrix, int row, int col){
    int i;
    int j;
    double** mat;
    PyObject* rowPy;
    PyObject* item;

    mat = (double**) malloc(row * sizeof(double*));
    for (i = 0; i < row; i++) {
        mat[i] = (double*)malloc(col * sizeof(double));

        rowPy = PyList_GetItem(matrix, i);
        for (j = 0; j < col; j++) {
            item = PyList_GetItem(rowPy, j);
            vectors[i][j] = PyLong_AsLong(item);  // Assuming matrix elements are integers
        }
    }
    return mat;

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