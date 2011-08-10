#include <QtGui>

#include "mainwindow.h"

#include "glwidget.h"
#include "gloperationsthread.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("3D cloud crop");

    GLWidget *glWidget = new GLWidget();
    setCentralWidget(glWidget);

    createActions();
    createMenu();

    connect(this, SIGNAL(gotFileNameToLoad(QString)),glWidget->getGLOperationThread(),SLOT(loadMesh(QString)));
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
    emit gotFileNameToLoad(fileName);
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
