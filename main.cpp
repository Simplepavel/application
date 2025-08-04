#include <QApplication>
#include "window.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    Window window;
    window.connect();
    window.showMaximized();
    return app.exec();
}