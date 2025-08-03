#include "window.h"


Window::Window(QWidget* parent): QWidget(parent)
{
    main_layout = new QHBoxLayout(this);

    left_box = new QVBoxLayout();

    search = new QLineEdit(this);
    search->setPlaceholderText("Поиск");
    
    left_inner1 = new QVBoxLayout();

    sorters_mode = new QLabel("Сортировать по:", this);
    sorters_mode->setAlignment(Qt::AlignBottom | Qt::AlignLeft);
    sorters_mode->setStyleSheet("background-color: red;");

    by_create = new QRadioButton("По дате создания");
    by_name = new QRadioButton("По названию");
    by_change = new QRadioButton("По дате изменения");
    
    
    left_inner2 = new QVBoxLayout();


    left_inner2->addWidget(sorters_mode, 2); 
    left_inner2->addWidget(by_create, 2); 
    left_inner2->addWidget(by_name, 2); 
    left_inner2->addWidget(by_change, 2);

    left_box->addWidget(search, 1);
    left_box->addLayout(left_inner1, 10);
    left_box->addLayout(left_inner2, 4);

 
    right_box = new QVBoxLayout();
    FileName = new QLabel("Заголовок", this);
    FileName->setAlignment(Qt::AlignCenter);
    QFont FileName_font = FileName->font();
    FileName_font.setPointSize(11);
    FileName->setFont(FileName_font);


    right_box->addWidget(FileName);

    contains = new QPlainTextEdit(this);
    QFont contains_font = contains->font();
    contains_font.setPointSize(24);
    contains->setFont(contains_font);    
    right_box->addWidget(contains, 17);


    add_bttn = new QPushButton("Добавить(Ctrl+P)", this);
    QKeySequence seq1(Qt::CTRL | Qt::Key_P);
    add_bttn->setShortcut(seq1);
    right_box->addWidget(add_bttn, 0, Qt::AlignTop | Qt::AlignLeft);
     


    save_bttn = new QPushButton("Сохранить(Ctrl+S)", this);
    QKeySequence seq2(Qt::CTRL | Qt::Key_S);
    save_bttn->setShortcut(seq2);
    right_box->addWidget(save_bttn, 1, Qt::AlignTop | Qt::AlignLeft);
    
    main_layout->addLayout(left_box, 1);
    main_layout->addLayout(right_box, 3);

    setLayout(main_layout);
}


Window::~Window(){};