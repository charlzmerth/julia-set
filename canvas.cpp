#include <QtConcurrent>
#include <QtWidgets>
#include <QPainter>
#include <functional>
#include "canvas.hpp"

Canvas::Canvas()
  : js {CANVAS_WIDTH, CANVAS_HEIGHT, C_REAL_INIT, C_IMAG_INIT, MAX_ITER_INIT},
    pixels {NUM_PIXELS},
    image {},
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
  js.setCReal(value / C_TICK_DIV);
  renderPixels();
  update();
}

void Canvas::cImagChanged(double value) {
  js.setCImag(value / C_TICK_DIV);
  renderPixels();
  update();
}

void Canvas::rChanged(double value) {
  js.setR(value / R_TICK_DIV);
  renderPixels();
  update();
}

void Canvas::maxIterChanged(int value) {
  js.maxIter = value * MAX_ITER_SCALE;
  renderPixels();
  update();
}

Window::Window() {
  rSlider = new QSlider;
  rSlider->setMinimum(TICK_START);
  rSlider->setMaximum(TICK_END);
  rSlider->setValue(R_INIT * R_TICK_DIV);

  maxIterSlider = new QSlider;
  maxIterSlider->setMinimum(TICK_START);
  maxIterSlider->setMaximum(TICK_END);
  maxIterSlider->setValue(MAX_ITER_INIT / MAX_ITER_SCALE);

  realSlider = new QSlider;
  realSlider->setMinimum(TICK_START);
  realSlider->setMaximum(TICK_END);
  realSlider->setValue(C_REAL_INIT * C_TICK_DIV);

  imagSlider = new QSlider;
  imagSlider->setMinimum(TICK_START);
  imagSlider->setMaximum(TICK_END);
  imagSlider->setValue(C_IMAG_INIT * C_TICK_DIV);

  canvas = new Canvas;
  connect(rSlider, &QSlider::valueChanged, canvas, &Canvas::rChanged);
  connect(maxIterSlider, &QSlider::valueChanged, canvas, &Canvas::maxIterChanged);
  connect(realSlider, &QSlider::valueChanged, canvas, &Canvas::cRealChanged);
  connect(imagSlider, &QSlider::valueChanged, canvas, &Canvas::cImagChanged);

  mainLayout = new QHBoxLayout;
  mainLayout->addWidget(maxIterSlider);
  mainLayout->addWidget(rSlider);
  mainLayout->addWidget(canvas);
  mainLayout->addWidget(realSlider);
  mainLayout->addWidget(imagSlider);
  setLayout(mainLayout);
}
