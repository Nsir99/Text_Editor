#pragma once
#include "gap_buffer.hpp"
#include "undo.hpp"
#include <vector>
#include <string>

struct Cursor {
    size_t line = 0;
    size_t column = 0;
};

class TextBuffer {
public:
    TextBuffer();

    void insert(char c);
    void backspace();

    void move_left();
    void move_right();
    void move_up();
    void move_down();

    void undo();
    void redo();

    std::string text() const;
    Cursor cursor() const;

private:
    GapBuffer buffer;
    UndoStack undo_stack;
    Cursor cur;
    std::vector<size_t> line_starts;

    size_t to_offset(size_t line, size_t col) const;
    void rebuild_lines();
};
