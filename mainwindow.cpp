#include <QtGui>

#include "mainwindow.h"

#include "meshviewwidget.h"
#include "loadmeshthread.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{


    setWindowTitle("3D cloud crop");

    MeshViewWidget *meshViewWidget = new MeshViewWidget();
    setCentralWidget(meshViewWidget);


    // Create thread that will load mesh file
    loadMeshThread = new LoadMeshThread(meshViewWidget, this);

    createActions();
    createMenu();
}

MainWindow::~MainWindow()
{

}

void MainWindow::openMeshFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                            tr("Open obj file to crop"),
                                            "",
                                            tr("Wavefrom OBJ(*.obj)"));
    loadMeshThread->loadMesh(fileName);
}

void MainWindow::createActions()
{
    // Open file action
    openMeshFileAction = new QAction(QIcon(":/images/open.png"), QString("&Open"), this);
    openMeshFileAction->setShortcut(QKeySequence::Open);
    connect(openMeshFileAction, SIGNAL(triggered()), this, SLOT(openMeshFile()));
}

void MainWindow::createMenu()
{
    QMenuBar *menubar = menuBar();
    QMenu *file = menubar->addMenu("&File");
    file->addAction(openMeshFileAction);
}
