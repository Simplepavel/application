#include "window.h"

Window::Window(DB *data_dase, QWidget *parent) : QWidget(parent), db(data_dase), file_id(-1), current_save(true)
{
    sequence_bttn.push_back(file_id);
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
    right_box->setContentsMargins(-1, -1, -1, 12);
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
    contains->hide();
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
    QObject::connect(delete_bttn, SIGNAL(clicked()), this, SLOT(delete_slot()));
    QObject::connect(contains, &QPlainTextEdit::textChanged, this, &Window::on_file_change);
}

void Window::add_bttn_slot()
{
    if (!current_save)
    {
        if (dialog_window("Сохранить текущие изменения?") == QDialog::Accepted) save_slot();
        else
        {
            db->get(file_id).save = true;
            QObject::connect(contains, &QPlainTextEdit::textChanged, this, &Window::on_file_change);
        }
    }
    QString result = get_file_name_widget();
    if (result.isEmpty())
    {
        return;
    }
    if (contains->isHidden())
    {
        contains->show();
    }
    elem *new_elem = new elem(QTime::currentTime(), result, "");
    file_id = db->add(new_elem);
    MyPushButton *bttn = new MyPushButton(file_id, new_elem->name, this);
    QObject::connect(bttn, &QPushButton::clicked, this, [this, bttn]()
                     { this->open_slot(bttn->get_id()); });
    left_inner1->addWidget(bttn);
    bttnGroup->addButton(bttn, file_id);
    FileName->setText(new_elem->name);
    contains->blockSignals(true);
    contains->clear();
    contains->blockSignals(false);
    sequence_bttn.push_back(file_id);
    current_save = true;
}

void Window::save_slot()
{
    if (file_id == -1)
    {
        warning("Выберите заметку для сохранения");
    }
    else
    {
        elem &save_elem = db->get(file_id);
        save_elem.contain = contains->toPlainText();
        current_save = true;
        save_elem.save = true;
        QObject::connect(contains, &QPlainTextEdit::textChanged, this, &Window::on_file_change);
    }
}

void Window::open_slot(int push_bttn_idx)
{
    elem &current_elem = db->get(file_id);
    if (!current_save)
    {
        if (dialog_window("Сохранить текущие изменения?") == QDialog::Accepted) save_slot();
        else 
        {
            current_elem.save = true;
            QObject::connect(contains, &QPlainTextEdit::textChanged, this, &Window::on_file_change);
        }
    }
    if (contains->isHidden())
    {
        contains->show();
    }
    elem &open_elem = db->get(push_bttn_idx);
    contains->blockSignals(true);
    contains->setPlainText(open_elem.contain);
    contains->blockSignals(false);
    FileName->setText(open_elem.name);
    file_id = push_bttn_idx;
    current_save = open_elem.save;
}

void Window::delete_slot() // Добавить вы действительно хотите удлаить заметку?
{
    if (file_id == -1)
    {
        warning("Создайте или выберите заметку для удаления");
        return;
    }
    
    if (dialog_window("Вы действительно хотите удалить заметку?") == QDialog::Accepted)
    {
        QAbstractButton *bttn_to_delete = bttnGroup->button(file_id);
        bttn_to_delete->deleteLater();
        left_inner1->removeWidget(bttn_to_delete);
        bttnGroup->removeButton(bttn_to_delete);

        sequence_bttn.remove(file_id);
        file_id = *(--sequence_bttn.end());
        if (file_id == -1)
        {
            FileName->clear();
            contains->clear();
            contains->hide();
            return;
        }
        elem &content = db->get(file_id);
        FileName->setText(content.name);
        contains->blockSignals(true);
        contains->setPlainText(content.contain);
        contains->blockSignals(false);
    }
}

QString Window::get_file_name_widget()
{
    QDialog *window = new QDialog(this);
    window->setModal(true);
    QLineEdit *line = new QLineEdit("Без названия", window);
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

    if (window->exec() == QDialog::Accepted)
        return line->text();
    else
        return "";
}

void Window::warning(const QString &txt_warning)
{
    QDialog required(this);
    required.setModal(true);
    QLabel label(txt_warning, this);
    QPushButton bttn("Ок", this);
    QVBoxLayout box;
    box.addWidget(&label);
    box.addWidget(&bttn);
    required.setLayout(&box);
    QObject::connect(&bttn, &QPushButton::clicked, &required, &QDialog::accept);
    required.exec();
}

int Window::dialog_window(const QString& txt) // сохрнаить заметку а еще удалить заметку и тп?
{
    QDialog* dialog = new QDialog(this);
    dialog->setModal(true);
    QLabel* lbl = new QLabel(txt, dialog);
    QPushButton* ok = new QPushButton("Ок", dialog);
    QPushButton* cancel = new QPushButton("Отмена", dialog);
    QHBoxLayout* inner = new QHBoxLayout;
    inner->addWidget(ok);
    inner->addWidget(cancel);

    QVBoxLayout* outer = new QVBoxLayout;

    outer->addWidget(lbl);
    outer->addLayout(inner);

    dialog->setLayout(outer);

    QObject::connect(ok, &QPushButton::clicked, dialog, &QDialog::accept);
    QObject::connect(cancel, &QPushButton::clicked, dialog, &QDialog::reject);

    return dialog->exec();
}



void Window::closeEvent(QCloseEvent* event)
{
    // db->save();
    event->accept();
}


void Window::on_file_change()
{
    current_save = false;
    db->get(file_id).save = false;
    qDebug() << "Изменяем константы";
    QObject::disconnect(contains, &QPlainTextEdit::textChanged, this, &Window::on_file_change);
}

Window::~Window() {};