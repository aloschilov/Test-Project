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

    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);

protected:
    void run();

private:
    QString fileName;
    GLWidget *glw;

    bool doRendering;
    int w;
    int h;
    int rotAngle;

    std::vector<GLfloat> loadedVerticesCoordinates;
    std::vector<GLfloat> croppedVecticesCoordinates;
    GLuint loadedVerticesVboId;
    QMutex glmutex;

    size_t loadedNumberOfVertices;

    GLfloat midX;
    GLfloat midY;
    GLfloat midZ;

    int xRot;
    int yRot;
    int zRot;
};

#endif // GLOPERATIONSTHREAD_H
