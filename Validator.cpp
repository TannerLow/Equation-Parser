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
    return it >= tokens.end();
}

bool Validator::terminal(string token){
    if(*it++ == token) return true;
    else it--;
        return false;
}

bool Validator::expression(){
    return expression1() && expression2();
}

bool Validator::expression1(){
    vector<string>::iterator save = it;
    if     (it = save, terminal("INT_LITERAL")) return true;
    else if(it = save, terminal("Identifier"))  return true;
    else if(it = save, terminal("("))           return expression() && terminal(")");
    else                                        return false;
}

bool Validator::expression2(){
    vector<string>::iterator save = it;
    if     (it = save, terminal("+")) return expression1() && expression2();
    else if(it = save, terminal("-")) return expression1() && expression2();
    else if(it = save, terminal("*")) return expression1() && expression2();
    else if(it = save, terminal("/")) return expression1() && expression2();
    else if(it = save, terminal("%")) return expression1() && expression2();
    else                              return true;
}
