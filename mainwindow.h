#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>
#include <QFile>
#include <QByteArray>
#include <QString>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int Page = 1;
    int const MaxLine = 25;
    int Mark = 1;
private:
    QString file_name; //имя открытого файла
    QString file_dir; //имя папки
    QString book_text; //текст открытой книги
    Ui::MainWindow *ui;
    int BookMark[200];
private slots:
    void dir_open(); //функция открытия папки
    void book_open(); //функция открытия книги
    void prev_page(); //функции кнопок
    void next_page();
    void OpenPage(int num );
    void OpenMyPage();
   // void MakeBookmark();
   /*
    void SeeBookmarks();// посмотреть закладки
    void SaveLastPlaceReading();// запомнить последнее место чтения
    void ContinueReading();// продолжить чтение */
};

#endif // MAINWINDOW_H
