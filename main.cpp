#include "mainwindow.h"
#include <QApplication>
#include "tree.h"
#include<QDebug>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Tree A;
    A.FillTree();
    MainWindow w;
    w.show();
    return a.exec();
}
