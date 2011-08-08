#include <QDebug>
#include <QtOpenGL>

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "loadmeshthread.h"
#include "meshviewwidget.h"
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

template <class T>
T* vector_to_pointer(vector<T> &v)
{
    typename vector<T>::iterator it;

    T* p = v.empty() ? NULL : &v[0] + (it - v.begin());
    return p;
}

LoadMeshThread::LoadMeshThread(MeshViewWidget *_meshViewWidget, QObject *parent) :
    QThread(parent), meshViewWidget(_meshViewWidget)
{

}

void LoadMeshThread::loadMesh(QString fileName)
{
    this->fileName = fileName;

    if(isRunning() == false)
        start();
}

void LoadMeshThread::run()
{
    qDebug() << "Making context of glwidget current";
    qDebug() << "Attempting to load wavefront file:" << fileName;

    vector<GLfloat> vertices_coordinates;
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

                    vertices_coordinates.push_back(first_coordinate);
                    vertices_coordinates.push_back(second_coordinate);
                    vertices_coordinates.push_back(third_coordinate);
            }
    }

    qDebug() << "Number of vertices:" << vertices_coordinates.size();
    in.close();

    GLuint verticesVboId;

    glGenBuffers(1, &verticesVboId);

//    qDebug() << "glGenBuffersARB" << glGenBuffersARB;
//    glGenBuffersARB( 1, &verticesVboId );
//    qDebug() << "glGenBuffersARB( 1, &verticesVboId );";

//    glBindBufferARB( GL_ARRAY_BUFFER_ARB, verticesVboId );
//    qDebug() << "glBindBufferARB( GL_ARRAY_BUFFER_ARB, verticesVboId );";

//    glBufferDataARB( GL_ARRAY_BUFFER_ARB,
//                     vertices_coordinates.size()*3*sizeof(GLfloat),
//                     vector_to_pointer(vertices_coordinates),
//                     GL_STATIC_DRAW_ARB );
//    qDebug() << "glBufferDataARB";
}
