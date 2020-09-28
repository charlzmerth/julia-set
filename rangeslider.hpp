#pragma once

#include <QtWidgets>

class RangeSlider : public QWidget {
  Q_OBJECT

private:
  const double min;
  const double max;
  const double interval;
  int ticks;
  double range;
  QSlider *slider;
  QLabel *minLabel;
  QLabel *maxLabel;
  QVBoxLayout *layout;

  inline void setValue(double n);
  inline double getValue() const;

private slots:
  void valueChangedRedirect();

public:
  RangeSlider(double min, double max, double interval, double init);

signals:
  void valueChanged(double value);
};
