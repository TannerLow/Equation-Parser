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
        void reset(std::vector<std::string> Tokens);
        bool expression(std::string endToken);
        bool expression();
        bool statement();
        bool function();
        bool library();
    private:
        bool endOfExpr();
        bool terminal(std::string token);
        bool statement1();
        bool expression1();
        bool expression2();
        bool expression3();
        bool expression4();
        //Variables
        std::vector<std::string> tokens;
        std::vector<std::string>::iterator it;
        bool empty = true;
};

#endif // VALIDATOR_H
