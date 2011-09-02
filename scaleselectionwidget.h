#ifndef SCALESELECTIONWIDGET_H
#define SCALESELECTIONWIDGET_H

#include <QWidget>

class Scale;
class ScaleWidget;

class ScaleSelectionWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ScaleSelectionWidget(QWidget *parent = 0);

signals:
    void scaleChanged(Scale *scale);

public slots:
    void setScalePointer(Scale *scale);

private:
    Scale *scale;
    ScaleWidget *scaleWidget;
};

#endif // SCALESELECTIONWIDGET_H
