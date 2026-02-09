#include "undo.hpp"

void UndoStack::push(std::function<void()> undo,
                     std::function<void()> redo)
{
    undo_stack.push({undo, redo});
    while (!redo_stack.empty())
        redo_stack.pop();
}

void UndoStack::undo() {
    if (undo_stack.empty()) return;
    Command cmd = undo_stack.top();
    undo_stack.pop();
    cmd.undo();
    redo_stack.push(cmd);
}

void UndoStack::redo() {
    if (redo_stack.empty()) return;
    Command cmd = redo_stack.top();
    redo_stack.pop();
    cmd.redo();
    undo_stack.push(cmd);
}
