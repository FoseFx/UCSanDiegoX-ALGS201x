#include <iostream>
#include <stack>
#include <string>

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
    bool isBalanced = false;                                        // my line

    std::stack <Bracket> opening_brackets_stack;
    for (int position = 0; position < text.length(); ++position) {
        char next = text[position];

        if (next == '(' || next == '[' || next == '{') {
            opening_brackets_stack.push(Bracket(next, position));   // my line
        }

        if (next == ')' || next == ']' || next == '}') {
            if(opening_brackets_stack.empty()) {                    // my line
                isBalanced = false;                                 // my line
                continue;                                           // my line
            }                                                       // my line
            Bracket br = opening_brackets_stack.top();              // my line
            opening_brackets_stack.pop();                           // my line
            isBalanced = br.Matchc(next);                           // my line
        }
    }
    std::cout << ((isBalanced)? "balanced":"not balanced") << "\n"; // my line

    return 0;
}
