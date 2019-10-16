#include <iostream>
#include "helper.h"

/*Helper functions referred to by the driver
 *code are located in the helper.h file.
 */

int main(){
    typedef std::vector<std::string> vector;
    std::string in;
    while(true){
        //User Input
        std::getline(std::cin, in);
        vector tokens = tokenize(in);
        if(in == "exit") return 0; //terminates program

        //Print categorized tokens of original expression
        vector lexxed = lex(tokens);
        for(int i = 0; i < lexxed.size(); i++)
            std::cout << lexxed[i] << " ";
        std::cout << std::endl;

        //Print expression in postfix notation
        vector postfix = eqToPostfix(tokens);
        if(postfix.size() > 0){
            for(int i = 0; i < postfix.size()-1; i++)
                std::cout << postfix[i] << " ";
            std::cout << postfix[postfix.size()-1] << std::endl;
        }

        //Print categorized tokens of postfix expression
        lexxed = lex(postfix);
        if(lexxed.size() > 0){
            for(int i = 0; i < lexxed.size()-1; i++)
                std::cout << lexxed[i] << " ";
            std::cout << lexxed[lexxed.size()-1] << std::endl;
        }
    }
    return 0;
}
