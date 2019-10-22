#include <iostream>
#include "helper.h"
#include "Validator.h"

/*Helper functions referred to by the driver
 *code are located in the helper.h file.
 */

using namespace helper;
using namespace std;

int main(){
    typedef vector<string> vector;
    //Validator test, check if an expression is valid
    string test = "123 + (90 *12) +17";
    vector testTokens = tokenize(test);
    vector testLexxed = lex(testTokens);
    for(int i = 0; i < testLexxed.size(); i++)
        cout << testLexxed[i] << " ";
    cout << endl;
    Validator v(testLexxed);
    cout << ((v.expression()) ? "true" : "false") << endl;

    return 0;

    //helper functions test
    string in;
    while(true){
        //User Input
        getline(cin, in);
        if(in == "exit") return 0; //terminates program
        vector tokens = tokenize(in);
        cout << "        Tokens: ";
        for(int i = 0; i < tokens.size()-1; i++)
            cout << tokens[i] << " ";
        cout << tokens[tokens.size()-1] << endl;

        //Print categorized tokens of original expression
        vector lexxed = lex(tokens);
        cout << "        Lexxed: ";
        for(int i = 0; i < lexxed.size(); i++)
            cout << lexxed[i] << " ";
        cout << endl;

        //Print expression in postfix notation
        vector postfix = exprToPostfix(tokens);
        cout << "       Postfix: ";
        if(postfix.size() > 0){
            for(int i = 0; i < postfix.size()-1; i++)
                cout << postfix[i] << " ";
            cout << postfix[postfix.size()-1] << endl;
        }

        //Print categorized tokens of postfix expression
        lexxed = lex(postfix);
        if(lexxed.size() > 0){
            cout << "Lexxed Postfix: ";
            for(int i = 0; i < lexxed.size()-1; i++)
                cout << lexxed[i] << " ";
            cout << lexxed[lexxed.size()-1] << endl;
        }
    }
    return 0;
}
