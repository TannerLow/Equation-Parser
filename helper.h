#ifndef HELPER_H_INCLUDED
#define HELPER_H_INCLUDED

#include <stack>
#include <string>
#include <vector>

bool isLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool isNumber(char c){
    return (c >= '0' && c <= '9');
}

bool isQuotation(char c){
    return (c == '\"');
}

/*
 *Gives precedent level of a string.
 *EX. ^ takes precedent over * and takes precedent over +
 *Non-operator strings return -1. Other negative values
 *are reserved for things like parentheses.
 */
int getPrec(std::string s){
         if(s == "+") return 12;
    else if(s == "-") return 12;
    else if(s == "*") return 13;
    else if(s == "/") return 13;
    else if(s == "%") return 13;
    else if(s == "^") return 14;
    else if(s == "=") return  2;
    else if(s == "+=")return  2;
    else if(s == "-=")return  2;
    else if(s == "*=")return  2;
    else if(s == "/=")return  2;
    else if(s == "%=")return  2;
    else if(s == "(") return -2;//artificial precedence to
    else if(s == ")") return -2;//work with lex function
    else              return -1;
}

/*
 *Places the given token in the stack. Pops elements from stack to
 *vector according to the token in order to create a postfix
 *vector.
 */
void pushToStack(std::vector<std::string> &v, std::stack<std::string> &s, std::string token){
    if(token == ")"){
        while(s.top() != "("){
            std::string tmp = s.top();
            s.pop();
            v.push_back(tmp);
        }
        s.pop();
    }
    else if(token == "(" || !s.empty() && s.top() == "("){
        s.push(token);
    }
    else{
        while(!s.empty() && getPrec(s.top()) >= getPrec(token)){
            std::string tmp = s.top();
            s.pop();
            v.push_back(tmp);
        }
        s.push(token);
    }
}

/*
 *Parses input vector in order to create a vector of the same
 *tokens but in postfix order. EX. this,+,that,*,those converts
 *to this,that,those,*,+.
 */
std::vector<std::string> eqToPostfix(std::vector<std::string> input){
    std::stack<std::string> operators;
    std::vector<std::string> postfix;

    for(int i = 0; i < input.size(); i++){
        char c = input[i][0];
        if(isNumber(c) || isLetter(c) || isQuotation(c)) postfix.push_back(input[i]);
        else{
            pushToStack(postfix,operators,input[i]);
        }
    }
    while(!operators.empty()){
        std::string tmp = operators.top();
        operators.pop();
        postfix.push_back(tmp);
    }

   return postfix;
}

/*
 *Converts char c to a string token and appends it
 *to the vector of tokens.
 */
void tokenizeHelper(std::string &current, std::vector<std::string> &tokens, char c){
    if(current.size() > 0){
        tokens.push_back(current);
        current = "";
    }
    tokens.push_back(std::string(1,c));
}


//Appends string s to vector of tokens.
void tokenizeHelper(std::string &current, std::vector<std::string> &tokens, std::string s){
    if(current.size() > 0){
        tokens.push_back(current);
        current = "";
    }
    tokens.push_back(s);
}

std::string combine(char c, char d){
    std::string s = "  ";
    s[0] = c, s[1] = d;
    return s;
}

/*
 *Breaks a string into a vector of tokens. Ignores whitespace
 *and splits a based on operators. EX. this= those +that
 *gets tokenized into this,=,those,+,that
 */
std::vector<std::string> tokenize(std::string s){
    std::vector<std::string> tokens;
    std::string currentToken = "";
    for(int i = 0; i < s.size(); i++){
        std::string cAndD = "";
        char c = s[i], d;
        if(i < s.size()-1) {
            d = s[i+1];
            cAndD = combine(c,d);
        }
        i++;
             if(cAndD == "+=") tokenizeHelper(currentToken,tokens,cAndD);
        else if(cAndD == "-=") tokenizeHelper(currentToken,tokens,cAndD);
        else if(cAndD == "*=") tokenizeHelper(currentToken,tokens,cAndD);
        else if(cAndD == "/=") tokenizeHelper(currentToken,tokens,cAndD);
        else if(cAndD == "%=") tokenizeHelper(currentToken,tokens,cAndD);
        else{
            switch(c){
            case '+': tokenizeHelper(currentToken,tokens,c); break;
            case '-': tokenizeHelper(currentToken,tokens,c); break;
            case '*': tokenizeHelper(currentToken,tokens,c); break;
            case '/': tokenizeHelper(currentToken,tokens,c); break;
            case '%': tokenizeHelper(currentToken,tokens,c); break;
            case '^': tokenizeHelper(currentToken,tokens,c); break;
            case '=': tokenizeHelper(currentToken,tokens,c); break;
            case '(': tokenizeHelper(currentToken,tokens,c); break;
            case ')': tokenizeHelper(currentToken,tokens,c); break;
            case ' ':                                        break;
            default : currentToken += c;                     break;
            }
            i--;
        }
    }
    if(currentToken.size() > 0)
        tokens.push_back(currentToken);
    return tokens;
}

/*
 *Categorizes the tokens if the input vector.
 *EX. 123 -> INT_LITERAL, name -> Identifier.
 *Operators are handled as UNIDENTIFIED but categorized as
 *their own type.
 *EX. this + that -> Identifier + Identifier. Operators are unchanged.
 */
std::vector<std::string> lex(std::vector<std::string> tokens){
    std::vector<std::string> lexxed;
    enum type {INT_LITERAL,STR_LITERAL, IDENTIFIER, INVALID_TOKEN, UNIDENTIFIED};

    for(int i = 0; i < tokens.size(); i++){
        bool invalid = false, skip = false;
        type current = UNIDENTIFIED;
        for(int j = 0; j < tokens[i].size(); j++){
            if(invalid) break; //Token marked as invalid
            if(skip)    break; //Process can be skipped
            char c = tokens[i][j];
            switch(current){
            case INVALID_TOKEN:
                lexxed.push_back("Invalid_Token");
                invalid = true;
                break;
            case UNIDENTIFIED:
                if     (isNumber(c))   current = INT_LITERAL;
                else if(isLetter(c))   current = IDENTIFIER ;
                else if(isQuotation(c))current = STR_LITERAL;
                break;
            case INT_LITERAL:
                if(!isNumber(c)) current = INVALID_TOKEN;
                break;
            case STR_LITERAL:
                //check if ends in quotation mark
                if(isQuotation(tokens[i][tokens[i].size()-1])) skip = true;
                else current = INVALID_TOKEN;
            default: break;
            }
        }
        switch(current){
        case INVALID_TOKEN:
            if(!invalid) lexxed.push_back("Invalid_Token");
            break;
        case UNIDENTIFIED:
            if(getPrec(tokens[i]) != -1)
                lexxed.push_back(tokens[i]);
            else
                lexxed.push_back("Unidentified");
            break;
        case INT_LITERAL:
            lexxed.push_back("INT_LITERAL");
            break;
        case STR_LITERAL:
            lexxed.push_back("STR_LITERAL");
            break;
        case IDENTIFIER:
            lexxed.push_back("Identifier");
            break;
        default:
            lexxed.push_back(tokens[i]);
            break;
        }
    }
    return lexxed;
}

#endif // HELPER_H_INCLUDED
