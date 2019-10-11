#include <iostream>
#include <stack>
#include <string>
#include <vector>

int getPrec(std::string s){
    if     (s == "+") return 0;
    else if(s == "-") return 0;
    else if(s == "*") return 1;
    else if(s == "/") return 1;
    else if(s == "^") return 2;
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

void eqToPostfix(std::vector<std::string> input){
    std::stack<std::string> operators;
    std::vector<std::string> postfix;

    for(int i = 0; i < input.size(); i++){
        char c = input[i][0];
        if(c >= '0' && c <= '9') postfix.push_back(input[i]);
        else{
            pushToStack(postfix,operators,input[i]);
        }
    }
    while(!operators.empty()){
        std::string tmp = operators.top();
        operators.pop();
        postfix.push_back(tmp);
    }

    for(int i = 0; i < postfix.size(); i++)
        std::cout << postfix[i] << " ";
    std::cout << std::endl;
}

void tokenizeHelper(std::string &current, std::vector<std::string> &tokens, char c){
    if(current.size() > 0){
        tokens.push_back(current);
        current = "";
    }
    tokens.push_back(std::string(1,c));
}

std::vector<std::string> tokenize(std::string s){
    std::vector<std::string> tokens;
    std::string currentToken = "";
    for(int i = 0; i < s.size(); i++){
        char c = s[i];
        switch(c){
        case '+': tokenizeHelper(currentToken,tokens,c); break;
        case '-': tokenizeHelper(currentToken,tokens,c); break;
        case '*': tokenizeHelper(currentToken,tokens,c); break;
        case '/': tokenizeHelper(currentToken,tokens,c); break;
        case '^': tokenizeHelper(currentToken,tokens,c); break;
        case '(': tokenizeHelper(currentToken,tokens,c); break;
        case ')': tokenizeHelper(currentToken,tokens,c); break;
        default : currentToken += c;                     break;
        }
    }
    if(currentToken.size() > 0)
        tokens.push_back(currentToken);
    return tokens;
}

int main(){
    std::string in;
    while(true){
        std::cin >> in;
        std::vector<std::string> tokens = tokenize(in);
        /*for(int i = 0; i < tokens.size(); i++){
            std::cout << tokens[i] << std::endl;
        }*/
        if(in == "exit") return 0;
        eqToPostfix(tokens);
    }
    return 0;
}
