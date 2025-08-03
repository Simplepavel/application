#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QLabel>
#include <QRadioButton>



#include <QFont>
#include <QKeySequence>


class Window: public QWidget
{
    Q_OBJECT
    private:
    QHBoxLayout* main_layout;

    QVBoxLayout* left_box;
    QLineEdit* search;
    QVBoxLayout* left_inner1;
    QVBoxLayout* left_inner2;
    QLabel* sorters_mode;
    QRadioButton* by_create;
    QRadioButton* by_name;
    QRadioButton* by_change;


    QVBoxLayout* right_box;

    QLabel* FileName;
    
    
    QPlainTextEdit* contains;
    QPushButton* add_bttn;
    QPushButton* save_bttn;



    QWidget* delete_me;



    public:
    Window(QWidget* parent = nullptr);
    ~Window();
};