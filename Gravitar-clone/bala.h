#ifndef BALA_H
#define BALA_H

#include <stdbool.h>
#include "nivel.h"
//#include "lista.h"
//#include "nave.h"

#define BALA_DURACION 700 //7 segundos

typedef struct bala bala_t;

//CREACION Y DESTRUCCION
bala_t* bala_crear(double posx, double posy, double vel, double ang, nivel_enum_t nivel, bool jugador);
void bala_destruir(bala_t *bala);


//GETTERS
//double bala_get_ang(bala_t *bala);
double bala_get_posx(bala_t *bala);
double bala_get_posy(bala_t *bala);
//double bala_get_vel(bala_t* bala);
double bala_get_vely(bala_t *bala);
double bala_get_velx(bala_t * bala);
nivel_enum_t bala_get_nivel(bala_t *bala);
bool bala_es_de_jugador(bala_t *bala);


//SETTERS
void bala_set_pos(bala_t *bala, double posx, double posy);
void bala_set_vel(bala_t *bala, double velx, double vely);
void bala_set_nivel(bala_t *bala, nivel_enum_t nivel);
//void bala_setear_ang(bala_t *bala, double ang);
bool bala_actualizar(bala_t* bala, double dt);
//void balas_mover(lista_t *balas);

#endif