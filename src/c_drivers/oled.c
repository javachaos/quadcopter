#include <syslog.h>
#include "oled.h"

void init_c(void) {
	Py_Initialize();
}

void destroy_c(void) {
	Py_Finalize();
	closelog();
}

void write_str(const char* str) {
	PyGILState_STATE state = PyGILState_Ensure();
	PyObject *pName, *pModule, *pCons;
	pName = PyString_FromString("oled");

	/* Error checking of pName left out */
	pModule = PyImport_Import(pName);
	Py_XDECREF(pName);

	if (pModule != NULL) {
		pCons = PyObject_GetAttrString(pModule, "OLED");
		pCons = PyObject_CallObject(pCons, NULL);
		char func[] = "write_str";
		char string[] = "s";
		/* pFunc is a new reference */
		PyObject_CallMethod(pCons, func, string, str);
        	Py_XDECREF(pCons);
		Py_XDECREF(pModule);
	} else {
		PyErr_Print();
		syslog(LOG_NOTICE, "Failed to load OLED.\n");
	}
	PyGILState_Release(state);
}
