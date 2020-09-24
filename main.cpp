#include <QApplication>
#include <QWidget>
#include "params.hpp"
#include "canvas.hpp"

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);
  Canvas c;

  c.resize(WINDOW_WIDTH, WINDOW_HEIGHT);
  c.setWindowTitle("JuliaSet");
  c.show();

  return app.exec();
}
