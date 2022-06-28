#ifndef COMBUSTIBLE_H
#define COMBUSTIBLE_H
#include "nave.h"

typedef struct combustible combustible_t;

//CREACION Y DESTRUCCION
combustible_t* combustible_crear(nivel_enum_t nivel, double posx, double posy, double ang);
void combustible_destruir(combustible_t* combustible);

//GETTERS
double combustible_get_posx(combustible_t* combustible);
double combustible_get_posy(combustible_t* combustible);
double combustible_get_ang(combustible_t* combustible);
nivel_enum_t combustible_get_nivel(combustible_t* combustible);

//SETTERS
void combustible_set_pos(combustible_t* combustible, double posx, double posy);
void combustible_set_ang(combustible_t* combustible, double ang);
void combustible_set_nivel(combustible_t* combustible, nivel_enum_t nivel);

#endif