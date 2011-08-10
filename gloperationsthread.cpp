#include <QDebug>


#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "gloperationsthread.h"
#include "glwidget.h"

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

template <class T>
T* vector_to_pointer(vector<T> &v)
{
    typename vector<T>::iterator it;

    T* p = v.empty() ? NULL : &v[0] + (it - v.begin());
    return p;
}

GLOperationThread::GLOperationThread(GLWidget *_glw) :
    QThread(), glw(_glw)
{
    this->moveToThread(this);
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

    qDebug() << "Number of vertices:" << loadedVerticesCoordinates.size();
    in.close();
}

void GLOperationThread::resizeViewport(const QSize &size)
{
    qDebug() << "resizeViewport()";
    w = size.width();
    h = size.height();
    glViewport(0, 0, w, h);
}

void GLOperationThread::render()
{
//    if(!doRendering)
//        return;
    qDebug() << "Trying to render";

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear The Screen And The Depth Buffer
    glLoadIdentity();                   // Reset The View
    glTranslatef(-1.5f,0.0f,-6.0f);             // Move Into The Screen And Left
    glRotatef(10,0.0f,1.0f,0.0f);             // Rotate The Triangle On The Y axis ( NEW )

    glBegin(GL_TRIANGLES);                  // Start Drawing A Triangle
        glColor3f(1.0f,0.0f,0.0f);          // Set Top Point Of Triangle To Red
        glVertex3f( 0.0f, 1.0f, 0.0f);          // First Point Of The Triangle
        glColor3f(0.0f,1.0f,0.0f);          // Set Left Point Of Triangle To Green
        glVertex3f(-1.0f,-1.0f, 0.0f);          // Second Point Of The Triangle
        glColor3f(0.0f,0.0f,1.0f);          // Set Right Point Of Triangle To Blue
        glVertex3f( 1.0f,-1.0f, 0.0f);          // Third Point Of The Triangle
    glEnd();                        // Done Drawing The Triangle

    glw->swapBuffers();
}

void GLOperationThread::run()
{
    qDebug() << "void GLOperationThread::run() glw->makeCurrent();";
    glw->makeCurrent();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-5.0, 5.0, -5.0, 5.0, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, 200, 200);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);

    exec();
    glw->doneCurrent();

//    GLuint verticesVboId;

//    glGenBuffers(1, &verticesVboId);

//    qDebug() << "glGenBuffersARB" << glGenBuffersARB;
//    glGenBuffersARB( 1, &verticesVboId );
//    qDebug() << "glGenBuffersARB( 1, &verticesVboId );";

//    glBindBufferARB( GL_ARRAY_BUFFER_ARB, verticesVboId );
//    qDebug() << "glBindBufferARB( GL_ARRAY_BUFFER_ARB, verticesVboId );";

//    glBufferDataARB( GL_ARRAY_BUFFER_ARB,
//                     loadedVerticesCoordinates.size()*3*sizeof(GLfloat),
//                     vector_to_pointer(loadedVerticesCoordinates),
//                     GL_STATIC_DRAW_ARB );
//    qDebug() << "glBufferDataARB";
}


bool GLOperationThread::isExtensionSupported(char *targetExtension)
{
    const unsigned char *extensions = NULL;
    const unsigned char *start;
    unsigned char *where;
    unsigned char *terminator;

    // Extension names should not have spaces
    where = (unsigned char*) strchr( targetExtension, ' ');
    if ( where || *targetExtension == '\0')
    {
        return false;
    }

    // Get extensions string
    extensions = glGetString( GL_EXTENSIONS );

    // Search the extensions string for an exact copy
    start = extensions;
    while(true)
    {
        where = (unsigned char*) strstr( (const char*) start, targetExtension );
        if ( !where )
        {
            break;
        }
        terminator = where + strlen( targetExtension );
        if( where == start || *(where - 1) == ' ')
            if( *terminator == ' ' || terminator == '\0')
                return true;
        start = terminator;
    }
    return false;
}
