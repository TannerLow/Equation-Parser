#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <string>
#include <vector>

//Recursive descent parser for checking validity of expressions
class Validator
{
    public:
        Validator(std::vector<std::string> Tokens);
        Validator(std::vector<std::string> Tokens, std::vector<std::string>::iterator start);
        bool expression();
    private:
        bool endOfExpr();
        bool terminal(std::string token);
        bool expression1();
        bool expression2();
        //Variables
        std::vector<std::string> tokens;
        std::vector<std::string>::iterator it;
        bool empty = true;
};

#endif // VALIDATOR_H
