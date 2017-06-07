#include <QApplication>
#include <QLabel>

#ifndef QT_NO_OPENGL
#include "MainWidget.h"
#endif

int32 main(int32 argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("cube");
    app.setApplicationVersion("0.1");
#ifndef QT_NO_OPENGL
    MainWidget widget;
    widget.show();
#else
    QLabel note("OpenGL Support required");
    note.show();
#endif
    return app.exec();
}
