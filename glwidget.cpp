#include <QtGui>
#include <QtOpenGL>

#include <math.h>

#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent, 0), glt(this)
{
    setAutoBufferSwap(false);
    resize(320, 240);

    connect(this, SIGNAL(paintRequested()), &glt, SLOT(render()));
    connect(this, SIGNAL(resizeRequested(QSize)), &glt, SLOT(resizeViewport(QSize)));
    glt.start();
}

GLWidget::~GLWidget()
{
    qDebug() << "Close event";
    glt.quit();
    glt.wait();
}

GLOperationThread *GLWidget::getGLOperationThread()
{
    return &glt;
}

void GLWidget::resizeEvent(QResizeEvent *evt)
{
    emit resizeRequested(evt->size());
    //glt.resizeViewport(evt->size());
}

void GLWidget::paintEvent(QPaintEvent *)
{
    emit paintRequested();
}

void GLWidget::closeEvent(QCloseEvent *evt)
{
    QGLWidget::closeEvent(evt);
}
