#include <QApplication>
#include "window.h"

int main(int argc, char* argv[])
{
    DB dataBase;
    QApplication app(argc, argv);
    Window window(&dataBase);
    window.connect();
    window.showMaximized();
    return app.exec();
}