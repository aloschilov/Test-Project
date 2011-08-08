#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>

class LoadMeshThread;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void openMeshFile();

private:
    void createActions();
    void createMenu();

    QAction *openMeshFileAction;

    LoadMeshThread *loadMeshThread;
};

#endif // MAINWINDOW_H
