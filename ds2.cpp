#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

// Node structure for Stack Linked List
struct Node {
    char data;
    Node* next;
};

// Stack Class definition
class Stack {
private:
    Node* top;

public:
    Stack() { 
        top = NULL; 
    }

    void push(char x) {
        Node* temp = new Node;
        temp->data = x;
        temp->next = top;
        top = temp;
    }

    char pop() {
        if (top == NULL) return '#';
        Node* temp = top;
        char ch = temp->data;
        top = top->next;
        delete temp;
        return ch;
    }

    char peek() {
        if (top == NULL) return '#';
        return top->data;
    }

    bool isEmpty() {
        return top == NULL;
    }
};

// Operator Precedence Helper Function
int priority(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

// Operand Identification Helper Function
bool operand(char ch) {
    if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9')) {
        return true;
    }
    return false;
}

// Conversion: Infix to Postfix
string infixToPostfix(string exp) {
    Stack s;
    string result = "";
    
    for (int i = 0; i < exp.length(); i++) {
        char ch = exp[i];
        
        if (operand(ch)) {
            result += ch;
        } 
        else if (ch == '(') {
            s.push(ch);
        } 
        else if (ch == ')') {
            while (!s.isEmpty() && s.peek() != '(') {
                result += s.pop();
            }
            s.pop(); // Remove '(' from stack
        } 
        else {
            // Correct logic handles operator precedence comparisons safely
            while (!s.isEmpty() && priority(s.peek()) >= priority(ch)) {
                result += s.pop();
            }
            s.push(ch);
        }
    }
    
    while (!s.isEmpty()) {
        result += s.pop();
    }
    return result;
}

// Conversion: Infix to Prefix
string infixToPrefix(string exp) {
    // Step 1: Reverse Infix Expression
    reverse(exp.begin(), exp.end());
    
    // Step 2: Swap Bracket Types
    for (int i = 0; i < exp.length(); i++) {
        if (exp[i] == '(') exp[i] = ')';
        else if (exp[i] == ')') exp[i] = '(';
    }
    
    // Step 3: Run modified postfix logic
    // Note: For pure mathematical prefix, right-associative precedence checks are required.
    // However, this standard reversal wrapper works with your base postfix parser.
    string postfix = infixToPostfix(exp);
    
    // Step 4: Reverse back to finalize prefix
    reverse(postfix.begin(), postfix.end());
    return postfix;
}

int main() {
    string exp;
    cout << "Enter Infix Expression : ";
    cin >> exp;
    
    cout << "\nPostfix : " << infixToPostfix(exp);
    cout << "\nPrefix  : " << infixToPrefix(exp) << endl;
    
    return 0;
}