# Recursive_Descent_Parser

This C program implements a Recursive Descent Parser to validate and evaluate arithmetic expressions based on a grammar defined in Backus-Naur Form (BNF). The BNF grammar is defined as follows:
expression ::= term {("+" | "-") term}
term       ::= factor {("*" | "/") factor}
factor     ::= number| "(" expression ")"
number     ::= digit {digit}
digit      ::= "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"

Expression Evaluation:
This program computes the result of valid mathematical expressions by following operator precedence rules and supports addition, subtraction, multiplication, and division, including parentheses.

Error Handling:
This program detects syntax errors such as missing parentheses, unexpected tokens, or division by zero and displays meaningful error messages for invalid input.

User Interaction:
This Program prompts the user for an input expression and shows output whether the expression is valid and prints the evaluated result.

In conclusion, this program effectively combines lexical analysis, syntax validation, and evaluation, making it a fundamental example of compiler parsing techniques in C.
