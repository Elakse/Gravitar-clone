#ifndef FISICA_H
#define FISICA_H

double computar_velocidad(double vi, double a, double dt);
double computar_posicion(double pi, double vi, double dt);
double com_x(double mod, double ang);
double com_y(double mod, double ang);
double computar_distancia(double x1, double y1, double x2, double y2);
double computar_angulo(double x1, double y1, double x2, double y2);
double com_modulo(double x, double y);

#endif