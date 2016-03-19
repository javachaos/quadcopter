#ifndef PARSE_H_
#define PARSE_H_

#include <stdio.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

const char COLON = ':';
const char NL    = '\n';
const char SPACE = ' ';
const char PER   = '.';
const char EOL   = '\0';

/**
 * Parse a string and ensure it is
 *  ([0-9]{1,2}):([0-9]{1,2}):([0-9]{1-10}\.[0-9]{1-10}):(.*{228})(/n)*
 *  Max size of s is 256 bytes (256 chars).
 *
 */
char* parse(char* s);

#ifdef __cplusplus
}
#endif
#endif
