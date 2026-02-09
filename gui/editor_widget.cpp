#include "editor_widget.hpp"
#include <QPainter>
#include <QKeyEvent>
#include <QFontMetrics>

EditorWidget::EditorWidget(QWidget* parent)
    : QWidget(parent)
{
    setFocusPolicy(Qt::StrongFocus);
    setFont(QFont("Monospace", 12));
}

void EditorWidget::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    QFontMetrics fm(font());

    int line_height = fm.height();
    int y = line_height;

    std::string text = buffer.text();
    QString qtext = QString::fromStdString(text);

    QStringList lines = qtext.split('\n');

    for (const QString& line : lines) {
        painter.drawText(5, y, line);
        y += line_height;
    }

    // Draw cursor
    Cursor c = buffer.cursor();
    int x = 5 + fm.horizontalAdvance(
        lines[c.line].left(c.column)
    );
    int cy = (c.line + 1) * line_height;

    painter.drawLine(x, cy - line_height + 2,
                     x, cy - 2);
}

void EditorWidget::keyPressEvent(QKeyEvent* event) {
    if (event->matches(QKeySequence::Undo)) {
        buffer.undo();
    }
    else if (event->matches(QKeySequence::Redo)) {
        buffer.redo();
    }
    else if (event->key() == Qt::Key_Backspace) {
        buffer.backspace();
    }
    else if (event->key() == Qt::Key_Return) {
        buffer.insert('\n');
    }
    else if (event->key() == Qt::Key_Left) {
        buffer.move_left();
    }
    else if (event->key() == Qt::Key_Right) {
        buffer.move_right();
    }
    else if (!event->text().isEmpty()) {
        QString text = event->text();
        if (!text.isEmpty()) {
            QChar c = text[0];
            if (c.isPrint()) {
                buffer.insert(c.toLatin1());
            }
        }
    }

    update(); // repaint
}
