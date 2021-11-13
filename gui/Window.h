#include <QWidget>

class Window : public QWidget
{
    Q_OBJECT
public:
    Window(QWidget *parent = Q_NULLPTR) : QWidget(parent) {}
}