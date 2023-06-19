# define PY_SSIZE_T_CLEAN
# include <Python.h>
# include "kmeans.c"

PyMODINIT_FUNC PyInit_mykmeanssp(void)
{
    PyObject *m;
    m = PyModule_Create(&kmeansmodule);
    if (!m) {
        return NULL;
    }
    return m;
}