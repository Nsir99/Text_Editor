#include <iostream>
#include "../headers/text_buffer.hpp"

int main() {
    TextBuffer tb;

    for (char c : std::string("Hello")) {
        tb.insert(c);
    }

    tb.insert('!');
    std::cout << tb.text() << std::endl; // Hello!

    tb.undo();
    std::cout << tb.text() << std::endl; // Hello

    tb.redo();
    std::cout << tb.text() << std::endl; // Hello!

    tb.erase();
    std::cout << tb.text() << std::endl; // Hello

    tb.undo();
    std::cout << tb.text() << std::endl; // Hello!

    return 0;
}
