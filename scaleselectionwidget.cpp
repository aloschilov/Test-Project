#include <QtGui>

#include "scaleselectionwidget.h"
#include "colormapradiobutton.h"
#include "scalewidget.h"

ScaleSelectionWidget::ScaleSelectionWidget(QWidget *parent) :
    QWidget(parent)
{
    QGroupBox *colormapGroupBox = new QGroupBox;
    colormapGroupBox->setTitle(tr("Colormap"));

    ColormapRadioButton *fireColormapRadioButton =
            new ColormapRadioButton(tr("fire"),":colormaps/fire.bmp",colormapGroupBox);
    fireColormapRadioButton->setChecked(true);
    ColormapRadioButton *grayscaleColormapRadioButton =
            new ColormapRadioButton(tr("grayscale"),":colormaps/grayscale.bmp",colormapGroupBox);
    ColormapRadioButton *rainbowColormapRadioButton =
            new ColormapRadioButton(tr("rainbow"),":colormaps/rainbow.bmp",colormapGroupBox);
    ColormapRadioButton *royalColormapRadioButton =
            new ColormapRadioButton(tr("royal"),":colormaps/royal.bmp",colormapGroupBox);
    ColormapRadioButton *topographColormapRadioButton =
            new ColormapRadioButton(tr("topograph"),":colormaps/topograph.bmp",colormapGroupBox);

    scaleWidget = new ScaleWidget(this);
    scaleWidget->changeScale(fireColormapRadioButton->getScale());
    scaleWidget->setFixedWidth(50);
    scale=fireColormapRadioButton->getScale();

    connect(fireColormapRadioButton,SIGNAL(scaleChoosen(Scale *)),this,SLOT(setScalePointer(Scale *)));
    connect(grayscaleColormapRadioButton,SIGNAL(scaleChoosen(Scale *)),this,SLOT(setScalePointer(Scale *)));
    connect(rainbowColormapRadioButton,SIGNAL(scaleChoosen(Scale *)),this,SLOT(setScalePointer(Scale *)));
    connect(royalColormapRadioButton,SIGNAL(scaleChoosen(Scale *)),this,SLOT(setScalePointer(Scale *)));
    connect(topographColormapRadioButton,SIGNAL(scaleChoosen(Scale *)),this,SLOT(setScalePointer(Scale *)));


    QHBoxLayout *mainLayout = new QHBoxLayout;

    QHBoxLayout *colormapGroupBoxLayout = new QHBoxLayout(colormapGroupBox);

    QVBoxLayout *buttonsLayout = new QVBoxLayout;
    buttonsLayout->addWidget(fireColormapRadioButton);
    buttonsLayout->addWidget(grayscaleColormapRadioButton);
    buttonsLayout->addWidget(rainbowColormapRadioButton);
    buttonsLayout->addWidget(royalColormapRadioButton);
    buttonsLayout->addWidget(topographColormapRadioButton);
    buttonsLayout->addStretch();
    colormapGroupBoxLayout->addLayout(buttonsLayout);
    colormapGroupBoxLayout->addWidget(scaleWidget);

    mainLayout->addWidget(colormapGroupBox);

    setLayout(mainLayout);
}

void ScaleSelectionWidget::setScalePointer(Scale *scale)
{
    this->scale = scale;
    this->scaleWidget->changeScale(scale);
    emit scaleChanged(scale);
}
