#include <iostream>
#include <stack>
#include <string>
#include <fstream>

using namespace std;

bool isDelimiter(const char&ch);
void delimChecker(const string s);
char match(char a);

int main(int argc, char *argv[]) {
    stack<char> stks;
    char ch;
    string delimiters;
    
    if(argc!=2) {
        cout << "usage: " << argv[0]<< "<input file>" << endl;
    }
    ifstream inFile(argv[1]);
    
    if (!inFile)
    {
        cout << "Error opening input file " << argv[1] << endl;
        exit(1);
    }
    
    /* Read in each character */
    while(inFile >> ch) {
        if(isDelimiter(ch)) {
            delimiters+=ch;
        }
    }
    
    delimChecker(delimiters);
    inFile.close();
    
    return 0;
}

/* Checks if input is a delimiter */
bool isDelimiter(const char&ch) {
    char delims[] = {'{', '}', '(', ')', '[', ']'};
    
    for(int i=0; i < 6; i++)
    {
        if(ch == delims[i])
            return true;
    }
    
    return false;
}

/* Main function for checking the delimiters match */
void delimChecker(string str) {
    stack<char> delims;
    char ch;
    
    for (int i=0; i < str.length(); i++) {
        switch (str[i]) {
                /* Push delimiter unto stack only if it's an opening */
            case '{':
            case '(':
            case '[':
                delims.push(str[i]);
                break;
            case '}':
                if (!delims.empty() && (delims.top() != '{')) {
                    cout << "Mismatched delimiter } found. Expecting delimiter " << match(delims.top()) << "." << endl;
                    return;
                }
                else if(delims.empty()) {
                    cout << "Extra delimiter " << str[i] << " found." << endl;
                    return;
                }
                delims.pop();
                break;
                
            case ')':
                if (!delims.empty() && (delims.top() != '(')) {
                    cout << "Mismatched delimiter ) found. Expecting delimiter "<<  match(delims.top()) << "." << endl;
                    return;
                }
                else if(delims.empty()) {
                    cout << "Extra delimiter " <<str[i] << " found." << endl;
                    return;
                }
                delims.pop();
                break;
                
            case ']':
                if (!delims.empty() && (delims.top() != '[')) {
                    cout << "Mismatched delimiter ] found. Expecting delimiter "<<  match(delims.top()) << "." << endl;
                    return;
                }
                else if(delims.empty()) {
                    cout << "Extra delimiter " <<str[i] << " found." << endl;
                    return;
                }
                delims.pop();
                break;
        }
    }
    
    if(!delims.empty()) {
        cout << "Extra delimiter " << delims.top() << " found." << endl;
        return;
    }
    
    cout << "All delimiters match." << endl;
    
}

/* Returns the expected closing of the delimiter at the top of the stack */
char match(char a) {
    char ch;
    if(a=='{') {
        ch = '}';
    }
    else if(a=='[') {
        ch = ']';
    }
    else {
        ch = ')';
    }
    
    return ch;
}
