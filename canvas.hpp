#pragma once

#include <QtWidgets>
#include <QPainter>
#include "params.hpp"
#include "matrix.hpp"
#include "juliaset.hpp"

class Canvas : public QWidget {
private slots:
  void realSliderChanged();

private:
  JuliaSet js;
  QSlider *realSlider;

public:
  Canvas();
  void renderImage();

protected:
  void paintEvent(QPaintEvent *event) override;
};
