#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct {
    char items[MAX_SIZE];
    int top;
} Stack;

void initialize(Stack *s) {
    s->top = -1;
}

void push(Stack *s, char c) {
    if (s->top == MAX_SIZE - 1) {
        printf("Stack Overflow\n");
        return;
    }
    s->items[++(s->top)] = c;
}

char pop(Stack *s) {
    if (s->top == -1) {
        printf("Stack Underflow\n");
        return -1;
    }
    return s->items[(s->top)--];
}

int isOperand(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

int precedence(char c) {
    if (c == '+' || c == '-')
        return 1;
    else if (c == '*' || c == '/')
        return 2;
    return 0;
}

void infixToPostfix(char *infix) {
    Stack stack;
    initialize(&stack);
    int i, j = 0;
    int length = strlen(infix);
    char postfix[MAX_SIZE];

    for (i = 0; i < length; i++) {
        char token = infix[i];
        if (token == ' ') {
            continue;
        } else if (isOperand(token)) {
            postfix[j++] = token;
        } else {
            while (stack.top >= 0 && precedence(stack.items[stack.top]) >= precedence(token)) {
                postfix[j++] = pop(&stack);
            }
            push(&stack, token);
        }
    }

    while (stack.top >= 0) {
        postfix[j++] = pop(&stack);
    }
    postfix[j] = '\0';

    printf("Postfix expression: %s\n", postfix);
}

int main() {
    char infixExpression[MAX_SIZE];
    printf("Enter the infix expression (e.g., 'Action + Comedy * Drama'): ");
    scanf("%[^\n]s", infixExpression);

    infixToPostfix(infixExpression);

    return 0;
}
