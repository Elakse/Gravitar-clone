#ifndef TORRETA_H
#define TORRETA_H

#include <SDL.h>
#include "figuras.h"
#include "bala.h"


typedef struct torreta torreta_t;

//Condición: Para el funcionamiento del TDA torreta_t las figuras anexadas al crear la torreta no deben ser destruidas.
//Pre para todas las funciones: todos los punteros deben apuntar a memoria valida correspondiente a su tipo.

//CREACION Y DESTRUCCION

torreta_t* torreta_crear(double posx, double posy, double ang, figura_t* fig_base, figura_t* fig_disparando);
void torreta_destruir(torreta_t* torreta, figura_t** fig_base, figura_t** fig_disparando);
void torreta_destruir_no_ref(torreta_t* torreta);

//GETTERS
double torreta_get_posx(torreta_t* torreta);
double torreta_get_posy(torreta_t* torreta);
double torreta_get_ang(torreta_t* torreta);

//SETTERS
void torreta_set_pos(torreta_t* torreta, double posx, double posy);
void torreta_set_ang(torreta_t* torreta, double ang);

//ACCIONES
void torreta_randomizar_disparos(void);
bala_t* torreta_dispara(torreta_t* torreta, double ang, double rango, size_t chances, double vel, size_t duracion_disparo, figura_t* bala_fig);
bool torreta_dibujar(torreta_t* torreta, double tras_x, double tras_y, double centro_escala, double escala, SDL_Renderer* renderer);

double torreta_distancia_a_punto(torreta_t* torreta, double px, double py);

#endif