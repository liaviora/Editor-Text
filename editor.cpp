#include "editor.h"
#include "ui_editor.h"

Editor::Editor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Editor)
{
    ui->setupUi(this);

    dialogs = new Dialogs(this);
    connect(ui->actionnew, &QAction::triggered, this, &Editor::newfile);
    connect(ui->actionopen, &QAction::triggered, this, &Editor::open);
    connect(ui->actionsave, &QAction::triggered, this, &Editor::save);
    connect(ui->actionsave_as, &QAction::triggered, this, &Editor::saveas);
    connect(ui->actionexit, &QAction::triggered, this, &Editor::exit);

    connect(ui->actioncopy, &QAction::triggered, ui->textedit, &QTextEdit::copy);
    connect(ui->actioncut, &QAction::triggered, ui->textedit, &QTextEdit::cut);
    connect(ui->actionpaste, &QAction::triggered, ui->textedit, &QTextEdit::paste);
    connect(ui->actionundo, &QAction::triggered, ui->textedit, &QTextEdit::undo);
    connect(ui->actionredo, &QAction::triggered, ui->textedit, &QTextEdit::redo);

    connect(ui->actionbold, &QAction::triggered, this, &Editor::setfontbold);
    connect(ui->actionitalic, &QAction::triggered, this, &Editor::setfontitalic);
    connect(ui->actionunderline, &QAction::triggered, this, &Editor::setfontunderline);
    connect(ui->actionabout, &QAction::triggered, this, &Editor::about);
    connect(ui->actionprint, &QAction::triggered, this, &Editor::print);
    connect(ui->actionsearch, &QAction::triggered, this, &Editor::dialogsStart);

    connect(dialogs->buttonsearch, &QPushButton::clicked, this, &Editor::searchText);
    connect(dialogs->buttonprev, &QPushButton::clicked, this, &Editor::previousText);

    setWindowIcon(QIcon(":/rexallina/images/icon.png"));
}

Editor::~Editor()
{
    delete ui;
}

void Editor::dialogsStart()
{
    dialogs->show();
}

void Editor::previousText()
{
    ui->textedit->find(dialogs->lineedit->text(), QTextDocument::FindBackward | QTextDocument::FindCaseSensitively);
}

void Editor::searchText()
{
    ui->textedit->find(dialogs->lineedit->text(), QTextDocument::FindCaseSensitively);
}

void Editor::exit()
{
    if (maybesave()) {
        QWidget::close();
    }
}

void Editor::newfile()
{
    if (maybesave()) {
        ui->textedit->clear();
    }
}

void Editor::open()
{
    if (maybesave()) {
        QString filename = QFileDialog::getOpenFileName(this);
        if (!filename.isEmpty())
            loadfile(filename);
    }
}

bool Editor::save()
{
    if (currentfile.isEmpty()) {
        return saveas();
    } else {
        return savefile(currentfile);
    }
}

bool Editor::saveas()
{
    QString filename = QFileDialog::getSaveFileName(this);
    if (filename.isEmpty())
        return false;
    return savefile(filename);
}

bool Editor::maybesave()
{
    if (ui->textedit->document()->isModified()) {
            QMessageBox::StandardButton rets;
            rets = QMessageBox::warning(this, tr("Warning"),
                                        tr("the document has been modified. \n"
                                           "Do you want to save changes?"),
                                        QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
            if (rets == QMessageBox::Save)
                return save();
            else if (rets == QMessageBox::Cancel)
                return false;
        }
    return true;
}

bool Editor::savefile(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Warning"),
                             tr("Cannot save file"));
        return false;
    }
    QTextStream out(&file);
    out << ui->textedit->toPlainText();
    setWindowTitle(filename);
    file.close();
    return true;
}

void Editor::loadfile(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Warning"),
                             tr("Cannot load file"));
        return;
    }
    QTextStream in(&file);
    ui->textedit->setText(in.readAll());
    setWindowTitle(filename);
    file.close();
}

void Editor::setfontbold(bool bold)
{
    bold ? ui->textedit->setFontWeight(QFont::Bold) :
        ui->textedit->setFontWeight(QFont::Normal);
}

void Editor::setfontunderline(bool underline)
{
    ui->textedit->setFontUnderline(underline);
}

void Editor::setfontitalic(bool italic)
{
    ui->textedit->setFontItalic(italic);
}

void Editor::about()
{
    QMessageBox::about(this, tr("About me"),
                       tr("Rexallina about Qt.\n"
                          "And test me about"));
}

void Editor::print()
{
    QPrinter printer;
    QPrintDialog dialogprinter(&printer, this);
    if (dialogprinter.exec() == QDialog::Rejected)
        return;
    ui->textedit->print(&printer);
}
