#include <Python.h>

static PyObject *floor_divide(PyObject *self, PyObject *args);

static PyMethodDef ListsMethods[] = {
    {"floor_divide", floor_divide, METH_VARARGS, "Python interface for floor_divide function"},
    {NULL, NULL, 0, NULL}
};


static struct PyModuleDef floor_dividemodule = {
    PyModuleDef_HEAD_INIT,
    "floor_divide",
    "Python interface for the floor_divide function",
    -1,
    ListsMethods
};

static PyObject *floor_divide(PyObject *self, PyObject *args) {
    PyObject *pList;
    PyObject *pItem;
    Py_ssize_t n;
    Py_ssize_t i;
    int divisor;

    if (!PyArg_ParseTuple(args, "O!i", &PyList_Type, &pList, &divisor)) {
        PyErr_SetString(PyExc_TypeError, "parameter must be a list and an integer.");
        return NULL;
    }

    n = PyList_Size(pList);
    for (i=0; i<n; i++) {
        pItem = PyList_GetItem(pList, i);
        if(!PyLong_Check(pItem)) {
            PyErr_SetString(PyExc_TypeError, "list items must be integers.");
            return NULL;
        }
    }

    return Py_BuildValue("");
}

PyMODINIT_FUNC PyInit_divpy(void) {
        return PyModule_Create(&floor_dividemodule);
}