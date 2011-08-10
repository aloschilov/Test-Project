#ifndef GLOPERATIONSTHREAD_H
#define GLOPERATIONSTHREAD_H

#include <QtGui>
#include <QtOpenGL>
#include <vector>

class GLWidget;

class GLOperationThread : public QThread
{
    Q_OBJECT

public:
    GLOperationThread(GLWidget *meshViewWidget);

signals:
    void meshFileSuccessfullyLoaded();

public slots:
    void loadMesh(QString fileName);
    void resizeViewport(const QSize &size);
    void render();

protected:
    void run();
    bool isExtensionSupported(char *targetExtension);

private:
    QString fileName;
    GLWidget *glw;

    bool doRendering;
    int w;
    int h;
    int rotAngle;

    std::vector<GLfloat> loadedVerticesCoordinates;
    std::vector<GLfloat> croppedVecticesCoordinates;
};

#endif // GLOPERATIONSTHREAD_H
