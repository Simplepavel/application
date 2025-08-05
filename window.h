#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QLabel>
#include <QRadioButton>
#include <QScrollArea>

#include <QFont>
#include <QKeySequence>

#include "MyLineEdit.h"
#include <QFocusEvent>
#include <QDebug>
#include <QSizePolicy>

class Window : public QWidget
{
    Q_OBJECT
private slots:
    void add_bttn_slot();

private:
    QHBoxLayout *main_layout;

    QVBoxLayout *left_box;
    QLineEdit *search;


    QVBoxLayout *left_inner1;
    QWidget* left_inner_widget;

    QVBoxLayout *left_inner2;
    QLabel *sorters_mode;
    QRadioButton *by_create;
    QRadioButton *by_name;
    QRadioButton *by_change;

    QVBoxLayout *right_box;

    MyLineEdit *FileName;

    QPlainTextEdit *contains;
    QPushButton *add_bttn;
    QPushButton *save_bttn;



    QScrollArea *scrollArea;

public:
    Window(QWidget *parent = nullptr);
    ~Window();
    void connect();
};