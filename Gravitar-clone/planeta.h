#ifndef PLANETA_H
#define PLANETA_H

#include "nave.h"
#include "figuras.h"

typedef struct planeta planeta_t;

//CREACIÓN y DESTRUCCIÓN

planeta_t* planeta_crear(double posx, double posy, double posx_tp, double posy_tp, size_t puntaje, estadio_t nivel, figura_t* planeta_fig);
void planeta_destruir(planeta_t* planeta, figura_t** figura);
void planeta_destruir_no_ref(planeta_t* planeta);

//GETTERS

estadio_t planeta_get_estadio(planeta_t* planeta);
figura_t* planeta_get_fig(planeta_t* planeta);
//char* planeta_get_figura_nom(planeta_t* planeta);
double planeta_get_posx(planeta_t* planeta);
double planeta_get_posy(planeta_t* planeta);
double planeta_get_posx_tp(planeta_t* planeta);
double planeta_get_posy_tp(planeta_t* planeta);
size_t planeta_get_puntaje(planeta_t* planeta);

//DISTANCIA

double planeta_distancia_a_punto(planeta_t* planeta, double px, double py);

//DIBUJO

bool planeta_dibujar(planeta_t* planeta, double tras_x, double tras_y, double centro_escala, double escala, SDL_Renderer* renderer);

#endif
