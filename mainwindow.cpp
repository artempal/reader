#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->prev_btn->setEnabled(false); //делаем кнопки вперед-назад неактивными
    ui->next_btn->setEnabled(false);
    ui->PageNumber->hide();
    ui->label->hide();
    ui->DesiredPage->setEnabled(false);
//    Коннекторы связывают кнопки и другие действия с функциями
   connect(ui->open_book,SIGNAL(triggered()),this,SLOT(book_open())); //при нажатии пункта меню Открыть книгу сработает функция book_open
   connect(ui->open_dir,SIGNAL(triggered()),this,SLOT(dir_open())); //при нажатии пункта меню Открыть папку сработает функция dir_open
   connect(ui->prev_btn,SIGNAL(clicked()),this,SLOT(prev_page())); //настроим функции при нажатии на кнопки вперед-назад
   connect(ui->next_btn,SIGNAL(clicked()),this,SLOT(next_page()));
   connect(ui->DesiredPage,SIGNAL(triggered()),this,SLOT(OpenMyPage()));
   connect(ui->MakeMark,SIGNAL(triggered),this,SLOT(MakeBookmark()));
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
    if(!file_name.isNull()) OpenPage(1); //если имя файла получено - читаем первую страницу книги
}


void MainWindow::dir_open()
{
    file_dir = QFileDialog::getExistingDirectory(0, "Выбрать папку с книгами", "");
}


void MainWindow::next_page()
{
    Page++;
    OpenPage(Page );
    ui->prev_btn->setEnabled(true);
}


void MainWindow::prev_page()
{
    Page--;
    OpenPage(Page);
    ui->next_btn->setEnabled(true);
}


void MainWindow :: OpenMyPage()
{
    Dialog *mwd = new Dialog(this,&file_name); //передадим имя файла в диалог
    connect(mwd,SIGNAL(sendData(int)),this,SLOT(OpenPage(int))); //ловим сигнал обновления из диалога ввода и запускаем обработку данных
    mwd->show();
}


void MainWindow:: OpenPage(int num)
{
    qDebug() << num;
    Page = num;
    ui->PageNumber->setValue(num);
    ui->book_text->clear();
    if(Page==0) OpenPage(1);

    QFile file(file_name); // создаем объект класса QFile
    if (!file.open(QIODevice::ReadOnly)) // проверяем, возможно ли открыть наш файл для чтения
    {
        qDebug() << "Ошибка чтения файла(5)";
        return; // если это сделать невозможно, то завершаем функцию
    }

    QTextStream stream(&file);
    QString str;
    int nline = 1;

    if(num == 1 )
    {
        ui->prev_btn->setEnabled(false);
        while( nline <=  MaxLine )
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
        ui->next_btn->setEnabled(true); //делаем активной кнопку вперед
        ui->label->show();
        ui->PageNumber->show();
        ui->DesiredPage->setEnabled(true);
        ui->PageNumber->setValue(Page);
    }
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
                ui->next_btn->setEnabled(false);
                ui->book_text->setTextColor(Qt::red);
                ui->book_text->append( "Конец книги");
                ui->book_text->setTextColor(Qt::black);
                break;
            }
        nline++;
    }
    file.close();
}


/*void MainWindow:: MakeBookmark()
{
    QFile File();
}
*/
