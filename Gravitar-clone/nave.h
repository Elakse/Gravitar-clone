#ifndef NAVE_H
#define NAVE_H

#include "bala.h"
#include "figuras.h"
#include<SDL.h>
#include<stdbool.h>


enum estadio { INICIO, NIVEL1, NIVEL2, NIVEL3, NIVEL4, NIVEL5 };
typedef enum estadio estadio_t;

typedef struct nave nave_t;

//CREACION Y DESTRUCCION

nave_t* nave_crear(size_t vidas, size_t fuel, estadio_t estadio, figura_t* fig_base, figura_t* fig_thruster_on);
void nave_destruir(nave_t* nave, figura_t** fig_base, figura_t** fig_thruster_on);

//SETTERS

void nave_setear_pos(nave_t *nave, double px, double py);
void nave_setear_vel(nave_t *nave, double vx, double vy);
void nave_setear_vely(nave_t *nave, double vy);
void nave_setear_velx(nave_t *nave, double vx);
void nave_setear_estadio(nave_t* nave, estadio_t estadio);
void nave_setear_vidas(nave_t* nave, size_t vidas);
void nave_restar_vida(nave_t* nave);
void nave_sumar_vida(nave_t* nave);
void nave_setear_ang_nave(nave_t* nave, double ang);
void nave_setear_a_thrust(nave_t* nave, float a);
void nave_setear_ang_g(nave_t *nave, double ang);

//GETTERS

double nave_get_posx(nave_t *nave);
double nave_get_posy(nave_t *nave);
size_t nave_get_vidas(nave_t* nave);
estadio_t nave_get_estadio(nave_t* nave);
double nave_get_ang(nave_t* nave);
double nave_get_vel(nave_t* nave);
double nave_get_velx(nave_t* nave);
double nave_get_vely(nave_t* nave);

//MOVIMIENTO

void nave_girar_der(nave_t* nave, double ang);
void nave_girar_izq(nave_t* nave, double ang);
void nave_mover(nave_t* nave, double dt);
double nave_distancia_a_punto(nave_t* nave, double x, double y);
double nave_distancia_a_figura(nave_t* nave, figura_t* figura);
bala_t* nave_dispara(nave_t* nave, double vel, size_t duracion_disparo, figura_t* bala_fig);


//DIBUJADO

bool nave_dibujar(nave_t* nave, double tras_x, double tras_y, double centro_escala, double escala, SDL_Renderer* renderer);

#endif
