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
//Py_BEGIN_ALLOW_THREADS
	PyGILState_STATE state = PyGILState_Ensure();
	PyObject *pName, *pModule, *pFunc, *pWrite, *pCons;
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
//	        Py_BLOCK_THREADS
        	Py_XDECREF(pCons);
		Py_XDECREF(pModule);
//              Py_UNBLOCK_THREADS
	} else {
		PyErr_Print();
		syslog(LOG_NOTICE, "Failed to load OLED.\n");
	}
	PyGILState_Release(state);
//	Py_END_ALLOW_THREADS
}
