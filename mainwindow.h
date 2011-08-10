#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void gotFileNameToLoad(QString filename);

private slots:
    void openMeshFile();

private:
    void createActions();
    void createMenu();

    QAction *openMeshFileAction;
};

#endif // MAINWINDOW_H
