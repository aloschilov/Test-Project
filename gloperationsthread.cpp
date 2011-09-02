#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "gloperationsthread.h"
#include "glwidget.h"
#include "glextensions.h"
#include "scale.h"

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
    this->moveToThread(this);
    loadedVerticesVboId = 0;
    loadedVerticesColorVboId = 0;
    applyScale = false;
}

void GLOperationThread::loadMesh(QString fileName)
{
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


    glGenBuffers(1, &loadedVerticesVboId);
    glBindBuffer(GL_ARRAY_BUFFER, loadedVerticesVboId);
    glBufferData(GL_ARRAY_BUFFER,
                 loadedVerticesCoordinates.size()*sizeof(GLfloat),
                 to_send,
                 GL_STATIC_DRAW );

    delete to_send;
}

void GLOperationThread::resizeViewport(const QSize &size)
{
    if (doRendering)
    {
        int width = size.width();
        int height = size.height();
        int side = qMin(width, height);

        glViewport((width - side) / 2, (height - side) / 2, side, side);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        //glOrtho(-0.5, +0.5, -0.5, +0.5, 4.0, 15.0);
        glMatrixMode(GL_MODELVIEW);
    }
}

void GLOperationThread::render()
{

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
        glColor3f(1.0f,1.0f,1.0f);
        glEnableClientState(GL_VERTEX_ARRAY);

        if (applyScale)
        {
            glEnableClientState(GL_COLOR_ARRAY);
        }

        glBindBuffer( GL_ARRAY_BUFFER, loadedVerticesVboId );
        glVertexPointer( 3, GL_FLOAT, 0, 0);

        if (applyScale)
        {
            glBindBuffer( GL_ARRAY_BUFFER, loadedVerticesColorVboId);
            glColorPointer( 4, GL_FLOAT, 0, 0);
        }

        glDrawArrays( GL_POINTS , 0, loadedVerticesCoordinates.size()/3);

        if (applyScale)
        {
            glDisableClientState(GL_COLOR_ARRAY);
        }

        glDisableClientState(GL_VERTEX_ARRAY);
    }

    glw->swapBuffers();
}

void GLOperationThread::run()
{
    glw->makeCurrent();

    if (!getGLExtensionFunctions().resolve(glw->context()))
    {
        return;
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);

    doRendering = true;
    resizeViewport(glw->geometry().size());

    exec();
    glw->doneCurrent();
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

static inline void qSetColor(GLfloat colorVec[], QColor c)
{
    colorVec[0] = c.redF();
    colorVec[1] = c.greenF();
    colorVec[2] = c.blueF();
    colorVec[3] = c.alphaF();
}

void GLOperationThread::setScale(Scale *scale)
{
    if (loadedVerticesCoordinates.size() == 0 )
        return;

    if (applyScale)
    {
        glDeleteBuffers(1, &loadedVerticesColorVboId);
    }

    GLuint numberOfColorComponents = (loadedVerticesCoordinates.size()/3)*4;
    GLuint numberOfVerticesComponents = loadedVerticesCoordinates.size()/3;

    // Adjusting scale to points array

    GLfloat maxZ;
    int i = 0;
    maxZ = loadedVerticesCoordinates[i*3+2];
    do {
        ++i;
        if (maxZ < loadedVerticesCoordinates[i*3+2])
        {
            maxZ = loadedVerticesCoordinates[i*3+2];
        }
    } while(i<numberOfVerticesComponents);

    GLfloat minZ;
    minZ = loadedVerticesCoordinates[i*3+2];
    do {
        ++i;
        if (minZ < loadedVerticesCoordinates[i*3+2])
        {
            minZ = loadedVerticesCoordinates[i*3+2];
        }
    } while(i<numberOfVerticesComponents);

    scale->setMaxValue(maxZ);
    scale->setMinValue(minZ);

    GLfloat *to_send = new GLfloat[numberOfColorComponents];

    for(int i=0; i<numberOfVerticesComponents;++i)
    {
        QColor color;
        color.setRgba(scale->getColor(loadedVerticesCoordinates[i*3+2]));
        qSetColor(&to_send[i*4],color);
    }

    glGenBuffers(1, &loadedVerticesColorVboId);
    glBindBuffer(GL_ARRAY_BUFFER, loadedVerticesColorVboId);
    glBufferData(GL_ARRAY_BUFFER,
                 numberOfColorComponents*sizeof(GLfloat),
                 to_send,
                 GL_STATIC_DRAW );

    delete to_send;

    applyScale = true;
    render();
}
