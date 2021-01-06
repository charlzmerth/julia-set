#include <QtConcurrent>
#include <QOpenGLPaintDevice>
#include <QtWidgets>
#include <QPainter>
#include <functional>
#include "canvas.hpp"
#include "rangeslider.hpp"

Canvas::Canvas()
  : js {CANVAS_WIDTH, CANVAS_HEIGHT, C_REAL_INIT, C_IMAG_INIT, MAX_ITER_INIT},
    pixels (NUM_PIXELS),
    viewer {CANVAS_WIDTH, CANVAS_HEIGHT},
    templatePixels {} {

  // Insert "ascending" pairs into templatePixels
  templatePixels.resize(NUM_PIXELS);
  for (int y = 0; y < CANVAS_HEIGHT; y++)
    for (int x = 0; x < CANVAS_WIDTH; x++)
      templatePixels[x + y * CANVAS_WIDTH] = std::pair<int, int>(x, y);

  renderPixels();
  update();
}

QSize Canvas::sizeHint() const {
  return QSize(CANVAS_WIDTH, CANVAS_HEIGHT);
}

void Canvas::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);

  QPainter painter(this);
  painter.drawImage(0, 0, image);
}

void Canvas::renderPixels() {
  // auto jsMapFunc = [this](std::pair<int, int> p) -> QRgb { return this->pixelValue(p); };
  std::function<QRgb(std::pair<int, int>)> jsMapFunc = std::bind(&Canvas::pixelValue, this, std::placeholders::_1);
  pixels = QtConcurrent::blockingMapped<QVector<QRgb>, QVector<std::pair<int, int>>, std::function<QRgb(std::pair<int, int>)>>(templatePixels, jsMapFunc);
  QRgb *rawPixels = pixels.data();
  image = QImage {(uchar*)rawPixels, CANVAS_WIDTH, CANVAS_HEIGHT, QImage::Format_ARGB32};
}

QRgb Canvas::pixelValue(std::pair<int, int> coords) {
  int iter = js.pixelValue(coords.first, coords.second);
  int norm = iter * 255 / (js.maxIter + 1);
  // QColor color = QColor::fromHsv(norm, 255, 255).rgb();
  return QColor{0, 0, norm}.rgb();
}

void Canvas::cRealChanged(double value) {
  js.setCReal(value);
  renderPixels();
  update();
}

void Canvas::cImagChanged(double value) {
  js.setCImag(value);
  renderPixels();
  update();
}

void Canvas::rChanged(double value) {
  js.setR(value);
  renderPixels();
  update();
}

void Canvas::maxIterChanged(int value) {
  js.maxIter = value;
  renderPixels();
  update();
}

Window::Window() {
  rSlider = new RangeSlider(R_MIN, R_MAX, R_INTERVAL, R_INIT);
  maxIterSlider = new RangeSlider(MAX_ITER_MIN, MAX_ITER_MAX, MAX_ITER_INTERVAL, MAX_ITER_INIT);
  realSlider = new RangeSlider(C_MIN, C_MAX, C_INTERVAL, C_REAL_INIT);
  imagSlider = new RangeSlider(C_MIN, C_MAX, C_INTERVAL, C_IMAG_INIT);

  canvas = new Canvas;
  connect(rSlider, &RangeSlider::valueChanged, canvas, &Canvas::rChanged);
  connect(maxIterSlider, &RangeSlider::valueChanged, canvas, &Canvas::maxIterChanged);
  connect(realSlider, &RangeSlider::valueChanged, canvas, &Canvas::cRealChanged);
  connect(imagSlider, &RangeSlider::valueChanged, canvas, &Canvas::cImagChanged);

  mainLayout = new QHBoxLayout;
  mainLayout->addWidget(maxIterSlider);
  mainLayout->addWidget(rSlider);
  mainLayout->addWidget(canvas);
  mainLayout->addWidget(realSlider);
  mainLayout->addWidget(imagSlider);
  setLayout(mainLayout);
}
