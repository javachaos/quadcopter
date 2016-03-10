/*
 * pwm.h
 *
 *  Created on: Mar 5, 2016
 *      Author: fred
 */

#ifndef SRC_C_DRIVERS_PWM_H_
#define SRC_C_DRIVERS_PWM_H_

/*
Copyright (c) 2013 Adafruit
Author: Justin Cooper
Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Modified By: Fred Laderoute 2016
*/

#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif
int build_path(const char *partial_path, const char *prefix, char *full_path, size_t full_path_len);
int load_device_tree(const char *name);
int unload_device_tree(const char *name);
int pwm_start(const char *key, float duty, float freq, int polarity);
int pwm_disable(const char *key);
int pwm_set_frequency(const char *key, float freq);
int pwm_set_duty_cycle(const char *key, float duty);
void pwm_cleanup(void);
int get_pwm_key(const char *input, char *key);

#ifdef __cplusplus
}
#endif
#endif /* SRC_C_DRIVERS_PWM_H_ */
