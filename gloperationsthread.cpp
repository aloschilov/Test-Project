#include <QDebug>


#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "gloperationsthread.h"
#include "glwidget.h"
#include "glextensions.h"

#include "ComputerGraphics/matrix.h"
#include "ComputerGraphics/linalg.h"

using namespace std;
using namespace Aloschil;


double string_to_double( const std::string& s ) {
        istringstream i(s);
        double x;
        if (!(i >> x))
                return 0;

        return x;
}

GLOperationThread::GLOperationThread(GLWidget *_glw) :
    QThread(), glw(_glw), xRot(0), yRot(0), zRot(0), doRendering(false)
{
    qDebug() << ">>> GLOperationThread::GLOperationThread()";
    this->moveToThread(this);
    loadedVerticesVboId = 0;
    qDebug() << "<<< GLOperationThread::GLOperationThread()";
}

void GLOperationThread::loadMesh(QString fileName)
{
    qDebug() << ">>> void GLOperationThread::loadMesh(QString fileName)";
    QMutexLocker lock(&glmutex);
    ifstream in(fileName.toStdString().c_str(), ios::in);
    string current_token;

    while(!in.eof()) {
        in >> current_token;
        if (current_token == string("v")) {
            double first_coordinate;
            double second_coordinate;
            double third_coordinate;

            in >> current_token;
            first_coordinate = string_to_double(current_token);
            in >> current_token;
            second_coordinate = string_to_double(current_token);
            in >> current_token;
            third_coordinate = string_to_double(current_token);

            loadedVerticesCoordinates.push_back(first_coordinate);
            loadedVerticesCoordinates.push_back(second_coordinate);
            loadedVerticesCoordinates.push_back(third_coordinate);
        }
    }

    in.close();

    GLfloat *to_send = new GLfloat[loadedVerticesCoordinates.size()];

    for(int i=0; i<loadedVerticesCoordinates.size();++i) {
        to_send[i] = loadedVerticesCoordinates[i];
    }


    loadedNumberOfVertices = loadedVerticesCoordinates.size()/3;

    glGenBuffers(1, &loadedVerticesVboId);
    glBindBuffer(GL_ARRAY_BUFFER, loadedVerticesVboId);
    glBufferData(GL_ARRAY_BUFFER,
                 loadedVerticesCoordinates.size()*sizeof(GLfloat),
                 to_send,
                 GL_STATIC_DRAW );

    delete to_send;

    qDebug() << "<<< void GLOperationThread::loadMesh(QString fileName)";
}

void GLOperationThread::resizeViewport(const QSize &size)
{
    qDebug() << ">>> void GLOperationThread::resizeViewport(const QSize &size)";

    if (doRendering)
    {
        int width = size.width();
        int height = size.height();
        int side = qMin(width, height);

        qDebug() << "glViewport with";
        qDebug() << "side: " << side;
        qDebug() << "width: " << width;
        qDebug() << "height: " << height;

        glViewport((width - side) / 2, (height - side) / 2, side, side);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        //glOrtho(-0.5, +0.5, -0.5, +0.5, 4.0, 15.0);
        glMatrixMode(GL_MODELVIEW);
    }

    qDebug() << "<<< void GLOperationThread::resizeViewport(const QSize &size)";
}

void GLOperationThread::render()
{
    qDebug() << ">>> void GLOperationThread::render()";
    QMutexLocker lock(&glmutex);

    if(doRendering == false)
        return;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glRotatef(xRot, 1.0, 0.0, 0.0);
    glRotatef(yRot, 0.0, 1.0, 0.0);
    glRotatef(zRot, 0.0, 0.0, 1.0);

    glScalef(0.01,0.01,0.01);

    if (loadedVerticesCoordinates.size() != 0 )
    {
        qDebug() << "   >>> if (loadedVerticesCoordinates.size() != 0 )";

        glColor3f(1.0f,1.0f,1.0f);
        glEnableClientState(GL_VERTEX_ARRAY);
        glBindBuffer( GL_ARRAY_BUFFER, loadedVerticesVboId );
        glVertexPointer( 3, GL_FLOAT, 0,  0);
        glDrawArrays( GL_POINTS , 0, loadedVerticesCoordinates.size()/3);
        glDisableClientState(GL_VERTEX_ARRAY);
        qDebug() << "   <<< if (loadedVerticesCoordinates.size() != 0 )";
    }

    glw->swapBuffers();
    qDebug() << "<<< void GLOperationThread::render()";
}

void GLOperationThread::run()
{
    qDebug() << ">>> void GLOperationThread::run()";
    glw->makeCurrent();

    glmutex.lock();


    if (!getGLExtensionFunctions().resolve(glw->context()))
    {
        qDebug() << "Failed to resolve OpenGL functions required";
        return;
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);

    doRendering = true;
    resizeViewport(glw->geometry().size());
    glmutex.unlock();

    exec();
    glw->doneCurrent();

    qDebug() << "<<< void GLOperationThread::run()";
}


void GLOperationThread::setXRotation(int angle)
{
    xRot = angle;
    render();
}

void GLOperationThread::setYRotation(int angle)
{
    yRot = angle;
    render();
}

void GLOperationThread::setZRotation(int angle)
{
    zRot = angle;
    render();
}
