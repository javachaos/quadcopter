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

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <time.h>
#include "pwm.h"

#define KEYLEN 7

#define PERIOD 0
#define DUTY 1

int pwm_initialized = 0;

char ctrl_dir[35];
char ocp_dir[25];

typedef struct pins_t {
    const char *name;
    const char *key;
    int gpio;
    int pwm_mux_mode;
    int ain;
} pins_t;

//Table generated based on https://raw.github.com/jadonk/bonescript/master/node_modules/bonescript/bone.js
pins_t table[] = {
  { "USR0", "USR0", 53, -1, -1},
  { "USR1", "USR1", 54, -1, -1},
  { "USR2", "USR2", 55, -1, -1},
  { "USR3", "USR3", 56, -1, -1},
  { "DGND", "P8_1", 0, -1, -1},
  { "DGND", "P8_2", 0, -1, -1},
  { "GPIO1_6", "P8_3", 38, -1, -1},
  { "GPIO1_7", "P8_4", 39, -1, -1},
  { "GPIO1_2", "P8_5", 34, -1, -1},
  { "GPIO1_3", "P8_6", 35, -1, -1},
  { "TIMER4", "P8_7", 66, -1, -1},
  { "TIMER7", "P8_8", 67, -1, -1},
  { "TIMER5", "P8_9", 69, -1, -1},
  { "TIMER6", "P8_10", 68, -1, -1},
  { "GPIO1_13", "P8_11", 45, -1, -1},
  { "GPIO1_12", "P8_12", 44, -1, -1},
  { "EHRPWM2B", "P8_13", 23, 4, -1},
  { "GPIO0_26", "P8_14", 26, -1, -1},
  { "GPIO1_15", "P8_15", 47, -1, -1},
  { "GPIO1_14", "P8_16", 46, -1, -1},
  { "GPIO0_27", "P8_17", 27, -1, -1},
  { "GPIO2_1", "P8_18", 65, -1, -1},
  { "EHRPWM2A", "P8_19", 22, 4, -1},
  { "GPIO1_31", "P8_20", 63, -1, -1},
  { "GPIO1_30", "P8_21", 62, -1, -1},
  { "GPIO1_5", "P8_22", 37, -1, -1},
  { "GPIO1_4", "P8_23", 36, -1, -1},
  { "GPIO1_1", "P8_24", 33, -1, -1},
  { "GPIO1_0", "P8_25", 32, -1, -1},
  { "GPIO1_29", "P8_26", 61, -1, -1},
  { "GPIO2_22", "P8_27", 86, -1, -1},
  { "GPIO2_24", "P8_28", 88, -1, -1},
  { "GPIO2_23", "P8_29", 87, -1, -1},
  { "GPIO2_25", "P8_30", 89, -1, -1},
  { "UART5_CTSN", "P8_31", 10, -1, -1},
  { "UART5_RTSN", "P8_32", 11, -1, -1},
  { "UART4_RTSN", "P8_33", 9, -1, -1},
  { "UART3_RTSN", "P8_34", 81, 2, -1},
  { "UART4_CTSN", "P8_35", 8, -1, -1},
  { "UART3_CTSN", "P8_36", 80, 2, -1},
  { "UART5_TXD", "P8_37", 78, -1, -1},
  { "UART5_RXD", "P8_38", 79, -1, -1},
  { "GPIO2_12", "P8_39", 76, -1, -1},
  { "GPIO2_13", "P8_40", 77, -1, -1},
  { "GPIO2_10", "P8_41", 74, -1, -1},
  { "GPIO2_11", "P8_42", 75, -1, -1},
  { "GPIO2_8", "P8_43", 72, -1, -1},
  { "GPIO2_9", "P8_44", 73, -1, -1},
  { "GPIO2_6", "P8_45", 70, 3, -1},
  { "GPIO2_7", "P8_46", 71, 3, -1},
  { "DGND", "P9_1", 0, -1, -1},
  { "DGND", "P9_2", 0, -1, -1},
  { "VDD_3V3", "P9_3", 0, -1, -1},
  { "VDD_3V3", "P9_4", 0, -1, -1},
  { "VDD_5V", "P9_5", 0, -1, -1},
  { "VDD_5V", "P9_6", 0, -1, -1},
  { "SYS_5V", "P9_7", 0, -1, -1},
  { "SYS_5V", "P9_8", 0, -1, -1},
  { "PWR_BUT", "P9_9", 0, -1, -1},
  { "SYS_RESETn", "P9_10", 0, -1, -1},
  { "UART4_RXD", "P9_11", 30, -1, -1},
  { "GPIO1_28", "P9_12", 60, -1, -1},
  { "UART4_TXD", "P9_13", 31, -1, -1},
  { "EHRPWM1A", "P9_14", 50, 6, -1},
  { "GPIO1_16", "P9_15", 48, -1, -1},
  { "EHRPWM1B", "P9_16", 51, 6, -1},
  { "I2C1_SCL", "P9_17", 5, -1, -1},
  { "I2C1_SDA", "P9_18", 4, -1, -1},
  { "I2C2_SCL", "P9_19", 13, -1, -1},
  { "I2C2_SDA", "P9_20", 12, -1, -1},
  { "UART2_TXD", "P9_21", 3, 3, -1},
  { "UART2_RXD", "P9_22", 2, 3, -1},
  { "GPIO1_17", "P9_23", 49, -1, -1},
  { "UART1_TXD", "P9_24", 15, -1, -1},
  { "GPIO3_21", "P9_25", 117, -1, -1},
  { "UART1_RXD", "P9_26", 14, -1, -1},
  { "GPIO3_19", "P9_27", 115, -1, -1},
  { "SPI1_CS0", "P9_28", 113, 4, -1},
  { "SPI1_D0", "P9_29", 111, 1, -1},
  { "SPI1_D1", "P9_30", 112, -1, -1},
  { "SPI1_SCLK", "P9_31", 110, 1, -1},
  { "VDD_ADC", "P9_32", 0, -1, -1},
  { "AIN4", "P9_33", 0, -1, 4},
  { "GNDA_ADC", "P9_34", 0, -1, -1},
  { "AIN6", "P9_35", 0, -1, 6},
  { "AIN5", "P9_36", 0, -1, 5},
  { "AIN2", "P9_37", 0, -1, 2},
  { "AIN3", "P9_38", 0, -1, 3},
  { "AIN0", "P9_39", 0, -1, 0},
  { "AIN1", "P9_40", 0, -1, 1},
  { "CLKOUT2", "P9_41", 20, -1, -1},
  { "GPIO0_7", "P9_42", 7, 0, -1},
  { "DGND", "P9_43", 0, -1, -1},
  { "DGND", "P9_44", 0, -1, -1},
  { "DGND", "P9_45", 0, -1, -1},
  { "DGND", "P9_46", 0, -1, -1},
    { NULL, NULL, 0 }
};

