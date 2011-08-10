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

signals:
    void paintRequested();
    void resizeRequested(QSize);

protected:
    void resizeEvent(QResizeEvent *);
    void paintEvent(QPaintEvent *);
    void closeEvent(QCloseEvent *);

    GLOperationThread glt;
};

#endif // GLWIDGET_H
