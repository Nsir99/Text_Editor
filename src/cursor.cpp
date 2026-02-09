#include "../headers/cursor.hpp"

Cursor::Cursor() : pos(0) {}

size_t Cursor::position() const {
    return pos;
}

void Cursor::move_left() {
    if (pos > 0)
        pos--;
}

void Cursor::move_right(size_t max) {
    if (pos < max)
        pos++;
}

void Cursor::set(size_t p) {
    pos = p;
}
