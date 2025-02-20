#ifndef EDITOR_H
#define EDITOR_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class Editor;
}
QT_END_NAMESPACE

class Editor : public QMainWindow
{
    Q_OBJECT

public:
    Editor(QWidget *parent = nullptr);
    ~Editor();

private slots:
    bool maybesave();
    bool save();
    bool saveas();
    void newfile();
    void open();
    void about();
    void exit();

private:
    QString currentfile;
    bool savefile(const QString &filename);
    void loadfile(const QString &filename);
    void setfontbold(bool bold);
    void setfontitalic(bool italic);
    void setfontunderline(bool underline);
    Ui::Editor *ui;
};
#endif // EDITOR_H
