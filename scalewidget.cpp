#include <QtGui>

#include "scale.h"
#include "scalewidget.h"

ScaleWidget::ScaleWidget(QWidget *parent)
    : QWidget(parent)
{
    scale=0;
}

void ScaleWidget::paintEvent(QPaintEvent * /*event*/)
{
    QPainter p(this);

    p.setRenderHint(QPainter::Antialiasing);
    p.setRenderHint(QPainter::SmoothPixmapTransform);

    if(scale)
    {
        double maxValue = scale->getMaxValue();
        double minValue = scale->getMinValue();
        double step = (maxValue - minValue)/double(rect().height());
        int height = rect().height();
        double curValue;
        for(int i=0;i<height;++i)
        {
            curValue=maxValue - double(i)*step;
            p.setPen(QColor(QColor::fromRgb(scale->getColor(curValue))));
            p.drawLine(0,i,rect().width(),i);
        }
    }
}

void ScaleWidget::changeScale(Scale *newScale)
{
    scale=newScale;
    update();
}
