#include "scale.h"
#include "colormapradiobutton.h"

using namespace std;

ColormapRadioButton::ColormapRadioButton(const QString &text,const QString &filename,QWidget *parent)
    : QRadioButton(text,parent)
{
    scale=0;
    QImage imageToPrepareScalePoints;
    imageToPrepareScalePoints.load(filename);
    int width = imageToPrepareScalePoints.width();
    vector<QRgb> vectorToInitScale;

    for(int i=0;i<width;++i)
    {
        vectorToInitScale.push_back(imageToPrepareScalePoints.pixel(i,0));
    }

    scale = new Scale(vectorToInitScale);
    connect(this,SIGNAL(toggled(bool)),this,SLOT(reemitClickedWithScale(bool)));
}
