#ifndef GLOPERATIONSTHREAD_H
#define GLOPERATIONSTHREAD_H

#include <QtGui>
#include <QtOpenGL>
#include <vector>

class GLWidget;
class Scale;

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
    void setScale(Scale *scale);

protected:
    void run();

private:
    QString fileName;
    GLWidget *glw;

    Scale *scale;

    bool doRendering;
    bool applyScale;

    int w;
    int h;
    int rotAngle;

    std::vector<GLfloat> loadedVerticesCoordinates;
    std::vector<GLfloat> croppedVecticesCoordinates;

    GLuint loadedVerticesVboId;
    GLuint loadedVerticesColorVboId;

    GLfloat midX;
    GLfloat midY;
    GLfloat midZ;

    int xRot;
    int yRot;
    int zRot;
};

#endif // GLOPERATIONSTHREAD_H
