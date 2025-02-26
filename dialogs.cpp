#include "dialogs.h"

Dialogs::Dialogs(QWidget *parent)
    : QDialog(parent)
{
    horizontal = new QHBoxLayout(this);
    lineedit = new QLineEdit(this);
    buttonsearch = new QPushButton("Find");
    buttonprev = new QPushButton("Previous");
    horizontal->addWidget(lineedit);
    horizontal->addWidget(buttonsearch);
    horizontal->addWidget(buttonprev);
}

Dialogs::~Dialogs()
{
}
