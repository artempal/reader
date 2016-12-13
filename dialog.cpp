#include "dialog.h"
#include "ui_dialog.h"

// Как передать сюда file_name, Page, MaxLine??????????????????????????????????????????????????????
// Наследование почему-то не получается
int Page2 = 1;
int const MaxLine2 = 25;

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui2(new Ui::Dialog)
{
    ui2->setupUi(this);
    connect(ui2->Close,SIGNAL(clicked()),this, SLOT (close()));
    connect(ui2->spinBox,SIGNAL(valueChanged(Page)),this, SLOT (OpenPage()));
}

Dialog::~Dialog()
{
    delete ui2;
}

void Dialog:: OpenPage()
{

}

void Dialog:: CountPages()
{
    QFile file(file_name); // создаем объект класса QFile
    if (!file.open(QIODevice::ReadOnly)) // проверяем, возможно ли открыть наш файл для чтения
    {
        qDebug() << "Ошибка чтения файла(4)";
        return; // если это сделать невозможно, то завершаем функцию
    }
    QTextStream stream(&file);
    QString str;
    int nline = 1, Pages = 1;
    while( stream.atEnd() )
    {
     str = stream.readLine(125);// считывание строки
            if(stream.atEnd())   break;
     nline++;
    }
    file.close();
    if(nline % MaxLine2  != 0)
        Pages = MaxLine2 + 1;
    else
        Pages = nline;
    ui2->textEdit->append(QString :: number(Pages) );

}
