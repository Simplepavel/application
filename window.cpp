#include "window.h"

Window::Window(DB *data_dase, QWidget *parent) : QWidget(parent), db(data_dase), file_id(-1)
{
    main_layout = new QHBoxLayout(this);
    left_box = new QVBoxLayout();

    search = new QLineEdit(this);
    search->setPlaceholderText("Поиск");

    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);

    left_inner_widget = new QWidget(this);
    left_inner1 = new QVBoxLayout(left_inner_widget);
    left_inner1->setSpacing(0);
    left_inner1->setAlignment(Qt::AlignTop);
    scrollArea->setWidget(left_inner_widget);

    sorters_mode = new QLabel("Сортировать по:", this);
    sorters_mode->setAlignment(Qt::AlignBottom | Qt::AlignLeft);

    by_create = new QRadioButton("По дате создания");
    by_name = new QRadioButton("По названию");
    by_change = new QRadioButton("По дате изменения");

    left_inner2 = new QVBoxLayout;

    left_inner2->addWidget(sorters_mode, 2);
    left_inner2->addWidget(by_create, 2);
    left_inner2->addWidget(by_name, 2);
    left_inner2->addWidget(by_change, 2);

    left_box->addWidget(search, 1);
    left_box->addWidget(scrollArea, 30); // вместе со scrollArea узнаем и про left_inner_widget
    left_box->addLayout(left_inner2, 4);

    right_box = new QVBoxLayout();
    right_box->setAlignment(Qt::AlignBottom | Qt::AlignLeft);
    right_box->setContentsMargins(-1, -1, -1, 13);
    FileName = new MyLineEdit("", this);
    FileName->setStyleSheet("QLineEdit { background: transparent; border: none; }");
    FileName->setAlignment(Qt::AlignCenter);
    QFont FileName_font = FileName->font();
    FileName_font.setPointSize(11);
    FileName->setFont(FileName_font);

    right_box->addWidget(FileName);

    contains = new QPlainTextEdit(this);
    QFont contains_font = contains->font();
    contains_font.setPointSize(24);
    contains->setFont(contains_font);
    right_box->addWidget(contains);

    add_bttn = new QPushButton("Добавить(Ctrl+P)", this);
    QKeySequence seq1(Qt::CTRL | Qt::Key_P);
    add_bttn->setShortcut(seq1);
    right_box->addWidget(add_bttn);

    save_bttn = new QPushButton("Сохранить изменения заметки(Ctrl+S)", this);
    QKeySequence seq2(Qt::CTRL | Qt::Key_S);
    save_bttn->setShortcut(seq2);
    right_box->addWidget(save_bttn);

    delete_bttn = new QPushButton("Удалить текущую открытую заметку(Crtl+D)", this);
    QKeySequence seq3(Qt::CTRL | Qt::Key_D);
    delete_bttn->setShortcut(seq3);
    right_box->addWidget(delete_bttn);

    bttnGroup = new QButtonGroup(this);

    main_layout->addLayout(left_box, 1);
    main_layout->addLayout(right_box, 3);
    setLayout(main_layout);
}

void Window::connect()
{
    QObject::connect(add_bttn, SIGNAL(clicked()), this, SLOT(add_bttn_slot()));
    QObject::connect(save_bttn, SIGNAL(clicked()), this, SLOT(save_slot()));
}

void Window::add_bttn_slot()
{
    elem *new_elem = new elem(QTime::currentTime(), get_file_name_widget(), "");
    file_id = db->add(new_elem);
    MyPushButton *bttn = new MyPushButton(file_id, new_elem->name, this);
    QObject::connect(bttn, &QPushButton::clicked, this, [this, bttn]()
                     { this->open_slot(bttn->get_id()); });
    left_inner1->addWidget(bttn);
    bttnGroup->addButton(bttn, file_id);
    FileName->setText(new_elem->name);
}

void Window::save_slot()
{
    elem &save_elem = db->get(file_id);
    save_elem.contain = contains->toPlainText();
}

void Window::open_slot(int push_bttn_idx)
{
    elem &open_elem = db->get(push_bttn_idx);
    contains->setPlainText(open_elem.contain);
    FileName->setText(open_elem.name);
    file_id = push_bttn_idx;
}

void Window::delete_slot()
{
}

QString Window::get_file_name_widget()
{
    QDialog *window = new QDialog(this);
    window->setModal(true);

    QLineEdit *line = new QLineEdit("Untitled", window);
    line->setPlaceholderText("Введите название новой заметки");

    QVBoxLayout *outer = new QVBoxLayout;
    QHBoxLayout *inner = new QHBoxLayout;

    QPushButton *ok = new QPushButton("Ок", window);
    QPushButton *close = new QPushButton("Закрыть", window);

    inner->addWidget(ok);
    inner->addWidget(close);

    outer->addWidget(line);
    outer->addLayout(inner);

    window->setLayout(outer);

    QObject::connect(ok, &QPushButton::clicked, window, &QDialog::accept);
    QObject::connect(close, &QPushButton::clicked, window, &QDialog::reject);

    window->exec();
    return line->text();
}

Window::~Window() {};