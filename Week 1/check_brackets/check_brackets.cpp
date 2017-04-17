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

bool match(char f, char s) {
    if (((f=='(') && (s==')')) || ((f=='[') && (s==']')) || ((f=='{') && (s=='}'))) {
        return true;
    }
    return false;
}

void check_brackets(std::string text) {
    std::stack <Bracket> opening_brackets_stack;
    for (int position = 0; position < text.length(); ++position) {
        char next = text[position];

        if (next == '(' || next == '[' || next == '{') {
            opening_brackets_stack.push(Bracket(next, position));
        }

        if (next == ')' || next == ']' || next == '}') {
            if (!opening_brackets_stack.empty()) {
                Bracket lst = opening_brackets_stack.top();
                if (match(lst.type, next)) {
                    opening_brackets_stack.pop();
                } else {
                    std::cout << position+1; 
                    return;
                }
            } else {
                std::cout << position+1;
                return; 
            }
        }
    }
    if (opening_brackets_stack.empty()) {
        std::cout << "Success";
        return;
    } else {
        while (opening_brackets_stack.size() != 1) {
            opening_brackets_stack.pop();
        }
        std::cout << opening_brackets_stack.top().position+1;
        return;
    }
}

int main() {
    std::string text;
    getline(std::cin, text);
    check_brackets(text);
    return 0;
}
