#include <QApplication>
#include <QWidget>
#include "params.hpp"
#include "canvas.hpp"

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);
  Window w;

  // c.resize(WINDOW_WIDTH, WINDOW_HEIGHT);
  w.setWindowTitle("JuliaSet");
  w.show();

  return app.exec();
}
