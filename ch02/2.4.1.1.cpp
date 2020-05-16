#include "iostream"
#include "Parser.h"

/*
 * Grammar: S -> + S S | - S S | a
 * Some input examples:
 * - +-aa
 * - a+-aa (invalid)
 * -  (invalid)
 */
class Parser1: public Parser {
public:

    explicit Parser1(string e) : Parser(move(e)) {}

    void analyse() override {
        S();
        if (isInvalid && iLookahead != expr.size()) {
            isInvalid = false;
            cerr << "Syntax invalid!";
        }
    }

private:
    void S() {
        switch (expr[iLookahead]) {
            case '+':
            case '-':
                match(expr[iLookahead]);
                S();S();
                break;
            case 'a':
                match(expr[iLookahead]);
                break;
            default:
                if (isInvalid && iLookahead < expr.size()) {
                    isInvalid = false;
                    cerr << "Syntax invalid!";
                }
                else return;
        }
    }
};

int main() {
    auto *parser = new Parser1(" ");
    parser->analyse();
    delete parser;
    return 0;
}