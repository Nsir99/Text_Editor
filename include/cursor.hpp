#pragma once

#include <cstddef>

class Cursor {
public:
    Cursor();
    

    size_t position() const;

    void move_left();
    void move_right(size_t max);

    void set(size_t pos);

private:
    size_t pos;
};
