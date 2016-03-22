#ifndef PARSE_H_
#define PARSE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <string.h>

const char UL    = '_';
const char DASH  = '-';
const char NL    = '\n';
const char SPACE = ' ';
const char PER   = '.';
const char EOL   = '\0';

/**
 * Parse a string and ensure it is
 * [21bytes](20 character string of ([A-Za-z0-9_\-.\\n ]*{20}[\0])
 * Max size of s is 21 bytes (21 chars).
 */
bool parse(const char* s);

#ifdef __cplusplus
}
#endif
#endif
