#include <QtGui>
#include <QtOpenGL>

#include <math.h>

#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    glt = new GLOperationThread(this);

    xRot = 0;
    yRot = 0;
    zRot = 0;

    setAutoBufferSwap(false);

    connect(this, SIGNAL(paintRequested()), glt, SLOT(render()));
    connect(this, SIGNAL(resizeRequested(QSize)), glt, SLOT(resizeViewport(QSize)));
}

GLWidget::~GLWidget()
{

}

GLOperationThread *GLWidget::getGLOperationThread()
{
    return glt;
}

void GLWidget::showEvent ( QShowEvent * event )
{
    if (glt->isRunning() == false)
    {
        glt->start();
    }
}

void GLWidget::resizeEvent(QResizeEvent *evt)
{
    emit resizeRequested(evt->size());
}

void GLWidget::paintEvent(QPaintEvent *)
{
    emit paintRequested();
}

void GLWidget::closeEvent(QCloseEvent *evt)
{
    qDebug() << ">>> void GLWidget::closeEvent(QCloseEvent *evt)";
    glt->quit();
    glt->wait();
    delete glt;
    GLWidget::closeEvent(evt);
    qDebug() << "<<< void GLWidget::closeEvent(QCloseEvent *evt)";
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(xRot + 8 * dy);
        setYRotation(yRot + 8 * dx);
    } else if (event->buttons() & Qt::RightButton) {
        setXRotation(xRot + 8 * dy);
        setZRotation(zRot + 8 * dx);
    }
    lastPos = event->pos();
}

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;
}

void GLWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
        emit xRotationChanged(angle);
    }
}

void GLWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        emit yRotationChanged(angle);
    }
}

void GLWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
        emit zRotationChanged(angle);
    }
}
