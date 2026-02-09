#pragma once

#include <cstddef>
#include <string>

class GapBuffer {
public:
    explicit GapBuffer(size_t initial_capacity = 1024);
    ~GapBuffer();

    GapBuffer(const GapBuffer&) = delete;
    GapBuffer& operator=(const GapBuffer&) = delete;

    void insert(char c);
    void erase();                 // backspace
    void move_cursor(size_t pos); // absolute position

    size_t size() const;
    size_t cursor() const;

    std::string to_string() const;

private:
    char* buffer;
    size_t capacity;
    size_t gap_start;
    size_t gap_end;

    void grow();
};
