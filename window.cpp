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
    contains = new QPlainTextEdit(this);


    QFont contains_font = contains->font();
    contains_font.setPointSize(24);
    contains->setFont(contains_font);
    
    
    right_box->addWidget(contains);

    main_layout->addLayout(left_box, 1);
    main_layout->addLayout(right_box, 3);

    setLayout(main_layout);
}


Window::~Window(){};