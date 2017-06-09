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
    QGridLayout* layout = new QGridLayout(&w);

    // Filter slider
    QLabel* filterLabel = new QLabel("Filter percentage");
    layout->addWidget(filterLabel, 1, 1);
    QSlider* filterSlider = new QSlider(Qt::Orientation::Horizontal);
    filterSlider->setMinimum(1);
    filterSlider->setMaximum(100);
    filterSlider->setValue(50);
    layout->addWidget(filterSlider, 1, 2);

    // Spot position slider
    QLabel* spotVerticalPositionLabel = new QLabel("Spot position");
    layout->addWidget(spotVerticalPositionLabel, 2, 1);
    QSlider* spotVerticalPositionSlider = new QSlider(Qt::Orientation::Horizontal);
    spotVerticalPositionSlider->setMinimum(0);
    spotVerticalPositionSlider->setMaximum(90);
    spotVerticalPositionSlider->setValue(0);
    layout->addWidget(spotVerticalPositionSlider, 2, 2);

    MainWidget* imageWidget = new MainWidget();
    layout->addWidget(imageWidget, 4, 1, 1, 2);
    QObject::connect(filterSlider, SIGNAL(valueChanged(int)), imageWidget, SLOT(filterSliderUpdate(int)));
    QObject::connect(spotVerticalPositionSlider, SIGNAL(valueChanged(int)), imageWidget, SLOT(spotVerticalSliderUpdate(int)));
    w.show();
#else
    QLabel note("OpenGL Support required");
    note.show();
#endif
    return app.exec();
}
