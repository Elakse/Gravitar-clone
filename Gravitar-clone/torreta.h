#ifndef TORRETA_H
#define TORRETA_H
#include "nave.h"

typedef struct torreta torreta_t;

//CREACION Y DESTRUCCION
torreta_t* torreta_crear(nivel_t nivel, double posx, double posy, double ang);
void torreta_destruir(torreta_t* torreta);

//GETTERS
double torreta_get_posx(torreta_t* torreta);
double torreta_get_posy(torreta_t* torreta);
double torreta_get_ang(torreta_t* torreta);
nivel_t torreta_get_nivel(torreta_t* torreta);

//SETTERS
void torreta_set_pos(torreta_t* torreta, double posx, double posy);
void torreta_set_ang(torreta_t* torreta, double ang);
void torreta_set_nivel(torreta_t* torreta, nivel_t nivel);

#endif