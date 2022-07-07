#ifndef NIVEL_H
#define NIVEL_H

#include <stdbool.h>
#include <SDL.h>
#include "nave.h"
#include "figuras.h"

#define DISTANCIA_COLISION 4

typedef struct nivel nivel_t;

//El TDA nivel no devolverá referencias a las figuras de los objetos agregados al destuirlo, solo podrá devolver referencia a la figura del layout
//Todas las figuras anexadas al nivel o a los objetos agregados al nivel no deben ser destruidas para el funcionamiento de funciones de dibujado y colisiones
//Se asume a las figuras centradas en 0,0 excepto por los layouts.

//CREACION Y DESTRUCCION

nivel_t* nivel_crear(figura_t* figura, size_t duracion_de_balas);
void nivel_destruir(nivel_t* nivel, figura_t** figura);


//SETTERS

bool nivel_agregar_torreta(nivel_t* nivel, double posx, double posy, double ang, figura_t* fig_base, figura_t* fig_disparando);
bool nivel_agregar_combustible(nivel_t* nivel, double posx, double posy, double ang, figura_t* figura);
bool nivel_agregar_bala(nivel_t* nivel, double posx, double posy, double vel, double ang, bool jugador, figura_t* fig_bala);
bool nivel_agregar_planeta(nivel_t* nivel, double posx, double posy, double posx_tp, double posy_tp, estadio_t estad, figura_t* fig_planeta);
bool nivel_agregar_reactor(nivel_t* nivel, double posx, double posy, double ang, size_t tiempo, figura_t* fig_react);

//GETTERS

bool nivel_es_inf(nivel_t * nivel);
double nivel_get_ancho(nivel_t* nivel);
double nivel_get_alto(nivel_t* nivel);
void nivel_get_max_min(nivel_t* nivel, double* x_max, double* y_max, double* x_min, double* y_min);

//ACTUALIZACIONES e ITERACCIONES

bool nivel_nave_dispara(nivel_t* nivel, nave_t* nave, double vel, figura_t* fig_bala);
bool nivel_torretas_disparan_a_nave(nivel_t* nivel, nave_t* nave, double rango, size_t chances, double vel, figura_t* fig_bala);
bool nivel_nave_disparada(nivel_t* nivel, nave_t* nave); 
size_t nivel_torretas_disparadas(nivel_t* nivel);
void nivel_balas_actualizar(nivel_t* nivel, double dt);
bool nivel_nave_accede_planetas(nivel_t* nivel, nave_t* nave);

//DIBUJO

void nivel_dibujar(nivel_t* nivel, double centro, double escala, double ventana_ancho, SDL_Renderer* renderer);



#endif