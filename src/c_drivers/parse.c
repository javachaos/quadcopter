#include <parse.h>

bool isDigit(char c) {
    if(c <= '9' && c >= '0')
        return true;
    return false;
}

bool isAlpha(char c) {
    if((c >= 'a' && c <= 'z') ||
            (c >= 'A' && c <= 'Z'))
        return true;
    return false;
}

bool parse(const char* str) {
    int len = strlen(str);
    if(len < 1 || len > 21) {
        return 0;
    }
    char s[21];
    strcpy(s,str);
    int i = -1;
    while (isDigit(s[++i])
        || isAlpha(s[i])
        || s[i] == UL
        || s[i] == DASH
        || s[i] == NL
        || s[i] == SPACE
        || s[i] == PER
        || i > 20);
    return s[i] == EOL;
}
