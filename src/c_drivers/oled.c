#include <syslog.h>
#include "oled.h"
#include "Constants.h"

void init_c(void) {
    Py_Initialize();
    openlog (DAEMON_NAME, LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);
    syslog (LOG_NOTICE, "oled.c initailized.");
}

void destroy_c(void) {
    Py_Finalize();
    closelog();
}

void write_str(const char* str) {

    PyObject *pName, *pModule, *pFunc, *pWrite, *pCons;
    pName = PyString_FromString("oled");

    /* Error checking of pName left out */
    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != NULL) {
        pFunc = PyObject_GetAttrString(pModule, "write_str");
        /* pFunc is a new reference */

        if (pFunc && PyCallable_Check(pFunc)) {
            PyObject* string = PyString_FromString(str);
            syslog (LOG_NOTICE, "OLED: %s\n", str);
            PyObject_CallObject(pFunc, string);
            Py_DECREF(string);
        } else {
            if (PyErr_Occurred())
                PyErr_Print();
            syslog (LOG_NOTICE, "Cannot find class OLED.\n");
        }
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
    }
    else {
        PyErr_Print();
        syslog (LOG_NOTICE, "Failed to load OLED.\n");
    }
}
