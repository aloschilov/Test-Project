#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include "gloperationsthread.h"


class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    GLWidget(QWidget *parent = 0);
    ~GLWidget();

    GLOperationThread *getGLOperationThread();

public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);

signals:
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);
    void paintRequested();
    void resizeRequested(QSize);

protected:
    void showEvent ( QShowEvent * event );
    void resizeEvent(QResizeEvent *);
    void paintEvent(QPaintEvent *);
    void closeEvent(QCloseEvent *);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    GLOperationThread *glt;

    int xRot;
    int yRot;
    int zRot;

    QPoint lastPos;
};

#endif // GLWIDGET_H
