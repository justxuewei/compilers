//
// Created by XavierNiu on 2020/5/16.
//

#ifndef COMPILERS_PARSER_H
#define COMPILERS_PARSER_H

#include "iostream"

using namespace std;


class Parser {
public:
    string expr;
    int iLookahead = 0;
    bool isInvalid = true;

    explicit Parser(string e) : expr(move(e)) {}

    virtual void analyse() {}

protected:
    void match(char c) {
        if (c == expr[iLookahead]) {
            printf("'%c' is matched.\n", c);
            if (iLookahead < expr.size()) iLookahead++;
            else return;
        } else {
            isInvalid = false;
            cerr << "Syntax invalid!";
        }
    }
};


#endif //COMPILERS_PARSER_H
