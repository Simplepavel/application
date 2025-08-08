#include "window.h"

Window::Window(QWidget *parent) : QWidget(parent)
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
    right_box->setContentsMargins(-1, -1, -1, 40);
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
    right_box->addWidget(contains, 11);

    add_bttn = new QPushButton("Добавить(Ctrl+P)", this);
    QKeySequence seq1(Qt::CTRL | Qt::Key_P);
    add_bttn->setShortcut(seq1);
    right_box->addWidget(add_bttn);

    save_bttn = new QPushButton("Сохранить(Ctrl+S)", this);
    QKeySequence seq2(Qt::CTRL | Qt::Key_S);
    save_bttn->setShortcut(seq2);
    right_box->addWidget(save_bttn);

    main_layout->addLayout(left_box, 1);
    main_layout->addLayout(right_box, 3);

    setLayout(main_layout);
}

void Window::connect()
{
    QObject::connect(add_bttn, SIGNAL(clicked()), this, SLOT(add_bttn_slot()));
}

void Window::add_bttn_slot()
{
    MyPushButton *bttn = new MyPushButton("Untitled", this);
    bttn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    // bttn->insert(*contains, *FileName);
    left_inner1->addWidget(bttn, 0, Qt::AlignTop);
}

Window::~Window() {};