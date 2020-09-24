#include <QtWidgets>
#include <QPainter>
#include "canvas.hpp"
#include "matrix.hpp"

Canvas::Canvas() : js {} {
  realSlider = new QSlider;
  realSlider->setTickInterval(TICK_INTERVAL);
  connect(realSlider, QOverload<int>::of(&QSlider::valueChanged),
          this, &Canvas::renderImage);
}

void Canvas::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);
  renderImage();
}

void Canvas::renderImage() {
  QRgb* pixels = new QRgb[CANVAS_WIDTH * CANVAS_HEIGHT];
  Matrix<double, CANVAS_WIDTH, CANVAS_HEIGHT> jsBitmap = js.generate();
  // jsBitmap.printMatrix();

  QImage image((uchar*)pixels, CANVAS_WIDTH, CANVAS_HEIGHT, QImage::Format_ARGB32);
  for (int y = 0; y < CANVAS_HEIGHT; y++) {
    for (int x = 0; x < CANVAS_WIDTH; x++) {
      int hue = jsBitmap.get(x, y) * 359;
      pixels[x + y * CANVAS_HEIGHT] = QColor::fromHsv(hue, 255, 255).rgb();
    }
  }

  QPainter painter(this);
  painter.drawImage(0, 0, image);

  delete[] pixels;
}
