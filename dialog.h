#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>
#include <QFile>
#include <QByteArray>
#include <QString>
#include "mywindow1.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    QString file_name;
    Ui::Dialog *ui2;
private slots:
    void CountPages(); // колличество страниц в книге
    void OpenPage(); // открыть определенную страницу
};

#endif // DIALOG_H
