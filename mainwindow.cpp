#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"

//int Page = 1;
//int const MaxLine = 25;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->prev_btn->hide(); //делаем кнопки вперед-назад неактивными
    ui->next_btn->hide();
    ui->PageNumber->hide();
    ui->label->hide();
//    Коннекторы связывают кнопки и другие действия с функциями
   connect(ui->open_book,SIGNAL(triggered()),this,SLOT(book_open())); //при нажатии пункта меню Открыть книгу сработает функция book_open
   connect(ui->open_dir,SIGNAL(triggered()),this,SLOT(dir_open())); //при нажатии пункта меню Открыть папку сработает функция dir_open
   connect(ui->prev_btn,SIGNAL(clicked()),this,SLOT(prev_page())); //настроим функции при нажатии на кнопки вперед-назад
   connect(ui->next_btn,SIGNAL(clicked()),this,SLOT(next_page()));
   //connect(ui->PageNumber,SIGNAL(valueChanged(QString)),this,SLOT(OpenPage())); // при вводе номера страницы , открыть ее
   connect(ui->DesiredPage,SIGNAL(triggered()),this,SLOT(OpenMyPage()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::book_open()
{
    QString dir;
    if(file_dir.isEmpty()) //если уже выбрана папка задаем стартовую директорию файловому диалогу
    {
        dir = file_dir;
    }
    file_name = QFileDialog::getOpenFileName(0, "Выбрать книгу", dir, "*.txt");
    if(!file_name.isNull()) get_book(); //если имя файла получено - читаем первую страницу книги
}
void MainWindow::dir_open()
{
    file_dir = QFileDialog::getExistingDirectory(0, "Выбрать папку с книгами", "");
}
void MainWindow::get_book() // Функция чтения книги
{
    QFile file(file_name); // создаем объект класса QFile
    if (!file.open(QIODevice::ReadOnly)) // проверяем, возможно ли открыть наш файл для чтения
    {
        qDebug() << "Ошибка чтения файла(1)";
        return; // если это сделать невозможно, то завершаем функцию
    }
    QTextStream stream(&file);
    QString str;
    int nline = 1;
    while( nline <= MaxLine )
    {
     str = stream.readLine(125);// считывание строки
     ui->book_text->append(str);// вывод строки на экран
            if(stream.atEnd())
            {
                ui->book_text->setTextColor(Qt::red);
                ui->book_text->append( "Конец книги");
                ui->book_text->setTextColor(Qt::black);
                ui->next_btn->setEnabled(false);
                break;
            }
        nline++;
    }
    file.close();
    ui->next_btn->show(); //делаем активной кнопку вперед
    ui->label->show();
    ui->PageNumber->show();
    ui->PageNumber->setValue(Page);

}
void MainWindow::next_page()
{
ui->book_text->clear();

QFile file(file_name); // создаем объект класса QFile
if (!file.open(QIODevice::ReadOnly)) // проверяем, возможно ли открыть наш файл для чтения
{
    qDebug() << "Ошибка чтения файла(2)";
    return; // если это сделать невозможно, то завершаем функцию
}
QTextStream stream(&file);
QString str;
int nline = 1;
Page++;
ui->PageNumber->setValue(Page);
while( nline <= Page * MaxLine )
{

 str = stream.readLine(125);// считывание строки
 if(nline <= (Page - 1) * MaxLine )
 {
     nline++;
     continue;
 }
 ui->book_text->append(str);// вывод строки на экран
        if(stream.atEnd())
        {
            ui->book_text->setTextColor(Qt::red);
            ui->book_text->append( "Конец книги");
            ui->book_text->setTextColor(Qt::black);
            ui->next_btn->setEnabled(false);
            break;
        }
    nline++;
}
file.close();
qDebug()<<Page;
ui->prev_btn->show();

}
void MainWindow::prev_page()
{
    ui->book_text->clear();

    QFile file(file_name); // создаем объект класса QFile
    if (!file.open(QIODevice::ReadOnly)) // проверяем, возможно ли открыть наш файл для чтения
    {
        qDebug() << "Ошибка чтения файла(3)";
        return; // если это сделать невозможно, то завершаем функцию
    }
    QTextStream stream(&file);
    QString str;
    int nline = 1;
    Page-- ;
    ui->PageNumber->setValue(Page);
    if(Page == 1 ) ui->prev_btn->setEnabled(false);
    while( nline <= Page * MaxLine )
    {

     str = stream.readLine(125);// считывание строки
     if(nline <= (Page - 1) * MaxLine )
     {
         nline++;
         continue;
     }
     ui->book_text->append(str);// вывод строки на экран
            if(stream.atEnd())
            {
                ui->book_text->setTextColor(Qt::red);
                ui->book_text->append( "Конец книги");
                ui->book_text->setTextColor(Qt::black);
                ui->next_btn->setEnabled(false);
                break;
            }
        nline++;
    }
    file.close();
    qDebug()<<Page;
}

void MainWindow :: OpenMyPage()
{
    Dialog *mwd = new Dialog(this,file_name); //передадим имя файла в диалог
    mwd->show();
}

/*
void MainWindow:: OpenPage()
{
    ui->book_text->clear();
  //  ui->PageNumber->setValue(););
    QFile file(file_name); // создаем объект класса QFile
    if (!file.open(QIODevice::ReadOnly)) // проверяем, возможно ли открыть наш файл для чтения
    {
        qDebug() << "Ошибка чтения файла(4)";
        return; // если это сделать невозможно, то завершаем функцию
    }
    QTextStream stream(&file);
    QString str;
    int nline = 1;
    if(Page == 1 ) ui->prev_btn->setEnabled(false);
    while( nline <= Page * MaxLine )
    {
     str = stream.readLine(125);// считывание строки
     if(nline <= (Page - 1) * MaxLine )
     {
         nline++;
         continue;
     }
     ui->book_text->append(str);// вывод строки на экран
            if(stream.atEnd())
            {
                ui->book_text->setTextColor(Qt::red);
                ui->book_text->append( "Конец книги");
                ui->book_text->setTextColor(Qt::black);
                ui->next_btn->setEnabled(false);
                break;
            }
        nline++;
    }
    file.close();
    qDebug()<<Page;
}
*/
