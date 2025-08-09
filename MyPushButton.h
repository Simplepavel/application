#include <QPushButton>
#include <QWidget>
class MyPushButton : public QPushButton
{
    Q_OBJECT
private:
    int own_id;

public:
    MyPushButton(int id, QWidget *parent = nullptr) : QPushButton(parent), own_id(id)
    {
    }
    MyPushButton(int id, QString txt, QWidget *parent = nullptr) : QPushButton(txt, parent), own_id(id)
    {
    }
    ~MyPushButton()
    {
    }
    int get_id(){return own_id;}
};