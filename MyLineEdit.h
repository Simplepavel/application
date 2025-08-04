#include <QLineEdit>
#include <QKeyEvent>
#include <QString>
#include <QTextCursor>
class MyLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    MyLineEdit(const QString& text = "", QWidget *parent = nullptr);
    ~MyLineEdit();
    void focusOutEvent(QFocusEvent* event) override;
};
