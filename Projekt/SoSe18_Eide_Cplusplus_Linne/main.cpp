#include "meinwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    meinWidget widget;
    widget.setFixedSize(750, 750);
    widget.show();
    return app.exec();
}
