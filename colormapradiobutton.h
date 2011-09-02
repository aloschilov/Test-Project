#ifndef COLORMAPRADIOBUTTON_H
#define COLORMAPRADIOBUTTON_H

#include <QRadioButton>

class Scale;

class ColormapRadioButton : public QRadioButton
{
    Q_OBJECT
public:
    ColormapRadioButton(const QString &text,const QString &filename,QWidget *parent=0);
    Scale *getScale() const {return scale;}
signals:
    void scaleChoosen(Scale *scale);
private slots:
    void reemitClickedWithScale(bool checked){if(checked) emit scaleChoosen(scale);}
private:
    Scale *scale;
};

#endif // COLORMAPRADIOBUTTON_H

