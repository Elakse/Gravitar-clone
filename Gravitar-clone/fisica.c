#include "fisica.h"
#include <math.h>

double computar_velocidad(double vi, double a, double dt) {
	return dt * a + vi;
}

double computar_posicion(double pi, double vi, double dt) {
	return dt * vi + pi;
}

double com_x(double mod, double ang) {
	return mod * cos(ang);
}

double com_y(double mod, double ang) {
	return mod * sin(ang);
}

double com_modulo(double x, double y) {
	return sqrt(x * x + y * y);
}