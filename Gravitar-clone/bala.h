#ifndef BALA_H
#define BALA_H

#include <stdbool.h>
#include "nivel.h"
#include "figuras.h"

typedef struct bala bala_t;

//CREACION Y DESTRUCCION
bala_t* bala_crear(double posx, double posy, double vel, double ang, size_t duracion, bool jugador, figura_t* figura);
void bala_destruir(bala_t* bala, figura_t** figura);



//GETTERS
//double bala_get_ang(bala_t *bala);
double bala_get_posx(bala_t *bala);
double bala_get_posy(bala_t *bala);
//double bala_get_vel(bala_t* bala);
double bala_get_vely(bala_t *bala);
double bala_get_velx(bala_t * bala);
bool bala_es_de_jugador(bala_t *bala);


//SETTERS
void bala_set_pos(bala_t *bala, double posx, double posy);
void bala_set_vel(bala_t *bala, double velx, double vely);
//void bala_setear_ang(bala_t *bala, double ang);
bool bala_actualizar(bala_t* bala, double dt);
//void balas_mover(lista_t *balas);

//DIBUJO
bool bala_dibujar(bala_t* bala, double tras_x, double tras_y, double centro_escala, double escala, SDL_Renderer* renderer);

#endif