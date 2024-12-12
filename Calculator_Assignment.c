#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Evaluate the mathematical expression and returns the result.
int evaluate(char *expr) {
    int i; //index
    int expLen = strlen(expr); //length of the expression
    int currNum;
    int op = 0;
    int numSign = 1; //it basically tells us whether the number is +ve(1) or-ve(0)
    char currOp = '+';

    // Iterate through each character of the expression.
    for (i = 0; i < expLen; i++) {
        // If the current character is a digit, parse the number.
        if (isdigit(expr[i])) {
            currNum = 0;
            while (i < expLen && isdigit(expr[i])) {
                currNum = currNum * 10 + (expr[i] - '0');
                i++;
            }
            i--;

            // Perform the appropriate arithmetic operation based on the current operator.
            switch (currOp) {
                case '+':
                    op += numSign * currNum;
                    break;
                case '-':
                    op -= numSign * currNum;
                    break;
                case '*':
                    op *= numSign * currNum;
                    break;
                case '/':
                    if (currNum == 0) {
                        printf("Error: Division by zero.\n");
                        return 0;
                    }
                    op += (int)(numSign * op / currNum);
                    break;
            }
        } 
        // Handle positive or negative numbers.
        else if (expr[i] == '+' || expr[i] == '-') {
            numSign = (expr[i] == '-') ? -1 : 1;
        } 
        // Update the current operator for multiplication or division.
        else if (expr[i] == '*' || expr[i] == '/') {
            currOp = expr[i];
        } 
        // Handle invalid characters.
        else if (!isspace(expr[i])) {
            printf("Error: Invalid expression.\n");
            return 0;
        }
    }

    return op;
}

int main() {
    char expr[100];

    // Prompt the user to enter a mathematical expression.
    printf("Enter a mathematical expression: ");
    fgets(expr, sizeof(expr), stdin);

    // Evaluate the expression and print the result or an error message.
    int result = evaluate(expr);
    if (result != 0) {
        printf("Result: %d\n", result);
    }

    return 0;
}