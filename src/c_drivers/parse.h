#ifndef PARSE_H_
#define PARSE_H_

#include <stdio.h>

typedef enum { false, true } bool;
/* bool type used for boolean operations */

const char COLON = ':';
const char NL = '\n';
const char SPACE = ' ';
const char PER = '.';
const char EOL = '\0';

/**
 * Parse a string and ensure it is
 *  ([0-9]{1,2}):([0-9]{1,2}):([0-9]{1-10}\.[0-9]{1-10}):(.*{228})(/n)*
 *  Max size of s is 256 bytes (256 chars).
 *
 */
char* parse(char* s);

#endif
