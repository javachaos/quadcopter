/*
 * oled.h
 *
 *  Created on: Mar 5, 2016
 *      Author: fred
 */

#ifndef SRC_C_DRIVERS_OLED_H_
#define SRC_C_DRIVERS_OLED_H_

#include "python2.7/Python.h"
#ifdef __cplusplus
extern "C" {
#endif

PyObject* module;
PyObject* create_oled();
extern void write_str(const char* str);
extern void scroll_text(const char* str);

#ifdef __cplusplus
}
#endif
#endif /* SRC_C_DRIVERS_OLED_H_ */
