
/*
How to compile:  gcc Calculator.c -o Calculator 

How to use calculator:
enter one digit, the operation, then the next digit. 
*/

#include <stdio.h>
#include "calc.h"

double add(double a, double b) {
    return a + b;
}

double subtract(double a, double b) {
    return a - b;
}

double multiply(double a, double b) {
    return a * b;
}

double divide(double a, double b) {
    if (b == 0.0) {
        printf("Error\n");
        return 0.0; 
    }
    return a / b;
}

int main(void) {
    double num1, num2, result;
    char op;

    printf("Simple Calculator\n");
    printf("Enter first number: ");
    if (scanf("%lf", &num1) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    printf("Enter operator (+, -, *, /): ");
    if (scanf(" %c", &op) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    printf("Enter second number: ");
    if (scanf("%lf", &num2) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    switch (op) {
        case '+':
            result = add(num1, num2);
            break;
        case '-':
            result = subtract(num1, num2);
            break;
        case '*':
        case 'x':
        case 'X':
            result = multiply(num1, num2);
            break;
        case '/':
            result = divide(num1, num2);
            break;
        default:
            printf("Error: Unsupported operator '%c'.\n", op);
            return 1;
    }

    printf("Result: %.6g\n", result);  // %.6g gives clean output for most cases
    return 0;
}