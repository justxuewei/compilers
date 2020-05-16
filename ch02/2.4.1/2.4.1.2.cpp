#include "iostream"
#include "Parser.h"

/*
 * Grammar: S -> S ( S ) S | epsilon
 * which is left recursive, so the first thing we need to do is that convert it to right recursive:
 * Right recursive grammar: S -> ( S ) S | epsilon
 *
 * Some input examples:
 * - ()()
 * - (() (invalid)
 * - (())
 */
class Parser2 : public Parser {
public:
    explicit Parser2(string s) : Parser(move(s)) {}
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
            case '(':
                match('(');
                S();
                match(')');
                S();
                break;
        }
    }
};

int main() {
    auto parser2 = new Parser2("()()()()");
    parser2->analyse();
    delete parser2;
    return 0;
}