#ifndef SCANNER_H
#define SCANNER_H

#include "Token.h"
#include <cstdio>

class Scanner {
        int line;
        std::string buffer;
        std::FILE* file;
        int filter();
public:
        Scanner(std::FILE * fp){
                this->file = fp;
                this->line = 0;
        }
        Token::Token getToken();
};

#endif