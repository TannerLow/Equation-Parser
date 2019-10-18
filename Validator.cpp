#include "Validator.h"

using namespace std;

Validator::Validator(vector<string> Tokens){
    tokens = Tokens;
    it = tokens.begin();
}

Validator::Validator(vector<string> Tokens, vector<string>::iterator start){
    tokens = Tokens;
    it = start;
}

bool Validator::endOfExpr(){
    return it == tokens.end();
}

bool Validator::terminal(string token){
    return (*it++ == token);
}

bool Validator::expression(){
    vector<string>::iterator save = it;
    bool result = terminal("INT_LITERAL") && expression1();
    return result;
}

bool Validator::expression1(){
    return endOfExpr()
        || terminal("+") && terminal("INT_LITERAL") && expression1();
}
