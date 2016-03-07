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

//PyObject* module;
//PyObject* create_oled(void);
void write_str(const char* str);
//void scroll_text(const char* str);
void init_c(void);
void destroy_c(void);
#ifdef __cplusplus
}
#endif
#endif /* SRC_C_DRIVERS_OLED_H_ */
