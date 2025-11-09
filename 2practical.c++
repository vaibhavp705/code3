2. Stack

#include <iostream>
#include <stack>
#include <string>
#include <algorithm>
using namespace std;

// Node structure for linked list stack
struct Node {
    char data;
    Node* next;
};

class Stack {
private:
    Node* top;
public:
    Stack() { top = NULL; }

    bool isEmpty() { return top == NULL; }

    void push(char x) {
        Node* temp = new Node();
        temp->data = x;
        temp->next = top;
        top = temp;
    }

    char pop() {
        if (isEmpty()) return '\0';
        Node* temp = top;
        char x = temp->data;
        top = top->next;
        delete temp;
        return x;
    }

    char peek() {
        if (isEmpty()) return '\0';
        return top->data;
    }
};

// precedence function
int precedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return -1;
}

// check if operand
bool isOperand(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (isdigit(c));
}

// Infix ? Postfix
string infixToPostfix(string infix) {
    Stack st;
    string postfix = "";
    for (char c : infix) {
        if (isOperand(c)) {
            postfix += c;
        } else if (c == '(') {
            st.push(c);
        } else if (c == ')') {
            while (!st.isEmpty() && st.peek() != '(') {
                postfix += st.pop();
            }
            st.pop(); // remove '('
        } else { // operator
            while (!st.isEmpty() && precedence(st.peek()) >= precedence(c)) {
                postfix += st.pop();
            }
            st.push(c);
        }
    }
    while (!st.isEmpty()) {
        postfix += st.pop();
    }
    return postfix;
}

// Infix ? Prefix
string infixToPrefix(string infix) {
    // reverse infix
    reverse(infix.begin(), infix.end());
    for (int i = 0; i < (int)infix.size(); i++) {
        if (infix[i] == '(') infix[i] = ')';
        else if (infix[i] == ')') infix[i] = '(';
    }
    // get postfix of reversed
    string postfix = infixToPostfix(infix);
    // reverse postfix ? prefix
    reverse(postfix.begin(), postfix.end());
    return postfix;
}

// Main function
int main() {
    string infix;
    cout << "Enter Infix Expression: ";
    cin >> infix;

    string postfix = infixToPostfix(infix);
    string prefix = infixToPrefix(infix);

    cout << "Infix   : " << infix << endl;
    cout << "Postfix : " << postfix << endl;
    cout << "Prefix  : " << prefix << endl;

    return 0;
}

Output:
 