// pwm exports
struct pwm_exp
{
    char key[KEYLEN+1]; /* leave room for terminating NUL byte */
    int period_fd;
    int duty_fd;
    int polarity_fd;
    unsigned long duty;
    unsigned long period_ns;
    struct pwm_exp *next;
};
struct pwm_exp *exported_pwms = NULL;

struct pwm_exp *lookup_exported_pwm(const char *key)
{
    struct pwm_exp *pwm = exported_pwms;

    while (pwm != NULL)
    {
        if (strcmp(pwm->key, key) == 0) {
            return pwm;
        }
        pwm = pwm->next;
    }

    return NULL; /* standard for pointers */
}

int build_path(const char *partial_path, const char *prefix, char *full_path, size_t full_path_len)
{
    DIR *dp;
    struct dirent *ep;

    dp = opendir (partial_path);
    if (dp != NULL) {
        while ((ep = readdir (dp))) {
            // Enforce that the prefix must be the first part of the file
            char* found_string = strstr(ep->d_name, prefix);

            if (found_string != NULL && (ep->d_name - found_string) == 0) {
                snprintf(full_path, full_path_len, "%s/%s", partial_path, ep->d_name);
                (void) closedir (dp);
                return 1;
            }
        }
        (void) closedir (dp);
    } else {
        return 0;
    }

    return 0;
}

