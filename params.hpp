#ifndef _PARAMS_HPP_
#define _PARAMS_HPP_

// static const int WINDOW_WIDTH = 1000;
// static const int WINDOW_HEIGHT = 1000;
static const int CANVAS_WIDTH = 1000;
static const int CANVAS_HEIGHT = CANVAS_WIDTH;
static const int NUM_PIXELS = CANVAS_WIDTH * CANVAS_HEIGHT;

// Slider parameters
static const int PRECISION = 2;

static const double R_MIN = 1.0;
static const double R_MAX = 3.0;
static const double R_INIT = 2;
static const double R_INTERVAL = 0.1;

static const int MAX_ITER_MIN = 1;
static const int MAX_ITER_MAX = 200;
static const int MAX_ITER_INIT = 50;
static const int MAX_ITER_INTERVAL = 1;

static const double C_MIN = -1.0;
static const double C_MAX = 1.0;
static const double C_INTERVAL = 0.05;
static const double C_REAL_INIT = 0.285;
static const double C_IMAG_INIT = 0.01;


#endif /* end of include guard: _PARAMS_HPP_ */
