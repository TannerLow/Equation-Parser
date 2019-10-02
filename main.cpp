#include <iostream>
#include <stack>
#include <string>
int getPrec(char c){
    switch(c){
    case '+': return 0;
    case '-': return 0;
    case '*': return 1;
    case '/': return 1;
    case '^': return 2;
    default : return -1;
    }
}

void pushToStack(std::string &v, std::stack<char> &s, char c){
    if(c == ')'){
        while(s.top() != '('){
            char tmp = s.top();
            s.pop();
            v.push_back(tmp);
        }
        s.pop();
    }
    else if(c == '(' || !s.empty() && s.top() == '('){
        s.push(c);
    }
    else{
        while(!s.empty() && getPrec(s.top()) >= getPrec(c)){
            char tmp = s.top();
            s.pop();
            v.push_back(tmp);
        }
        s.push(c);
    }
}

void eqToPostfix(std::string input){
    std::stack<char> operators;
    std::string postfix;

    for(int i = 0; i < input.size(); i++){
        char c = input[i];
        if(c >= '0' && c <= '9') postfix.push_back(c);
        else{
            pushToStack(postfix,operators,c);
        }
    }
    while(!operators.empty()){
        char tmp = operators.top();
        operators.pop();
        postfix.push_back(tmp);
    }

    std::cout << postfix << std::endl;
}

int main(){
    std::string in;
    while(true){
        std::cin >> in;
        if(in == "exit") return 0;
        eqToPostfix(in);
    }
    return 0;
}
