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
    //Py_BEGIN_ALLOW_THREADS
    PyGILState_STATE state = PyGILState_Ensure();
    PyObject *pName, *pModule, *pFunc, *pWrite, *pCons;
    pName = PyString_FromString("oled");

    /* Error checking of pName left out */
    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != NULL) {
        pCons = PyObject_GetAttrString(pModule, "OLED");
        pCons = PyObject_CallObject(pCons, NULL);
        /* pFunc is a new reference */
        PyObject_CallMethod(pCons, "write_str", "s", str);
        Py_DECREF(pCons);
        Py_DECREF(pModule);
    }
    else {
        PyErr_Print();
        syslog (LOG_NOTICE, "Failed to load OLED.\n");
    }
    PyGILState_Release(state);
    //Py_END_ALLOW_THREADS
}
