#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

enum {Num};
int token;
int token_val;
char *line = NULL;
char *src = NULL;


void next() {
    // skip white space
    while (*src == ' ' || *src == '\t') {
        src++;
    }

    token = *src++;

    if (token >= '0' && token <= '9') {
        token_val = token - '0';
        token = Num;

        while(*src >= '0' && *src <= '9') {
            token_val = token_val * 10 + *src - '0';
            src++;
        }
        return;
    }

    // printf("unexpexted %s\n", *src);
}

void match(int tk) {
    if (token != tk) {
        printf("expected token: %d(%c), got: %d(%c)\n", tk, tk, token, token);
        exit(-1);
    }
    next();
}

// BNF 范式
// <expr> ::= <expr> + <term>
//          | <expr> - <term>
//          | <term>

// <term> ::= <term> * <factor>
//          | <term> / <factor>
//          | <factor>

// <factor> ::= ( <expr> )
//            | Num

// 消除左递归后的文法
// <expr> ::= <term> <expr_tail>
// <expr_tail> ::= + <term> <expr_tail>
//               | - <term> <expr_tail>
//               | <empty>

// <term> ::= <factor> <term_tail>
// <term_tail> ::= * <factor> <term_tail>
//               | / <factor> <term_tail>
//               | <empty>

// <factor> ::= ( <expr> )
//            | Num


int expr();
int expr_tail(int lvalue);
int term();
int term_tail(int lvalue);
int factor();

int expr() {
    int lvalue = term();
    return expr_tail(lvalue);
}

int expr_tail(int lvalue) {
    if (token == '+') {
        match('+');
        int value = lvalue + term();
        return expr_tail(value);
    } else if (token == '-') {
        match('-');
        int value = lvalue - term();
        return expr_tail(value);
    } else {
        return lvalue;
    }
}

int term() {
    int lvalue = factor();
    return term_tail(lvalue);
}

int term_tail(int lvalue) {
    if (token == '*') {
        match('*');
        int value = lvalue * factor();
        return term_tail(value);
    } else if (token == '/') {
        match('/');
        int value = lvalue / factor();
        return term_tail(value);
    } else {
        return lvalue;
    }
}

int factor() {
    int value = 0;
    if (token == '(') {
        match('(');
        value = expr();
        match(')');
    } else {
        value = token_val;
        match(Num);
    }
    return value;
}


int main (int argc, char **argv) {
    line = (char *)malloc(sizeof(char) * 20);
    while (fgets(line, 20, stdin)) {
        src = line;
        next();
        printf("%d\n", expr());
    }
    return 0;
}
