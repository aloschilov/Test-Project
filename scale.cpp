#include "scale.h"

using namespace std;

Scale::Scale(const vector<QRgb> &pointsToInitScale):
    scalePoints(pointsToInitScale)
{
    minValue = 0.0;
    maxValue = 1.0;

    // Step in numberic form between two points with known colors
    step = (maxValue - minValue)/double(scalePoints.size());
}

QRgb Scale::getColor(double value)
{
    if(value<=minValue) return scalePoints.front();
    if(value>=maxValue) return scalePoints.back();
    double tmp= (value-minValue)/step;
    size_t leftIndex = size_t(tmp);
    return scalePoints[leftIndex%scalePoints.size()];
}

void Scale::setMinValue(double newMinValue)
{
    minValue = newMinValue;
    step = (maxValue - minValue)/double(scalePoints.size());
}

void Scale::setMaxValue(double newMaxValue)
{
    maxValue = newMaxValue;
    step = (maxValue - minValue)/double(scalePoints.size());
}
