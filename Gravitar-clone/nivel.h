#ifndef NIVEL_H
#define NIVEL_H
#include <stdbool.h>
#include "figuras.h"

typedef enum { INICIO, NIVEL1, NIVEL2, NIVEL3, NIVEL4, NIVEL5 } nivel_enum_t;

typedef struct nivel nivel_t;

//CREACION Y DESTRUCCION
void nivel_dibujar(nivel_t* nivel, double escala, double centro, SDL_Renderer* renderer);
nivel_t* nivel_crear(nivel_enum_t nivel_enum);
void nivel_destruir(nivel_t* nivel);
//void nivel_tickear(nivel_t* nivel, struct nave_t* nave, double escala, double centro, SDL_Renderer* renderer);

//SETTER

#endif