int initialize_pwm(void)
{
    if  (!pwm_initialized && load_device_tree("am33xx_pwm")) {
        build_path("/sys/devices", "ocp", ocp_dir, sizeof(ocp_dir));
        pwm_initialized = 1;
        return 1;
    }

    return 0;
}

int load_device_tree(const char *name)
{
    FILE *file = NULL;
    char slots[40];
    char line[256];

    build_path("/sys/devices", "bone_capemgr", ctrl_dir, sizeof(ctrl_dir));
    snprintf(slots, sizeof(slots), "%s/slots", ctrl_dir);

    file = fopen(slots, "r+");
    if (!file) {
        return 0;
    }

    while (fgets(line, sizeof(line), file)) {
        //the device is already loaded, return 1
        if (strstr(line, name)) {
            fclose(file);
            return 1;
        }
    }

    //if the device isn't already loaded, load it, and return
    //fprintf(file, name);
    fputs(name, file);
    fclose(file);

    //0.2 second delay
    struct timespec ts;
    ts.tv_nsec = 200000000;
    nanosleep(&ts, NULL);

    return 1;
}

int unload_device_tree(const char *name)
{
    FILE *file = NULL;
    char slots[40];
    char line[256];
    char *slot_line;

    build_path("/sys/devices", "bone_capemgr", ctrl_dir, sizeof(ctrl_dir));
    snprintf(slots, sizeof(slots), "%s/slots", ctrl_dir);

    file = fopen(slots, "r+");
    if (!file) {
        return 0;
    }

    while (fgets(line, sizeof(line), file)) {
        //the device is loaded, let's unload it
        if (strstr(line, name)) {
            slot_line = strtok(line, ":");
            //remove leading spaces
            while(*slot_line == ' ')
                slot_line++;

            fprintf(file, "-%s", slot_line);
            fclose(file);
            return 1;
        }
    }

    //not loaded, close file
    fclose(file);

    return 1;
}

int pwm_set_frequency(const char *key, float freq) {
    int len;
    char buffer[20];
    unsigned long period_ns;
    struct pwm_exp *pwm;

    if (freq <= 0.0)
        return -1;

    pwm = lookup_exported_pwm(key);

    if (pwm == NULL) {
        return -1;
    }

    period_ns = (unsigned long)(1e9 / freq);

    if (period_ns != pwm->period_ns) {
        pwm->period_ns = period_ns;

        len = snprintf(buffer, sizeof(buffer), "%lu", period_ns);
        if(write(pwm->period_fd, buffer, len)){}
    }

    return 1;
}

int pwm_set_polarity(const char *key, int polarity) {
    int len;
    char buffer[7]; /* allow room for trailing NUL byte */
    struct pwm_exp *pwm;

    pwm = lookup_exported_pwm(key);

    if (pwm == NULL) {
        return -1;
    }

    len = snprintf(buffer, sizeof(buffer), "%d", polarity);

    write(pwm->polarity_fd, buffer, len);

    return 0;
}

int pwm_set_duty_cycle(const char *key, float duty) {
    int len;
    char buffer[20];
    struct pwm_exp *pwm;

    if (duty < 0.0 || duty > 100.0)
        return -1;

    pwm = lookup_exported_pwm(key);

    if (pwm == NULL) {
        return -1;
    }

    pwm->duty = (unsigned long)(pwm->period_ns * (duty / 100.0));

    len = snprintf(buffer, sizeof(buffer), "%lu", pwm->duty);

    write(pwm->duty_fd, buffer, len);

    return 0;
}

