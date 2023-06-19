# define PY_SSIZE_T_CLEAN
# include <Python.h>

static void fit(){
    printf("%s", "fit");
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