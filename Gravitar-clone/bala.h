#ifndef BALA_H
#define BALA_H

#include "nivel.h"
#include "lista.h"
#include "nave.h"

typedef struct bala bala_t;

//CREACION Y DESTRUCCION
bala_t* bala_crear(nave_t *nave);
void bala_destruir(bala_t *bala);


//GETTERS
double bala_get_ang(bala_t *bala);
double bala_get_posx(bala_t *bala);
double bala_get_posy(bala_t *bala);
double bala_get_vel(bala_t* bala);
double bala_get_vely(bala_t *bala);
double bala_get_velx(bala_t * bala);
nivel_enum_t bala_get_nivel(bala_t *bala);
bool bala_es_de_jugador(bala_t *bala);


//SETTERS
void bala_set_pos(bala_t *bala, double posx, double posy);
void bala_set_vel(bala_t *bala, double vel);
void bala_set_nivel(bala_t *bala, nivel_enum_t nivel);
void bala_setear_ang(bala_t *bala, double ang);
void bala_mover(bala_t *bala, double dt);
void balas_mover(lista_t *balas);

#endif