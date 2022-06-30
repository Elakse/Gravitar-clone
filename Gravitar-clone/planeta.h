#ifndef PLANETA_H
#define PLANETA_H

#include "nivel.h"

typedef struct planeta planeta_t;

//CREACIÓN y DESTRUCCIÓN

planeta_t* planeta_crear(double posx, double posy, nivel_enum_t nivel, figura_t *planeta_fig);
void planeta_destruir(planeta_t* planeta);

//GETTERS

nivel_enum_t planeta_get_nivel(planeta_t* planeta);
figura_t* planeta_get_fig(planeta_t* planeta);
//char* planeta_get_figura_nom(planeta_t* planeta);
double planeta_get_posx(planeta_t* planeta);
double planeta_get_posy(planeta_t* planeta);

//FISICA

double planeta_distancia_a_punto(planeta_t* planeta, double x, double y);

#endif