int pwm_start(const char *key, float duty, float freq, int polarity)
{
    char fragment[18];
    char pwm_test_fragment[20];
    char pwm_test_path[45];
    char period_path[50];
    char duty_path[50];
    char polarity_path[55];
    int period_fd, duty_fd, polarity_fd;
    struct pwm_exp *new_pwm, *pwm;

    if(!pwm_initialized) {
        initialize_pwm();
    }

    snprintf(fragment, sizeof(fragment), "bone_pwm_%s", key);


    if (!load_device_tree(fragment)) {
        //error enabling pin for pwm
        return -1;
    }

    //creates the fragment in order to build the pwm_test_filename, such as "pwm_test_P9_13"
    snprintf(pwm_test_fragment, sizeof(pwm_test_fragment), "pwm_test_%s", key);

    //finds and builds the pwm_test_path, as it can be variable...
    build_path(ocp_dir, pwm_test_fragment, pwm_test_path, sizeof(pwm_test_path));

    //create the path for the period and duty
    snprintf(period_path, sizeof(period_path), "%s/period", pwm_test_path);
    snprintf(duty_path, sizeof(duty_path), "%s/duty", pwm_test_path);
    snprintf(polarity_path, sizeof(polarity_path), "%s/polarity", pwm_test_path);

    //add period and duty fd to pwm list
    if ((period_fd = open(period_path, O_RDWR)) < 0)
        return -1;


    if ((duty_fd = open(duty_path, O_RDWR)) < 0) {
        //error, close already opened period_fd.
        close(period_fd);
        return -1;
    }

    if ((polarity_fd = open(polarity_path, O_RDWR)) < 0) {
        //error, close already opened period_fd and duty_fd.
        close(period_fd);
        close(duty_fd);
        return -1;
    }

    // add to list
    new_pwm = (struct pwm_exp*)malloc(sizeof(struct pwm_exp));
    if (new_pwm == 0) {
        return -1; // out of memory
    }

    strncpy(new_pwm->key, key, KEYLEN);  /* can leave string unterminated */
    new_pwm->key[KEYLEN] = '\0'; /* terminate string */
    new_pwm->period_fd = period_fd;
    new_pwm->duty_fd = duty_fd;
    new_pwm->polarity_fd = polarity_fd;
    new_pwm->next = NULL;

    if (exported_pwms == NULL)
    {
        // create new list
        exported_pwms = new_pwm;
    } else {
        // add to end of existing list
        pwm = exported_pwms;
        while (pwm->next != NULL)
            pwm = pwm->next;
        pwm->next = new_pwm;
    }

    pwm_set_frequency(key, freq);
    pwm_set_polarity(key, polarity);
    pwm_set_duty_cycle(key, duty);

    return 1;
}

int pwm_disable(const char *key)
{
    struct pwm_exp *pwm, *temp, *prev_pwm = NULL;
    char fragment[18];

    snprintf(fragment, sizeof(fragment), "bone_pwm_%s", key);
    unload_device_tree(fragment);

    // remove from list
    pwm = exported_pwms;
    while (pwm != NULL)
    {
        if (strcmp(pwm->key, key) == 0)
        {
            //close the fd
            close(pwm->period_fd);
            close(pwm->duty_fd);
            close(pwm->polarity_fd);

            if (prev_pwm == NULL)
            {
                exported_pwms = pwm->next;
                prev_pwm = pwm;
            } else {
                prev_pwm->next = pwm->next;
            }

            temp = pwm;
            pwm = pwm->next;
            free(temp);
        } else {
            prev_pwm = pwm;
            pwm = pwm->next;
        }
    }
    return 0;
}

int copy_pwm_key_by_key(const char *input_key, char *key)
{
    pins_t *p;
    for (p = table; p->key != NULL; ++p) {
        if (strcmp(p->key, input_key) == 0) {
            //validate it's a valid pwm pin
            if (p->pwm_mux_mode == -1)
                return 0;

            strncpy(key, p->key, 7);
            key[7] = '\0';
            return 1;
        }
    }
    return 0;
}

int get_pwm_key_by_name(const char *name, char *key)
{
    pins_t *p;
    for (p = table; p->name != NULL; ++p) {
        if (strcmp(p->name, name) == 0) {
            //validate it's a valid pwm pin
            if (p->pwm_mux_mode == -1)
                return 0;

            strncpy(key, p->key, 7);
            key[7] = '\0';
            return 1;
        }
    }
    return 0;
}

int get_pwm_key(const char *input, char *key)
{
    if (!copy_pwm_key_by_key(input, key)) {
        return get_pwm_key_by_name(input, key);
    }

    return 1;
}

void pwm_cleanup(void)
{
    while (exported_pwms != NULL) {
        pwm_disable(exported_pwms->key);
    }
}
