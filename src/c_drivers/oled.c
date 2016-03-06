#include "oled.h"

PyObject* create_module(void) {
    Py_Initialize();
    PyObject* pName = PyString_FromString("oled.py");
    PyObject* pModule = PyImport_Import(pName);
    Py_DECREF(pName);
   return pModule;
}

void close_module(PyObject* module) {
    Py_XDECREF(module);
    Py_Finalize();
}

void write_str(const char* str) {
    PyObject* module = create_module();
    PyObject* pStr = PyString_FromString(str);
    PyObject* clazz = PyObject_GetAttrString(module,"OLED");
    PyObject_CallObject(clazz, NULL);
    PyObject* pFunc = PyObject_GetAttrString(clazz,".write_str");

    if (pFunc && PyCallable_Check(pFunc)) {
        PyObject_CallObject(pFunc, pStr);
    }
    Py_XDECREF(clazz);
    Py_DECREF(pStr);
    Py_XDECREF(pFunc);
    close_module(module);
    Py_Finalize();
}
