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
    vector<string>::iterator save = it;
    return (it = save, expression1() && endOfExpr())
        || (it = save, terminal("Identifier") && expression4() && endOfExpr());
}

bool Validator::expression1(){
    return expression2() && expression3();
}

bool Validator::expression2(){
    if     (terminal("INT_LITERAL")) return true;
    else if(terminal("Identifier"))  return true;
    else if(terminal("("))           return expression1() && terminal(")");
    else                             return false;
}

bool Validator::expression3(){
    if     (terminal("+")) return expression1();
    else if(terminal("-")) return expression1();
    else if(terminal("*")) return expression1();
    else if(terminal("/")) return expression1();
    else if(terminal("%")) return expression1();
    else                   return true;
}

bool Validator::expression4(){
    if     (terminal("=") ) return expression1();
    else if(terminal("+=")) return expression1();
    else if(terminal("-=")) return expression1();
    else if(terminal("*=")) return expression1();
    else if(terminal("/=")) return expression1();
    else if(terminal("%=")) return expression1();
    else                    return false;
}
