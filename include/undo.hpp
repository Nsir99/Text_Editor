#pragma once
#include <functional>
#include <stack>

struct Command {
    std::function<void()> undo;
    std::function<void()> redo;
};

class UndoStack {
public:
    void push(std::function<void()> undo,
              std::function<void()> redo);

    void undo();
    void redo();

private:
    std::stack<Command> undo_stack;
    std::stack<Command> redo_stack;
};
