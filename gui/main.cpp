#include <QApplication>
#include "Window.h"

int main()
{
    QApplication app;
    Window window;
    window.show();
    return app.exec();
}