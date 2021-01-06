#pragma once

#include <QtWidgets>
#include <QPainter>
#include <utility>
#include "params.hpp"
#include "juliaset.hpp"
#include "rangeslider.hpp"

class Canvas : public QWidget {
  Q_OBJECT

private:
  JuliaSet js;
  QVector<QRgb> pixels;
  QOpenGLPaintDevice viewer;
  QVector<std::pair<int, int>> templatePixels;

public:
  Canvas();
  QRgb pixelValue(std::pair<int, int>);
  QSize sizeHint() const override;
  void renderPixels();

public slots:
  void rChanged(double value);
  void cRealChanged(double value);
  void cImagChanged(double value);
  void maxIterChanged(int value);

protected:
  void paintEvent(QPaintEvent *event) override;
};

class Window : public QWidget {
  Q_OBJECT

private:
  RangeSlider *realSlider;
  RangeSlider *imagSlider;
  RangeSlider *rSlider;
  RangeSlider *maxIterSlider;
  QHBoxLayout *mainLayout;
  Canvas *canvas;

public:
  Window();
};
