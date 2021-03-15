#include <Python.h>

static PyObject *read_list(PyObject *self, PyObject *args);

static PyMethodDef ListsMethods[] = {
    {"read_list", read_list, METH_VARARGS, "Python interface for read_list function"},
    {NULL, NULL, 0, NULL}
};


static struct PyModuleDef read_listmodule = {
    PyModuleDef_HEAD_INIT,
    "read_list",
    "Python interface for the read_list function",
    -1,
    ListsMethods
};

static PyObject *read_list(PyObject *self, PyObject *args) {
    PyObject *pList;
    PyObject *pItem;
    Py_ssize_t n;
    int i;

    if (!PyArg_ParseTuple(args, "O!", &PyList_Type, &pList)) {
        PyErr_SetString(PyExc_TypeError, "parameter must be a list.");
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

PyMODINIT_FUNC PyInit_read_list(void) {
        return PyModule_Create(&read_listmodule);
}