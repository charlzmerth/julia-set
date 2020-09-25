#pragma once

#include <QtWidgets>
#include <QPainter>
#include <utility>
#include "params.hpp"
#include "matrix.hpp"
#include "juliaset.hpp"

static const int TICK_INTERVAL = 1;
static const int TICK_START = 0;
static const int TICK_END = 100;
static const double C_TICK_DIV = 100.0;
static const double R_TICK_DIV = 10.0;
static const int MAX_ITER_SCALE = 10;

class Canvas : public QWidget {
  Q_OBJECT

private:
  JuliaSet js;
  QVector<QRgb> pixels;
  QImage image;
  QVector<std::pair<int, int>> templatePixels;

public:
  Canvas();
  QRgb pixelValue(std::pair<int, int>);
  void rChanged(double value);
  void cRealChanged(double value);
  void cImagChanged(double value);
  void maxIterChanged(int value);
  QSize sizeHint() const override;
  void renderPixels();

protected:
  void paintEvent(QPaintEvent *event) override;
};

class Window : public QWidget {
  Q_OBJECT

private:
  QSlider *realSlider;
  QSlider *imagSlider;
  QSlider *rSlider;
  QSlider *maxIterSlider;
  QHBoxLayout *mainLayout;
  Canvas *canvas;

public:
  Window();
};
