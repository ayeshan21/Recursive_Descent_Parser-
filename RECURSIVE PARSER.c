#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Token Types
typedef enum {
    TOKEN_NUMBER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULT,
    TOKEN_DIV,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_EOF
} TokenType;

// Token Structure
typedef struct {
    TokenType type;
    int value;
} Token;

// Lexer State
const char *input;
int pos = 0;
Token current_token;

// Function Prototypes
Token get_next_token();
void advance();
void error(const char *message);
void match(TokenType type);
int parse_expression();
int parse_term();
int parse_factor();

// Lexer Implementation
Token get_next_token() {
    while (input[pos] != '\0') {
        if (isspace(input[pos])) {
            pos++;
            continue;
        }
        if (isdigit(input[pos])) {
            int value = 0;
            while (isdigit(input[pos])) {
                value = value * 10 + (input[pos] - '0');
                pos++;
            }
            return (Token){TOKEN_NUMBER, value};
        }
        if (input[pos] == '+') return (Token){TOKEN_PLUS, 0}, pos++, current_token;
        if (input[pos] == '-') return (Token){TOKEN_MINUS, 0}, pos++, current_token;
        if (input[pos] == '*') return (Token){TOKEN_MULT, 0}, pos++, current_token;
        if (input[pos] == '/') return (Token){TOKEN_DIV, 0}, pos++, current_token;
        if (input[pos] == '(') return (Token){TOKEN_LPAREN, 0}, pos++, current_token;
        if (input[pos] == ')') return (Token){TOKEN_RPAREN, 0}, pos++, current_token;

        error("Invalid character");
    }
    return (Token){TOKEN_EOF, 0};
}

void advance() {
    current_token = get_next_token();
}

void error(const char *message) {
    fprintf(stderr, "Error: %s\n", message);
    exit(EXIT_FAILURE);
}

// Match a specific token type
void match(TokenType type) {
    if (current_token.type == type) {
        advance();
    } else {
        error("Unexpected token");
    }
}

// Parser Implementation
int parse_expression() {
    int result = parse_term();
    while (current_token.type == TOKEN_PLUS || current_token.type == TOKEN_MINUS) {
        if (current_token.type == TOKEN_PLUS) {
            match(TOKEN_PLUS);
            result += parse_term();
        } else if (current_token.type == TOKEN_MINUS) {
            match(TOKEN_MINUS);
            result -= parse_term();
        }
    }
    return result;
}

int parse_term() {
    int result = parse_factor();
    while (current_token.type == TOKEN_MULT || current_token.type == TOKEN_DIV) {
        if (current_token.type == TOKEN_MULT) {
            match(TOKEN_MULT);
            result *= parse_factor();
        } else if (current_token.type == TOKEN_DIV) {
            match(TOKEN_DIV);
            int divisor = parse_factor();
            if (divisor == 0) {
                error("Division by zero");
            }
            result /= divisor;
        }
    }
    return result;
}

int parse_factor() {
    if (current_token.type == TOKEN_NUMBER) {
        int value = current_token.value;
        match(TOKEN_NUMBER);
        return value;
    } else if (current_token.type == TOKEN_LPAREN) {
        match(TOKEN_LPAREN);
        int result = parse_expression();
        match(TOKEN_RPAREN);
        return result;
    } else {
        error("Expected number or '('");
        return 0;
    }
}

// Main Function
int main() {
    char expression[256];
    printf("Enter an expression: ");
    fgets(expression, sizeof(expression), stdin);

    input = expression;
    pos = 0;
    advance();

    int result = parse_expression();
    if (current_token.type != TOKEN_EOF) {
        error("Unexpected characters at the end of the input");
    }

    printf("Valid expression. Result: %d\n", result);
    return 0;
}
