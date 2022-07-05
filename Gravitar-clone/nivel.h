#ifndef NIVEL_H
#define NIVEL_H
#include <stdbool.h>
#include <SDL.h>
#include "figuras.h"
#include "nave.h"

#define DISTANCIA_COLISION 4

struct nivel;
typedef struct nivel nivel_t;

//CREACION Y DESTRUCCION

nivel_t* nivel_crear(figura_t* figura, size_t duracion_de_balas);
void nivel_destruir(nivel_t* nivel);


//SETTER

bool nivel_agregar_torreta(nivel_t* nivel, double posx, double posy, double ang, figura_t* fig_base, figura_t* fig_disparando);

bool nivel_agregar_combustible(nivel_t* nivel, double posx, double posy, double ang, figura_t* figura);

bool nivel_agregar_bala(nivel_t* nivel, double posx, double posy, double vel, double ang, bool jugador, figura_t* fig_bala);

bool nivel_agregar_planeta(nivel_t* nivel, double posx, double posy, double posx_tp, double posy_tp, enum estadio estad, figura_t* fig_planeta);

bool nivel_agregar_reactor(nivel_t* nivel, double posx, double posy, double ang, size_t tiempo, figura_t* fig_react);

bool nivel_nave_dispara(nivel_t* nivel, struct nave* nave, double vel, figura_t* fig_bala);

bool nivel_torretas_disparan_a_nave(nivel_t* nivel,struct nave* nave, double rango, size_t chances, double vel, figura_t* fig_bala);

bool nivel_nave_disparada(nivel_t* nivel, struct nave* nave); 

size_t nivel_torretas_disparadas(nivel_t* nivel);

void nivel_balas_actualizar(nivel_t* nivel, double dt);

void nivel_dibujar(nivel_t* nivel, double centro, double escala, double ventana_ancho, SDL_Renderer* renderer);



#endif