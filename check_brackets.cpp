#include <iostream>
#include <stack>
#include <string>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
struct Bracket {
    Bracket(char type, int position):
            type(type),
            position(position)
    {}

    bool Matchc(char c) {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }

    char type;
    int position;
};

int main() {
    std::string text;
    getline(std::cin, text);
    bool isBalanced = true;
    int failedChar = -1;

    std::stack<Bracket> opening_brackets_stack;
    for (int position = 0; position < text.length(); ++position) {
        char next = text[position];
        if (next == '(' || next == '[' || next == '{') {
            opening_brackets_stack.push(Bracket(next, position));
        }
        if (next == ')' || next == ']' || next == '}') {
            // First unmatched closing bracket
            if (opening_brackets_stack.empty()) {
                isBalanced = false;
                failedChar = position;
                break;
            }
            Bracket bracket = opening_brackets_stack.top();
            opening_brackets_stack.pop();
            if (!bracket.Matchc(next)) {
                isBalanced = false;
                failedChar = position;
                break;
            }
        }
    }

    if (isBalanced) {
        isBalanced = opening_brackets_stack.empty();
        if (!isBalanced) {
            while (opening_brackets_stack.size() != 1) {
                opening_brackets_stack.pop();
            }
            failedChar = opening_brackets_stack.top().position;
        }
    }

    if (isBalanced) {
        std::cout << "Success";
    } else {
        std::cout << std::to_string(failedChar + 1);
    }
    return 0;
}
#pragma clang diagnostic pop