#include <QApplication>
#include "editor_widget.hpp"

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    EditorWidget editor;
    editor.resize(800, 600);
    editor.show();

    return app.exec();
}
