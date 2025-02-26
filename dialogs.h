#ifndef DIALOGS_H
#define DIALOGS_H

#include <QDialog>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>

class Dialogs : public QDialog
{
    Q_OBJECT

public:
    Dialogs(QWidget *parent = nullptr);
    ~Dialogs();

    QHBoxLayout *horizontal;
    QLineEdit *lineedit;
    QPushButton *buttonsearch;
    QPushButton *buttonprev;
};

#endif // DIALOGS_H
