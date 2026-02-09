#pragma once
#include <QWidget>
#include "../include/text_buffer.hpp"

class EditorWidget : public QWidget {

public:
    explicit EditorWidget(QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent*) override;
    void keyPressEvent(QKeyEvent* event) override;

private:
    TextBuffer buffer;
};
