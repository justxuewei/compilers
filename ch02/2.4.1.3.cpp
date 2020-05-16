#include "iostream"
#include "Parser.h"

/*
 * Grammar: S -> 0 S 1 | 0 1
 * It is not invalid for a predictive parser, because S can be split into S1 and S2 like below:
 * - S1 -> 0 S 1, FIRST(S1) = { 0 }
 * - S2 -> 0 1, FIRST(S2) = { 0 }
 * parser has no idea which S should be used, therefore, a conversion must be applied to S:
 * - S -> 0 R
 * - R -> S 1 | 1
 */
class Parser3 : public Parser {
public:
    explicit Parser3(string s) : Parser(move(s)) {}
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
            case '0':
                match('0');
                R();
                break;
            default:
                if (isInvalid) {
                    isInvalid = false;
                    cerr << "Syntax invalid!";
                }
        }
    }

    void R() {
        switch (expr[iLookahead]) {
            case '0':
                S();
                match('1');
                break;
            case '1':
                match('1');
                break;
            default:
                if (isInvalid) {
                    isInvalid = false;
                    cerr << "Syntax invalid!";
                }
        }
    }
};

int main() {
    auto parser3 = new Parser3("00111");
    parser3->analyse();
    delete parser3;
    return 0;
}