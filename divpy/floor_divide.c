#include <Python.h>
#include "libdivide/libdivide.h"

static PyObject *floor_divide(PyObject *self, PyObject *args);

static PyMethodDef ListsMethods[] = {
    {"floor_divide", floor_divide, METH_VARARGS, "Python interface for floor_divide function"},
    {NULL, NULL, 0, NULL}
};

static inline PyObject *libdivide_divide(PyObject *pItem, const struct libdivide_u64_t *divisor) {
    long cItem, cQuotient;
    PyObject *pQuotient;

    cItem = PyLong_AsLong(pItem);
    cQuotient = libdivide_u64_do(cItem, divisor);
    pQuotient = PyLong_FromLong(cQuotient);
    return pQuotient;
}

static struct PyModuleDef floor_dividemodule = {
    PyModuleDef_HEAD_INIT,
    "floor_divide",
    "Python interface for the floor_divide function",
    -1,
    ListsMethods
};

static PyObject *floor_divide(PyObject *self, PyObject *args) {
    PyObject *pList, *pListNew;
    PyObject *pItem, *pQuotient;
    Py_ssize_t n;
    Py_ssize_t i;
    long divisor;
    struct libdivide_u64_t libdivisor;

    if (!PyArg_ParseTuple(args, "O!i", &PyList_Type, &pList, &divisor)) {
        PyErr_SetString(PyExc_TypeError, "parameter must be a list and an integer.");
        return NULL;
    }

    libdivisor = libdivide_u64_gen(divisor);

    n = PyList_Size(pList);
    pListNew = PyList_New(n);
    for (i=0; i<n; i++) {
        pItem = PyList_GetItem(pList, i);
        if(!PyLong_Check(pItem)) {
            char *error_message = malloc((log(n)+50)*sizeof(char));
            sprintf(error_message, "List item at index %ld is not an integer!", i);
            PyErr_SetString(PyExc_TypeError, error_message);
            return NULL;
        }
        pQuotient = libdivide_divide(pItem, &libdivisor);
        PyList_SetItem(pListNew, i, pQuotient);
    }

    return pListNew;
}

PyMODINIT_FUNC PyInit_divpy(void) {
        return PyModule_Create(&floor_dividemodule);
}