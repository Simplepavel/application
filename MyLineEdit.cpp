#include "MyLineEdit.h"



MyLineEdit::MyLineEdit(const QString& text, QWidget* parent):QLineEdit(text, parent)
{}

MyLineEdit::~MyLineEdit()
{}


void MyLineEdit::focusOutEvent(QFocusEvent* event)
{
    QLineEdit::focusOutEvent(event);
    if (text() == ""){setText("Untitled");} 
}



