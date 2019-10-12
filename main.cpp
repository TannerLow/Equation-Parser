#include <iostream>
#include <stack>
#include <string>
#include <vector>

bool isLetter(char c) {
    return (c >= 'a' && c <= 'z');
}

bool isNumber(char c){
    return (c >= '0' && c <= '9');
}

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

std::vector<std::string> eqToPostfix(std::vector<std::string> input){
    std::stack<std::string> operators;
    std::vector<std::string> postfix;

    for(int i = 0; i < input.size(); i++){
        char c = input[i][0];
        if(isNumber(c) || isLetter(c)) postfix.push_back(input[i]);
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

void tokenizeHelper(std::string &current, std::vector<std::string> &tokens, char c){
    if(current.size() > 0){
        tokens.push_back(current);
        current = "";
    }
    tokens.push_back(std::string(1,c));
}

void tokenizeHelper(std::string &current, std::vector<std::string> &tokens, std::string s){
    if(current.size() > 0){
        tokens.push_back(current);
        current = "";
        tokens.push_back(s);
    }
}

std::string combine(char c, char d){
    std::string s = "  ";
    s[0] = c, s[1] = d;
    return s;
}

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

std::vector<std::string> lex(std::vector<std::string> tokens){
    std::vector<std::string> lexxed;
    enum type {INT_LITERAL, IDENTIFIER, INVALID_TOKEN, UNIDENTIFIED};

    for(int i = 0; i < tokens.size(); i++){
        bool invalid = false;
        type current = UNIDENTIFIED;
        for(int j = 0; j < tokens[i].size(); j++){
            if(invalid) break;
            char c = tokens[i][j];
            switch(current){
            case INVALID_TOKEN:
                lexxed.push_back("InvalidToken");
                invalid = true;
                break;
            case UNIDENTIFIED:
                if     (isNumber(c)) current = INT_LITERAL;
                else if(isLetter(c)) current = IDENTIFIER;
                break;
            case INT_LITERAL:
                if(!isNumber(c)) current = INVALID_TOKEN;
                break;
            default: break;
            }
        }
        switch(current){
        case INVALID_TOKEN:
            if(!invalid) lexxed.push_back("InvalidToken");
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

int main(){
    typedef std::vector<std::string> vector;
    std::string in;
    while(true){
        std::getline(std::cin, in);
        vector tokens = tokenize(in);
        if(in == "exit") return 0; //terminates program

        vector lexxed = lex(tokens);
        for(int i = 0; i < lexxed.size(); i++)
            std::cout << lexxed[i] << " ";
        std::cout << std::endl;

        vector postfix = eqToPostfix(tokens);
        if(postfix.size() > 0){
            for(int i = 0; i < postfix.size()-1; i++)
                std::cout << postfix[i] << " ";
            std::cout << postfix[postfix.size()-1] << std::endl;
        }

        lexxed = lex(postfix);
        if(lexxed.size() > 0){
            for(int i = 0; i < lexxed.size()-1; i++)
                std::cout << lexxed[i] << " ";
            std::cout << lexxed[lexxed.size()-1] << std::endl;
        }
    }
    return 0;
}
