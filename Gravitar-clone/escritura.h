#ifndef ESCRITURA_H
#define ESCRITURA_H

#include "caracteres.h"
#include <stdbool.h>
#include <SDL.h>

struct caracter;

struct caracter letra_a_caracter(char letra);


void dibujar_caracter(char letra, double posx, double posy, double escala, bool r, bool g, bool b, double ventana_alto, SDL_Renderer* renderer);
void dibujar_texto(char* texto, double posx, double posy, double escala, bool r, bool g, bool b, double ventana_alto, SDL_Renderer* renderer);


#endif
