#ifndef POLILINEA_H
#define POLILINEA_H

#include <stdbool.h>
#include <stddef.h>
#include "color.h"

typedef struct polilinea polilinea_t;

polilinea_t *polilinea_crear_vacia(size_t n);
polilinea_t *polilinea_crear(const float puntos[][2], size_t n, color_t color);
void polilinea_destruir(polilinea_t *polilinea);

size_t polilinea_cantidad_puntos(const polilinea_t *polilinea);
bool polilinea_obtener_punto(const polilinea_t *polilinea, size_t pos, float *x, float *y);
color_t polilinea_obtener_color(const polilinea_t *polilinea);
bool polilinea_setear_punto(polilinea_t *polilinea, size_t pos, float x, float y);
void polilinea_setear_color(polilinea_t *polilinea, color_t color);

void trasladar(polilinea_t *polilinea, float dx, float dy);
void rotar(polilinea_t *polilinea, double rad);
double distancia_punto_a_polilinea(const polilinea_t *polilinea, float px, float py);

polilinea_t *polilinea_clonar(const polilinea_t *polilinea);

#endif
