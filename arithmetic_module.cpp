/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/
#include <iostream>
#include <stack>
#include <string>

using namespace std;

int evaluateExpression(char* expression) {
    stack<int> operandStack;
    stack<char> operatorStack;

    for (int i = 0; expression[i] != '\0'; i++) {
        if (expression[i] == ' ') {
            continue;
        }
        else if (isdigit(expression[i])) {
            int operand = 0;
            while (isdigit(expression[i])) {
                operand = (operand * 10) + (expression[i] - '0');
                i++;
            }
            i--;
            operandStack.push(operand);
        }
        else if (expression[i] == '(') {
            operatorStack.push(expression[i]);
        }
        else if (expression[i] == ')') {
            while (operatorStack.top() != '(') {
                int operand2 = operandStack.top();
                operandStack.pop();
                int operand1 = operandStack.top();
                operandStack.pop();
                char op = operatorStack.top();
                operatorStack.pop();
                int result;
                switch (op) {
                    case '+':
                        result = operand1 + operand2;
                        break;
                    case '-':
                        result = operand1 - operand2;
                        break;
                    case '*':
                        result = operand1 * operand2;
                        break;
                    case '/':
                        result = operand1 / operand2;
                        break;
                }
                operandStack.push(result);
            }
            operatorStack.pop();
        }
        else {
            while (!operatorStack.empty() && operatorStack.top() != '(' && ((expression[i] == '*' || expression[i] == '/') || (expression[i] == '+' || expression[i] == '-') && (operatorStack.top() == '+' || operatorStack.top() == '-'))) {
                int operand2 = operandStack.top();
                operandStack.pop();
                int operand1 = operandStack.top();
                operandStack.pop();
                char op = operatorStack.top();
                operatorStack.pop();
                int result;
                switch (op) {
                    case '+':
                        result = operand1 + operand2;
                        break;
                    case '-':
                        result = operand1 - operand2;
                        break;
                    case '*':
                        result = operand1 * operand2;
                        break;
                    case '/':
                        result = operand1 / operand2;
                        break;
                }
                operandStack.push(result);
            }
            operatorStack.push(expression[i]);
        }
    }

    while (!operatorStack.empty()) {
        int operand2 = operandStack.top();
        operandStack.pop();
        int operand1 = operandStack.top();
        operandStack.pop();
        char op = operatorStack.top();
        operatorStack.pop();
        int result;
        switch (op) {
            case '+':
                result = operand1 + operand2;
                break;
            case '-':
                result = operand1 - operand2;
                break;
            case '*':
                result = operand1 * operand2;
                break;
            case '/':
                result = operand1 / operand2;
                break;
        }
        operandStack.push(result);
    }

    return operandStack.top();
}


double evaluateExpression_Double(char* expression) {
    stack<double> operandStack;
    stack<char> operatorStack;

    for (int i = 0; expression[i] != '\0'; i++) {
        if (expression[i] == ' ') {
            continue;
        }
        else if (isdigit(expression[i])) {
            double operand = 0;
            while (isdigit(expression[i])) {
                operand = (operand * 10) + (expression[i] - '0');
                i++;
            }
            if (expression[i] == '.') {
                i++;
                double fraction = 1;
                while (isdigit(expression[i])) {
                    fraction /= 10;
                    operand += (expression[i] - '0') * fraction;
                    i++;
                }
            }
            i--;
            operandStack.push(operand);
        }
        else if (expression[i] == '(') {
            operatorStack.push(expression[i]);
        }
        else if (expression[i] == ')') {
            while (operatorStack.top() != '(') {
                double operand2 = operandStack.top();
                operandStack.pop();
                double operand1 = operandStack.top();
                operandStack.pop();
                char op = operatorStack.top();
                operatorStack.pop();
                double result;
                switch (op) {
                case '+':
                    result = operand1 + operand2;
                    break;
                case '-':
                    result = operand1 - operand2;
                    break;
                case '*':
                    result = operand1 * operand2;
                    break;
                case '/':
                    result = operand1 / operand2;
                    break;
                }
                operandStack.push(result);
            }
            operatorStack.pop();
        }
        else {
            while (!operatorStack.empty() && operatorStack.top() != '(' && ((expression[i] == '*' || expression[i] == '/') || (expression[i] == '+' || expression[i] == '-') && (operatorStack.top() == '+' || operatorStack.top() == '-'))) {
                double operand2 = operandStack.top();
                operandStack.pop();
                double operand1 = operandStack.top();
                operandStack.pop();
                char op = operatorStack.top();
                operatorStack.pop();
                double result;
                switch (op) {
                case '+':
                    result = operand1 + operand2;
                    break;
                case '-':
                    result = operand1 - operand2;
                    break;
                case '*':
                    result = operand1 * operand2;
                    break;
                case '/':
                    result = operand1 / operand2;
                    break;
                }
                operandStack.push(result);
            }
            operatorStack.push(expression[i]);
        }
    }

    while (!operatorStack.empty()) {
        double operand2 = operandStack.top();
        operandStack.pop();
        double operand1 = operandStack.top();
        operandStack.pop();
        char op = operatorStack.top();
        operatorStack.pop();
        double result;
        switch (op) {
        case '+':
            result = operand1 + operand2;
            break;
        case '-':
            result = operand1 - operand2;
            break;
        case '*':
            result = operand1 * operand2;
            break;
        case '/':
            result = operand1 / operand2;
            break;
        }
        operandStack.push(result);
    }

    return operandStack.top();
}

int test() {
    char expression[] = "(((2+2)+(2*2))/4)*223344";
    int result = evaluateExpression(expression);
    cout << "Result: " << result << endl;
    return 0;
}