#include "gap_buffer.hpp"
#include <cstring>

GapBuffer::GapBuffer(size_t cap)
    : capacity(cap), gap_start(0), gap_end(cap)
{
    buffer = new char[capacity];
}

GapBuffer::~GapBuffer() {
    delete[] buffer;
}

size_t GapBuffer::size() const {
    return capacity - (gap_end - gap_start);
}

size_t GapBuffer::cursor() const {
    return gap_start;
}

void GapBuffer::grow() {
    size_t new_cap = capacity * 2;
    char* new_buf = new char[new_cap];

    size_t left_size = gap_start;
    size_t right_size = capacity - gap_end;

    std::memcpy(new_buf, buffer, left_size);
    std::memcpy(new_buf + new_cap - right_size,
                buffer + gap_end, right_size);

    gap_end = new_cap - right_size;
    capacity = new_cap;

    delete[] buffer;
    buffer = new_buf;
}

void GapBuffer::insert(char c) {
    if (gap_start == gap_end)
        grow();
    buffer[gap_start++] = c;
}

void GapBuffer::erase() {
    if (gap_start > 0)
        gap_start--;
}

void GapBuffer::move_cursor(size_t pos) {
    if (pos < gap_start) {
        while (pos < gap_start) {
            buffer[--gap_end] = buffer[--gap_start];
        }
    } else {
        while (gap_start < pos) {
            buffer[gap_start++] = buffer[gap_end++];
        }
    }
}

std::string GapBuffer::to_string() const {
    std::string result;
    result.reserve(size());
    result.append(buffer, gap_start);
    result.append(buffer + gap_end, capacity - gap_end);
    return result;
}
