#ifndef LOADMESHTHREAD_H
#define LOADMESHTHREAD_H

#include <QThread>

class MeshViewWidget;

class LoadMeshThread : public QThread
{
    Q_OBJECT
public:
    explicit LoadMeshThread(MeshViewWidget *meshViewWidget, QObject *parent = 0);

signals:
    void meshFileSuccessfullyLoaded();

public slots:
    void loadMesh(QString fileName);

protected:
    void run();

private:
    QString fileName;
    MeshViewWidget *meshViewWidget;
};

#endif // LOADMESHTHREAD_H
