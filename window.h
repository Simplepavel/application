#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QLabel>
#include <QRadioButton>
#include <QScrollArea>
#include <QDialog>

#include <QFont>
#include <QKeySequence>
#include <QFocusEvent>
#include <QDebug>
#include <QSizePolicy>
#include <QButtonGroup>
#include <List>

#include "MyLineEdit.h"
#include "MyPushButton.h"
#include "DataBase.h"

class Window : public QWidget
{
    Q_OBJECT
private slots:
    void add_bttn_slot();
    void save_slot();
    void delete_slot();

private:
    DB *db;
    QHBoxLayout *main_layout;
    QVBoxLayout *left_box;
    QLineEdit *search;

    QVBoxLayout *left_inner1;
    QWidget *left_inner_widget;

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
    QPushButton *delete_bttn;

    QButtonGroup *bttnGroup;
    QScrollArea *scrollArea;
    int file_id;
    std::list<int> sequence_bttn;

    void open_slot(int);
    QString get_file_name_widget();
    void warning(const QString&);

public:
    Window(DB *data_base, QWidget *parent = nullptr);
    ~Window();
    void connect();
};