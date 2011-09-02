#ifndef SCALE_H
#define SCALE_H

#include <QImage>
#include <vector>

class Scale
{
public:
    Scale(const std::vector<QRgb>& pointsToInitScale);
    QRgb getColor(double value);
    void setMinValue(double newMinValue);
    void setMaxValue(double newMaxValue);
    double getMaxValue() const {return maxValue;}
    double getMinValue() const {return minValue;}
private:
    double minValue;
    double maxValue;
    double step;
    std::vector<QRgb> scalePoints;
};

#endif // SCALE_H
