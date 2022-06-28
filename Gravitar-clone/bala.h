#ifndef BALA_H
#define BALA_H

#include "nave.h"
#include "lista.h"

typedef struct bala bala_t;

bala_t* bala_crear(nave_t *nave);
void bala_destruir(bala_t *bala);
double bala_get_ang(bala_t* bala);
double bala_get_posx(bala_t* bala);
double bala_get_posy(bala_t* bala);
void bala_setear_ang(bala_t* bala, double ang);
void bala_mover(bala_t* bala, double dt);
void balas_mover(lista_t* balas);

#endif