#include "text_buffer.hpp"

TextBuffer::TextBuffer() {
    line_starts.push_back(0);
}

size_t TextBuffer::to_offset(size_t line, size_t col) const {
    return line_starts[line] + col;
}

void TextBuffer::rebuild_lines() {
    line_starts.clear();
    line_starts.push_back(0);

    std::string s = buffer.to_string();
    for (size_t i = 0; i < s.size(); ++i) {
        if (s[i] == '\n')
            line_starts.push_back(i + 1);
    }
}

void TextBuffer::insert(char c) {
    size_t line = cur.line;
    size_t col = cur.column;
    size_t pos = to_offset(line, col);

    auto undo = [this, line, col]() {
        buffer.move_cursor(to_offset(line, col + 1));
        buffer.erase();
        rebuild_lines();
        cur = {line, col};
    };

    auto redo = [this, c, line, col]() {
        buffer.move_cursor(to_offset(line, col));
        buffer.insert(c);
        rebuild_lines();
        if (c == '\n') {
            cur.line++;
            cur.column = 0;
        } else {
            cur.column++;
        }
    };

    redo();
    undo_stack.push(undo, redo);
}

void TextBuffer::backspace() {
    if (cur.line == 0 && cur.column == 0)
        return;

    size_t line = cur.line;
    size_t col = cur.column;
    size_t pos = to_offset(line, col);

    buffer.move_cursor(pos);
    buffer.erase();

    rebuild_lines();

    if (col > 0) {
        cur.column--;
    } else {
        cur.line--;
        cur.column = 0;
    }
}

void TextBuffer::move_left() {
    if (cur.column > 0) cur.column--;
}

void TextBuffer::move_right() {
    cur.column++;
}

void TextBuffer::move_up() {
    if (cur.line > 0) cur.line--;
}

void TextBuffer::move_down() {
    if (cur.line + 1 < line_starts.size())
        cur.line++;
}

void TextBuffer::undo() {
    undo_stack.undo();
}

void TextBuffer::redo() {
    undo_stack.redo();
}

std::string TextBuffer::text() const {
    return buffer.to_string();
}

Cursor TextBuffer::cursor() const {
    return cur;
}
