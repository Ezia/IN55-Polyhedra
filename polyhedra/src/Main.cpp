#include <QApplication>
#include <QLabel>

#include <QSlider>
#include <QVBoxLayout>


#ifndef QT_NO_OPENGL
#include "MainWidget.h"
#endif

int32 main(int32 argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("cube");
    app.setApplicationVersion("0.1");
#ifndef QT_NO_OPENGL
    QWidget w;
    w.resize(500, 500);
    QVBoxLayout* layout = new QVBoxLayout(&w);
    QSlider* slider = new QSlider(Qt::Orientation::Horizontal);
    layout->addWidget(slider);
    MainWidget* widget = new MainWidget();
    layout->addWidget(widget);
    QObject::connect(slider, SIGNAL(valueChanged(int)), widget, SLOT(cursorMoved(int)));
    w.show();
#else
    QLabel note("OpenGL Support required");
    note.show();
#endif
    return app.exec();
}
