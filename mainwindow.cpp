#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->prev_btn->hide(); //делаем кнопки вперед-назад неактивными
    ui->next_btn->hide();
//    Коннекторы связывают кнопки и другие действия с функциями
   connect(ui->open_book,SIGNAL(triggered()),this,SLOT(book_open())); //при нажатии пункта меню Открыть книгу сработает функция book_open
   connect(ui->open_dir,SIGNAL(triggered()),this,SLOT(dir_open())); //при нажатии пункта меню Открыть папку сработает функция dir_open
   connect(ui->prev_btn,SIGNAL(clicked()),this,SLOT(prev_page())); //настроим функции при нажатии на кнопки вперед-назад
   connect(ui->next_btn,SIGNAL(clicked()),this,SLOT(next_page()));
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
void MainWindow::get_book()
{
    QFile file(file_name); // создаем объект класса QFile
    if (!file.open(QIODevice::ReadOnly)) // проверяем, возможно ли открыть наш файл для чтения
    return; // если это сделать невозможно, то завершаем функцию
    QByteArray data = file.readAll(); //читаем весь текст книги в переменную
    QString book_text = (QString) data; //преобразуем в QString
    ui->book_text->setText(book_text); //выводим первую страницу (правда я пока не понял, как выводить определенное кол-во строк, поэтому вывел всю книгу, тут надо думать
    ui->next_btn->show(); //делаем активной кнопку вперед
}
void MainWindow::next_page()
{

}
void MainWindow::prev_page()
{

}
