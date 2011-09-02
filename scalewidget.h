#ifndef SCALEWIDGET_H
#define SCALEWIDGET_H

#include <QWidget>

class Scale;

class ScaleWidget : public QWidget
{
    Q_OBJECT
public:
    ScaleWidget(QWidget *parent=0);
public slots:
    void changeScale(Scale *newScale);
protected:
    void paintEvent(QPaintEvent * /*event*/);
private:
    Scale *scale;
};

#endif // SCALEWIDGET_H

