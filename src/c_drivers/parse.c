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

char* parse(char* s) {
    int i = -1;
    while (isDigit(s[++i]));
    if(i < 2 && (s[i] == COLON || s[i-1] == COLON)) {
        if (i > 2) {
            return 0;
        } else {
            while(isDigit(s[++i]));
            if(i < 5 && (s[i] != COLON || s[i-1] == COLON)) {
                if (i > 5) {
                    return 0;
                } else {
                    while((isDigit(s[++i]) || s[i] == PER));
                    if(i < 27 && (s[i] != COLON || s[i-1] != COLON)) {
                        if (i > 27) {
                            return 0;
                        } else {
                            while((isAlpha(s[++i]) || isDigit(s[i]) || i == SPACE || i == PER || i == NL) && i != EOL);
                            if (i < 256) {
                                return s;
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}

int main(int argc, char* argv) {

    printf("%s", parse("0:0:0.000:Test\n "));
    return 0;
}
