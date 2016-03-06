
#include "python2.7/Python.h"

PyObject* create_module() {
    PyInitialize();
    PyObject* pName = PyString_FromString("OLED");
    PyObject* pModule = PyImport_Import(pName);
    Py_DEVREF(pName);
    return pModule;    
}

void close_module(PyObject* module) {
    Py_XDECREF(module);
    PyFinalize();
}
void write_str(const char* str) {
    PyObject* module = create_module();
    PyObject* pStr = PyString_FromString(str);
    PyObject* pFunc = PyObject_GetAttrString(module,"write_str");

    if (pFunc && PyCallable_Check(pFunc)) {
        PyObject_CallObject(pFunc,pstr);
    }
    py_DECREP(pStr);
    Py_XDECREF(pFunc);
    close_module();
    Py_Finalize();
}
