#ifndef POLILINEA_H
#define POLILINEA_H

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <SDL.h>
#include "color.h"
#define ROJO        0x04
#define VERDE       0x02
#define AZUL        0x01
#define INFINITO    0x40
#define TIPO        0x07
#define CANT_PUNTOS 0x03FF

typedef struct polilinea polilinea_t;

//CREACIÓN Y DESTRUCCION

polilinea_t *polilinea_crear_vacia(size_t n);
polilinea_t* leer_polilinea(FILE* f);
polilinea_t *polilinea_crear(const float puntos[][2], size_t n, color_t color);
void polilinea_destruir(polilinea_t *polilinea);

//GETTERS Y SETTERS

size_t polilinea_cantidad_puntos(const polilinea_t *polilinea);
bool polilinea_obtener_punto(const polilinea_t *polilinea, size_t pos, float *x, float *y);
color_t polilinea_obtener_color(const polilinea_t *polilinea);
bool polilinea_setear_punto(polilinea_t *polilinea, size_t pos, float x, float y);
void polilinea_setear_color(polilinea_t *polilinea, color_t color);
double polilinea_obtener_x_max(const polilinea_t* polilinea);
double polilinea_obtener_y_max(const polilinea_t* polilinea);
double polilinea_obtener_x_min(const polilinea_t* polilinea);
double polilinea_obtener_y_min(const polilinea_t* polilinea);

//MOVIMIENTO Y DISTANCIA

void polilinea_trasladar(polilinea_t *polilinea, float dx, float dy);
void polilinea_rotar(polilinea_t *polilinea, double rad);
void polilinea_escalar(polilinea_t* polilinea, double escala);
double distancia_punto_a_polilinea(const polilinea_t *polilinea, float px, float py);

//MEMORIA

polilinea_t *polilinea_clonar(const polilinea_t *polilinea);

//DIBUJADO

void polilinea_dibujar(polilinea_t* poli, double pos_x, double pos_y, double ang, double escala, SDL_Renderer* renderer);
void polilinea_dibujar_escala_relativa(polilinea_t* poli, double posx, double posy, double ang, double centro, double escala, SDL_Renderer* renderer);

#endif
