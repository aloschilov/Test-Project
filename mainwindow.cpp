#include <QtGui>

#include "mainwindow.h"

#include "meshviewwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *tempWidget = new MeshViewWidget();

    setCentralWidget(tempWidget);
}

MainWindow::~MainWindow()
{

}
