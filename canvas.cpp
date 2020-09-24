#include <QtWidgets>
#include <QPainter>
#include "canvas.hpp"
#include "matrix.hpp"
#include <iostream>

Canvas::Canvas() : js {} {

}

QSize Canvas::sizeHint() const {
  return QSize(CANVAS_WIDTH, CANVAS_HEIGHT);
}

void Canvas::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);
  renderImage();
}

void Canvas::renderImage() {
  QRgb* pixels = new QRgb[CANVAS_WIDTH * CANVAS_HEIGHT];
  Matrix<double, CANVAS_WIDTH, CANVAS_HEIGHT> jsBitmap = js.generate();

  QImage image((uchar*)pixels, CANVAS_WIDTH, CANVAS_HEIGHT, QImage::Format_ARGB32);
  for (int y = 0; y < CANVAS_HEIGHT; y++) {
    for (int x = 0; x < CANVAS_WIDTH; x++) {
      int hue = jsBitmap.get(x, y) * 358;
      pixels[x + y * CANVAS_HEIGHT] = QColor::fromHsv(hue, 255, 255).rgb();
    }
  }

  QPainter painter(this);
  painter.drawImage(0, 0, image);

  delete[] pixels;
}

void Canvas::setCReal(double value) {
  js.setCReal(value / 100.0);
  repaint();
}

void Canvas::setCImag(double value) {
  js.setCImag(value / 100.0);
  update();
}



Window::Window() {
  realSlider = new QSlider;
  realSlider->setMinimum(0);
  realSlider->setMaximum(100);

  imagSlider = new QSlider;
  imagSlider->setMinimum(0);
  imagSlider->setMaximum(100);

  canvas = new Canvas;

  connect(realSlider, &QSlider::valueChanged, canvas, &Canvas::setCReal);
  connect(imagSlider, &QSlider::valueChanged, canvas, &Canvas::setCImag);


  mainLayout = new QHBoxLayout;
  mainLayout->addWidget(realSlider);
  mainLayout->addWidget(canvas);
  mainLayout->addWidget(imagSlider);
  setLayout(mainLayout);
}
