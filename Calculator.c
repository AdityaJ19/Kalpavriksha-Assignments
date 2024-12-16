#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to perform the arithmetic operation
int performOperation(int a, int b, char op) {
    if (op == '+') return a + b;
    if (op == '-') return a - b;
    if (op == '*') return a * b;
    if (op == '/') {
        if (b == 0) {
            printf("Division by zero.\n");
            return 0; // Return 0 on division by zero
        }
        return a / b;
    }
    return 0;
}

// Function to evaluate mathematical expression
int evaluate(char *expr) {
    int numbers[100], numstk = -1;
    char operators[100], opstk = -1;
    int currNum = 0;
    int i = 0, expLen = strlen(expr);

    // Process each character in the expression
    while (i < expLen) {
        char ch = expr[i];

        if (isspace(ch)) {
            // Ignore whitespace
            i++;
            continue;
        }

        if (isdigit(ch)) {
            
            currNum = 0;
            while (i < expLen && isdigit(expr[i])) {
                currNum = currNum * 10 + (expr[i] - '0');
                i++;
            }
            numbers[++numstk] = currNum; // Push the number in the stack
            continue;
        }

        if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            // Process operators based on precedence
            while (opstk >= 0 && (
                (ch == '+' || ch == '-') || 
                (operators[opstk] == '*' || operators[opstk] == '/'))) {
                int b = numbers[numstk--];
                int a = numbers[numstk--];
                char op = operators[opstk--];
                numbers[++numstk] = performOperation(a, b, op);
            }
            operators[++opstk] = ch; // Push the current operator
        } else {
            printf("Invalid character '%c' in expression.\n", ch);
            return 0;
        }

        i++;
    }

    // Process any remaining operators
    while (opstk >= 0) {
        int b = numbers[numstk--];
        int a = numbers[numstk--];
        char op = operators[opstk--];
        numbers[++numstk] = performOperation(a, b, op);
    }

    return numbers[numstk];
}

// Function to remove whitespace from the expression
void rmvWhiteSpace(char *expr) {
    int i = 0, j = 0;
    while (expr[i] != '\0') {
        if (!isspace(expr[i])) {
            expr[j++] = expr[i];
        }
        i++;
    }
    expr[j] = '\0';
}

// Function to validate the expression
int isValidExpression(char *expr) {
    int len = strlen(expr);
    int prevWasOperator = 1; // Start with 1 to disallow starting with an operator

    for (int i = 0; i < len; i++) {
        char ch = expr[i];

        if (isspace(ch)) continue;

        if (isdigit(ch)) {
            prevWasOperator = 0; // Mark as valid operand
        } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            if (prevWasOperator) {
                printf("Consecutive operators or invalid start.\n");
                return 0;
            }
            prevWasOperator = 1; // Mark as operator
        } else {
            printf("Invalid character '%c' in expression.\n", ch);
            return 0;
        }
    }

    if (prevWasOperator) {
        printf("Expression cannot end with an operator.\n");
        return 0;
    }

    return 1;
}

int main() {
    char expr[100];

    // Enter a mathematical expression
    printf("Enter a mathematical expression: ");
    fgets(expr, sizeof(expr), stdin);

    expr[strcspn(expr, "\n")] = '\0';

    // Remove whitespaces
    rmvWhiteSpace(expr);

    if (strlen(expr) == 0) {
        printf("Input cannot be empty.\n");
        return 0;
    }

    // check if the expression is right or not
    if (!isValidExpression(expr)) {
        printf("Invalid expression.\n");
        return 0;
    }

    int result = evaluate(expr);
    printf("Result: %d\n", result);

    return 0;
}
