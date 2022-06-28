#ifndef NAVE_H
#define NAVE_H

#include<SDL.h>
#include "polilinea.h"
#include "nivel.h"

typedef struct nave nave_t;

//CREACION Y DESTRUCCION

nave_t *nave_crear(size_t vidas, size_t fuel, nivel_enum_t nivel, char *figura);
void nave_destruir(nave_t *nave);

//SETTERS

void nave_setear_pos(nave_t *nave, double px, double py);
void nave_setear_vel(nave_t *nave, double vx, double vy);
void nave_setear_vely(nave_t *nave, double vy);
void nave_setear_velx(nave_t *nave, double vx);
void nave_setear_nivel(nave_t* nave, nivel_enum_t nivel);
void nave_setear_vidas(nave_t* nave, size_t vidas);
void nave_restar_vida(nave_t* nave);
void nave_sumar_vida(nave_t* nave);
void nave_setear_ang_nave(nave_t *nave, double ang);
void nave_setear_a_thrust(nave_t *nave, float a);
void nave_setear_ang_g(nave_t *nave, double ang);
bool nave_cambiar_nombre_fig(nave_t *nave, char *nombre);

//GETTERS

double nave_get_posx(nave_t *nave);
double nave_get_posy(nave_t *nave);
size_t nave_get_vidas(nave_t* nave);
nivel_enum_t nave_get_nivel(nave_t *nave);
double nave_get_ang(nave_t *nave);
double nave_get_vel(nave_t *nave);
double nave_get_velx(nave_t *nave);
double nave_get_vely(nave_t *nave);
char* nave_get_nombre_fig(nave_t* nave);

//MOVIMIENTO

void nave_girar_der(nave_t *nave, double ang);
void nave_girar_izq(nave_t *nave, double ang);
void nave_mover(nave_t *nave, double dt);

#endif
