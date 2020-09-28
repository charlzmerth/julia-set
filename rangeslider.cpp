#include <QtWidgets>
#include <QString>
#include "params.hpp"
#include "rangeslider.hpp"

RangeSlider::RangeSlider(double min, double max, double interval, double init)
  : min {min}, max {max}, interval {interval} {
    range = max - min;
    ticks = range / interval;

    QString minString = QString::number(min, 'g', PRECISION);
    minLabel = new QLabel{minString};
    QString maxString = QString::number(max, 'g', PRECISION);
    maxLabel = new QLabel{maxString};

    slider = new QSlider(Qt::Vertical);
    slider->setMinimum(0);
    slider->setTickInterval(1);
    slider->setMaximum(ticks);
    setValue(init);

    layout = new QVBoxLayout;
    layout->addWidget(maxLabel);
    layout->addWidget(slider);
    layout->addWidget(minLabel);
    setLayout(layout);

    connect(slider, &QSlider::valueChanged, this, &RangeSlider::valueChangedRedirect);
}

void RangeSlider::valueChangedRedirect() {
  emit valueChanged(this->getValue());
}

inline void RangeSlider::setValue(double n) {
  slider->setValue((n - min) / range * ticks);
}

inline double RangeSlider::getValue() const {
  return slider->value() / static_cast<double>(ticks) * range + min;
}
