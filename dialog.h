#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>
#include <QFile>
#include <QByteArray>
#include <QString>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0, QString *in_file_name = 0);
    ~Dialog();

private:
    QString file_name;
    Ui::Dialog *ui2;
private slots:
    void CountPages(); // колличество страниц в книге
    void OpenPage(int); // открыть определенную страницу
    //void onSendData();
signals:
    void sendData(int);
};

#endif // DIALOG_H
