#pragma once

#include <QtWidgets>
#include <QPainter>
#include "params.hpp"
#include "matrix.hpp"
#include "juliaset.hpp"

class Canvas : public QWidget {
  Q_OBJECT

// protected slots:
//   void realSliderChanged();
//   void imagSliderChanged();

private:
  JuliaSet js;

public:
  Canvas();
  void renderImage();
  void setCReal(double value);
  void setCImag(double value);
  QSize sizeHint() const override;

protected:
  void paintEvent(QPaintEvent *event) override;
};

class Window : public QWidget {
  Q_OBJECT

private:
  QSlider *realSlider;
  QSlider *imagSlider;
  QHBoxLayout *mainLayout;
  Canvas *canvas;

public:
  Window();
};
